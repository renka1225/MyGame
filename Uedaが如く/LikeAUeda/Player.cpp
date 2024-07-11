#include "DxLib.h"
#include "Camera.h"
#include "Stage.h"
#include "UIBattle.h"
#include "Shader.h"
#include "Input.h"
#include "Player.h"

// 定数
namespace
{
	// プレイヤー情報
	constexpr float kMaxHp = 100.0f;					// 最大HP
	constexpr float kMaxGauge = 100.0f;					// 最大ゲージ量
	constexpr float kMaxSpeed = 6.0f;					// プレイヤーの最大移動速度
	constexpr float kAcceleration = 0.2f;				// プレイヤーの加速度
	constexpr float kDeceleration = 0.2f;				// プレイヤーの減速度
	constexpr float kAvoidDist = 40.0f;					// 回避の距離
	constexpr float kAngleSpeed = 0.2f;					// プレイヤー角度の変化速度
	constexpr float kVelocity = 6.0f;					// ジャンプの高さ
	constexpr float kGravity = -0.25f;					// 重力
	constexpr float kScale = 0.3f;						// プレイヤーモデルの拡大率
	const VECTOR kInitDir = VGet(0.0f, 0.0f, 0.0f);		// 初期方向
	const VECTOR kInitPos = VGet(0.0f, 0.0f, 0.0f);		// 初期位置

	// アニメーション情報
	constexpr float kAnimBlendMax = 1.0f;	 // アニメーションブレンドの最大値
	constexpr float kAnimBlendSpeed = 0.2f;	 // アニメーションブレンドの変化速度
	constexpr float kPlayAnimSpeed = 0.5f;	 // 通常のアニメーションの速度
	constexpr float kAttackAnimSpeed = 0.7f; // 攻撃アニメーションの速度
}


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() :
	m_hp(kMaxHp),
	m_gauge(0.0f),
	m_pos(kInitPos),
	m_isMove(false),
	m_isAttack(false),
	m_targetMoveDir(kInitDir),
	m_angle(0.0f),
	m_jumpPower(0.0f),
	m_moveSpeed(0.0f),
	m_currentState(State::kFightIdle),
	m_modelHandle(-1),
	m_currentPlayAnim(-1),
	m_currentAnimCount(0.0f),
	m_prevPlayAnim(-1),
	m_prevAnimCount(0.0f),
	m_animBlendRate(kAnimBlendMax)
{
	m_modelHandle = MV1LoadModel("data/Model/player.mv1");
}


/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	MV1DeleteModel(m_modelHandle);
	//m_pShader->UnLoad();
}


/// <summary>
/// 初期化
/// </summary>
void Player::Init(std::shared_ptr<Shader> shader)
{
	m_pUIBattle = std::make_shared<UIBattle>();
	m_pShader = shader;
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	MV1SetPosition(m_modelHandle, m_pos);
	PlayAnim(AnimKind::kFightIdle);
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力コマンド</param>
/// <param name="stage">ステージ情報参照</param>
void Player::Update(const Input& input, const Camera& camera, Stage& stage)
{
	// シェーダをセット
	//m_pShader->Update();

	/*パッド入力によって移動パラメータを設定する*/
	VECTOR	upMoveVec;		// 上ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	leftMoveVec;	// 左ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	moveVec;		// このフレームの移動ベクトル

	// プレイヤーの状態を更新
	State prevState = m_currentState;
	m_currentState = Attack(input);
	m_currentState = Avoidance(input, moveVec);
	m_currentState = UpdateMoveParameter(input, camera, upMoveVec, leftMoveVec, moveVec);

	// アニメーション状態を更新
	UpdateAnimState(prevState);

	// プレイヤーの移動方向を設定
	UpdateAngle();

	// 移動ベクトルを元にプレイヤーを移動させる
	Move(moveVec, stage);

	// アニメーション処理の更新
	UpdateAnim();
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// シェーダの描画
	//m_pShader->Draw();

	MV1DrawModel(m_modelHandle);

	// HPゲージを表示
	m_pUIBattle->DrawPlayerHP(m_hp, kMaxHp);
	m_pUIBattle->DrawPlayerGauge(m_gauge, kMaxGauge);

#ifdef _DEBUG	// デバッグ表示
	DrawFormatString(0, 20, 0xffffff, "プレイヤー座標(%2f,%2f,%2f)", m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 40, 0xffffff, "hp:%f",m_hp);
#endif
}


/// <summary>
/// 床に当たったとき
/// </summary>
void Player::OnHitFloor()
{
	m_jumpPower = 0.0f;

	// 移動中の場合
	if (m_isMove)
	{
		// 移動状態にする
		m_currentState = State::kRun;
	}
	else
	{
		// 待機状態にする
		m_currentState = State::kFightIdle;
	}
}


/// <summary>
/// ダメージを受けたとき
/// </summary>
void Player::OnDamage()
{
	m_hp = std::min(m_hp, kMaxHp);
}


/// <summary>
/// プレイヤーの移動処理
/// </summary>
void Player::Move(const VECTOR& MoveVector, Stage& stage)
{
	// 攻撃中か
	bool isAttackAnim = m_currentPlayAnim == static_cast<int>(State::kPunch) || m_currentPlayAnim == static_cast<int>(State::kKick);
	if (fabs(MoveVector.x) > 0.0f || fabs(MoveVector.z) > 0.0f && isAttackAnim)
	{
		m_isMove = true;
	}
	else
	{
		m_isMove = false;
	}

	// 当たり判定を行って座標を保存する
	m_pos = stage.CheckCollision(*this, MoveVector);

	// プレイヤーの座標を更新する
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
///  攻撃処理
/// </summary>
/// <param name="input">入力処理</param>
/// <returns>現在の状態</returns>
Player::State Player::Attack(const Input& input)
{
	State nextState = m_currentState;

	if (input.IsTriggered("punch") && !m_isAttack)
	{
		m_isAttack = true;
		nextState = State::kPunch;

		m_gauge += 3.0f;
	}
	else if (input.IsTriggered("kick") && !m_isAttack)
	{
		m_isAttack = true;
		nextState = State::kKick;

		m_gauge += 5.0f;
	}

	m_gauge = std::min(m_gauge, kMaxHp);

	return nextState;
}


/// <summary>
/// 回避処理
/// </summary>
/// <param name="input">入力処理</param>
/// <returns>現在の状態</returns>
Player::State Player::Avoidance(const Input& input, VECTOR& moveVec)
{
	State nextState = m_currentState;

	if (input.IsTriggered("avoidance") && !m_isAttack)
	{
		m_isAttack = true;
		nextState = State::kAvoid;

		// 移動ベクトルを設定する
		VECTOR backMoveVec = VScale(m_targetMoveDir, -1.0f);
		m_pos = VAdd(m_pos, VScale(backMoveVec, kAvoidDist));
	}

	return nextState;
}


/// <summary>
/// 移動パラメータを設定する
/// </summary>
/// <param name="input">入力処理</param>
/// <param name="camera">カメラ</param>
/// <param name="upMoveVec">上方向への移動ベクトル</param>
/// <param name="leftMoveVec">左方向への移動ベクトル</param>
/// <param name="moveVec">移動ベクトル</param>
/// <returns>現在の状態</returns>
Player::State Player::UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	State nextState = m_currentState;

	/*プレイヤーの移動方向ベクトルを求める*/
	// 上ボタンを押したとき
	upMoveVec = VSub(camera.GetAngle(), camera.GetPos());
	upMoveVec.y = 0.0f;

	// 左ボタンを押したとき
	leftMoveVec = VCross(upMoveVec, VGet(0.0f, 1.0f, 0.0f));

	// ベクトルの正規化
	upMoveVec = VNorm(upMoveVec);
	leftMoveVec = VNorm(leftMoveVec);

	// このフレームでの移動ベクトルを初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// 移動したか(true:移動した)
	bool isPressMove = false;

	if (!m_isAttack)
	{
		// ボタンを押したら移動
		if (input.IsPressing("up"))
		{
			moveVec = VAdd(moveVec, upMoveVec);
			isPressMove = true;
		}
		if (input.IsPressing("down"))
		{
			moveVec = VAdd(moveVec, VScale(upMoveVec, -1.0f));
			isPressMove = true;
		}
		if (input.IsPressing("left"))
		{
			moveVec = VAdd(moveVec, leftMoveVec);
			isPressMove = true;
		}
		if (input.IsPressing("right"))
		{
			moveVec = VAdd(moveVec, VScale(leftMoveVec, -1.0f));
			isPressMove = true;
		}

		// 移動ボタンが押されている場合
		if (isPressMove)
		{
			// 待機状態の場合
			if (m_currentState == State::kFightIdle)
			{
				nextState = State::kRun; // 移動状態にする
			}

			// プレイヤーが向く方向を設定する
			m_targetMoveDir = VNorm(moveVec);

			// プレイヤーの加速度を設定する
			if (m_moveSpeed < kMaxSpeed)
			{
				m_moveSpeed += kAcceleration;
				m_moveSpeed = (std::min)(m_moveSpeed, kMaxSpeed);
			}
			// プレイヤーの移動ベクトルを設定する
			moveVec = VScale(m_targetMoveDir, m_moveSpeed);
		}
		// 移動しない場合
		else
		{
			// 移動状態の場合
			if (m_currentState == State::kRun)
			{
				// 待機状態にする
				nextState = State::kFightIdle;
				m_moveSpeed = 0.0f;
			}

			// プレイヤーを減速させる
			if (m_moveSpeed > 0.0f)
			{
				m_moveSpeed -= kDeceleration;
				m_moveSpeed = (std::max)(0.0f, m_moveSpeed);
			}
			moveVec = VScale(m_targetMoveDir, m_moveSpeed);
		}
	}

	return nextState;
}


/// <summary>
/// プレイヤーの回転を制御する
/// </summary>
void Player::UpdateAngle()
{
	// プレイヤーの角度を更新
	m_angle = atan2f(m_targetMoveDir.x, m_targetMoveDir.z);
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));
}


/// <summary>
/// アニメーション状態の更新
/// </summary>
/// <param name="prevState">現在のアニメーション状態</param>
void Player::UpdateAnimState(State prevState)
{
	// 待機状態から
	if (prevState == State::kFightIdle)
	{
		// 移動アニメーションを再生
		if(m_currentState == State::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == State::kPunch)PlayAnim(AnimKind::kPunch);
		// キックアニメーションを再生
		if (m_currentState == State::kKick)	PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == State::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// 移動状態から
	else if (prevState == State::kRun)
	{
		// 待機アニメーションを再生
		if(m_currentState == State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// パンチアニメーションを再生
		if (m_currentState == State::kPunch) PlayAnim(AnimKind::kPunch);
		// キックアニメーションを再生
		if (m_currentState == State::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == State::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// パンチ状態から
	else if (prevState == State::kPunch)
	{
		// 待機アニメーションを再生
		if (m_currentState == State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == State::kRun) PlayAnim(AnimKind::kRun);
		// キックアニメーションを再生
		if (m_currentState == State::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == State::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// キック状態から
	else if (prevState == State::kKick)
	{
		// 待機アニメーションを再生
		if (m_currentState == State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == State::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == State::kPunch) PlayAnim(AnimKind::kPunch);
		// 回避アニメーションを再生
		if (m_currentState == State::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// 回避状態から
	else if (prevState == State::kAvoid)
	{
		// 待機アニメーションを再生
		if (m_currentState == State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == State::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == State::kPunch) PlayAnim(AnimKind::kPunch);
		// キックアニメーションを再生
		if (m_currentState == State::kKick) PlayAnim(AnimKind::kKick);
	}
}


/// <summary>
/// アニメーション処理
/// </summary>
void Player::UpdateAnim()
{
	float animTotalTime; // 再生中のアニメーション時間

	// ブレンド率が1以下の場合
	if (m_animBlendRate < kAnimBlendMax)
	{
		m_animBlendRate += kAnimBlendSpeed;
		if (m_animBlendRate >= kAnimBlendMax)
		{
			m_animBlendRate = kAnimBlendMax;
		}
	}

	// 現在再生中のアニメーションの処理
	if (m_currentPlayAnim != -1)
	{
		// アニメーションの総時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_currentPlayAnim);
		if (m_currentPlayAnim == static_cast<int>(AnimKind::kPunch) || 
			m_currentPlayAnim == static_cast<int>(AnimKind::kKick))
		{
			m_currentAnimCount += kAttackAnimSpeed;
		}
		else
		{
			m_currentAnimCount += kPlayAnimSpeed;
		}

		// アニメーションの再生時間をループ
		if (m_currentAnimCount > animTotalTime)
		{
			// 攻撃アニメーションが終了したら待機状態に移行
			if (m_isAttack)
			{
				m_isAttack = false;
				m_currentState = State::kFightIdle;
				PlayAnim(AnimKind::kFightIdle);
			}

			m_currentAnimCount = static_cast<float>(fmod(m_currentAnimCount, animTotalTime));
		}

		// 再生時間を更新
		MV1SetAttachAnimTime(m_modelHandle, m_currentPlayAnim, m_currentAnimCount);
		// アニメーションのブレンド率を設定する
		MV1SetAttachAnimBlendRate(m_modelHandle, m_currentPlayAnim, m_animBlendRate);

		
	}

	// 1つ前に再生していたアニメーションの処理
	if (m_prevPlayAnim != -1)
	{
		// アニメーションの総時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_prevPlayAnim);
		if (m_prevPlayAnim == static_cast<int>(AnimKind::kPunch) ||
			m_prevPlayAnim == static_cast<int>(AnimKind::kKick))
		{
			m_prevAnimCount += kAttackAnimSpeed;
		}
		else
		{
			m_prevAnimCount += kPlayAnimSpeed;
		}

		// アニメーションの再生時間をループ
		if (m_prevPlayAnim > animTotalTime)
		{
			m_prevAnimCount = static_cast<float>(fmod(m_prevAnimCount, animTotalTime));
		}

		// 再生時間を更新
		MV1SetAttachAnimTime(m_modelHandle, m_prevPlayAnim, m_prevAnimCount);
		// アニメーションのブレンド率を設定する
		MV1SetAttachAnimBlendRate(m_modelHandle, m_prevPlayAnim, kAnimBlendMax - m_animBlendRate);
	}
}


/// <summary>
/// アニメーションを再生する
/// </summary>
/// <param name="playAnim">再生するアニメーション状態</param>
void Player::PlayAnim(AnimKind playAnimIndex)
{
	// 1つ前のアニメーションがアタッチされている場合削除する
	if (m_prevPlayAnim != -1)
	{
		MV1DetachAnim(m_modelHandle, m_prevPlayAnim);
		m_prevPlayAnim = -1;
	}

	// 現在再生中のアニメーションを1つ前に移動する
	m_prevPlayAnim = m_currentPlayAnim;
	m_prevAnimCount = m_currentAnimCount;

	// 新たにアニメーションをアタッチする
	m_currentPlayAnim = MV1AttachAnim(m_modelHandle, static_cast<int>(playAnimIndex), -1, false);
	m_currentAnimCount = 0.0f;

	// ブレンド率はPrevが有効でない場合、1.0にする
	if (m_prevPlayAnim == -1)
	{
		m_animBlendRate = kAnimBlendMax;
	}
	else
	{
		m_animBlendRate = 0.0f;
	}
}