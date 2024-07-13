#include "DxLib.h"
#include "Camera.h"
#include "Stage.h"
#include "EnemyBase.h"
#include "UIGauge.h"
#include "Input.h"
#include "Player.h"

// 定数
namespace
{
	// プレイヤー情報
	const char* const kfileName = "data/Model/player.mv1";	// プレイヤーのファイル名
	constexpr float kMaxHp = 100.0f;						// 最大HP
	constexpr float kMaxGauge = 100.0f;						// 最大ゲージ量
	constexpr float kPunchPower = 3.0f;						// パンチの攻撃力
	constexpr float kKickPower = 5.0f;						// キックの攻撃力
	constexpr float kMaxSpeed = 5.0f;						// プレイヤーの最大移動速度
	constexpr float kAcceleration = 0.2f;					// プレイヤーの加速度
	constexpr float kDeceleration = 0.2f;					// プレイヤーの減速度
	constexpr float kAvoidDist = 60.0f;						// 回避の距離
	constexpr float kAngleSpeed = 0.2f;						// プレイヤー角度の変化速度
	constexpr float kVelocity = 6.0f;						// ジャンプの高さ
	constexpr float kGravity = -0.25f;						// 重力
	constexpr float kScale = 0.3f;							// プレイヤーモデルの拡大率
	const VECTOR kInitDir = VGet(0.0f, 0.0f, 0.0f);			// 初期方向
	const VECTOR kInitPos = VGet(0.0f, 0.0f, -20.0f);		// 初期位置

	// コリジョン情報
	constexpr float kHitHeight = 43.0f;				// 当たり判定カプセルの高さ
	constexpr float kHitRadius = 8.0f;				// 当たり判定カプセルの半径
	constexpr float kHitAimRadius = 10.0f;			// 腕の当たり判定カプセルの長さ
	constexpr float kHitLegRadius = 10.0f;			// 足の当たり判定カプセルの長さ
	const VECTOR kArmPos = VGet(3.0f, 40.0f, 0.0f); // 腕の当たり判定位置
	const VECTOR kLegPos = VGet(3.0f, 20.0f, 0.0f); // 脚の当たり判定位置

	// アニメーション情報
	constexpr float kAnimBlendMax = 1.0f;	 // アニメーションブレンドの最大値
	constexpr float kAnimBlendSpeed = 0.2f;	 // アニメーションブレンドの変化速度
	constexpr float kPlayAnimSpeed = 0.5f;	 // 通常のアニメーションの速度
	constexpr float kAttackAnimSpeed = 0.8f; // 攻撃アニメーションの速度
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
	m_moveSpeed(0.0f),
	m_currentState(State::kFightIdle),
	m_modelHandle(-1),
	m_currentPlayAnim(-1),
	m_currentAnimCount(0.0f),
	m_prevPlayAnim(-1),
	m_prevAnimCount(0.0f),
	m_animBlendRate(kAnimBlendMax)
{
	m_modelHandle = MV1LoadModel(kfileName);
	// モデル全体のコリジョン情報のセットアップ
	MV1SetupCollInfo(m_modelHandle, -1);
}


/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
/// 初期化
/// </summary>
void Player::Init()
{
	m_pUIGauge = std::make_shared<UIGauge>();
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
	// パッド入力によって移動パラメータを設定する
	VECTOR	upMoveVec;		// 上ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	leftMoveVec;	// 左ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	moveVec;		// このフレームの移動ベクトル

	// プレイヤーの状態を更新
	State prevState = m_currentState;

	// 攻撃処理
	m_currentState = Attack(input);
	// 回避処理
	m_currentState = Avoidance(input, moveVec);
	// 移動処理
	m_currentState = UpdateMoveParameter(input, camera, upMoveVec, leftMoveVec, moveVec);

	// アニメーション状態を更新
	UpdateAnimState(prevState);

	// プレイヤーの移動方向を設定
	UpdateAngle();

	// 移動ベクトルを元にプレイヤーを移動させる
	Move(moveVec, stage);

	// アニメーション処理の更新
	UpdateAnim();

	// 当たり判定の位置更新
	UpdateCol();
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	MV1DrawModel(m_modelHandle);

	// HPゲージを表示
	m_pUIGauge->DrawPlayerHP(m_hp, kMaxHp);
	m_pUIGauge->DrawPlayerGauge(m_gauge, kMaxGauge);

#ifdef _DEBUG	// デバッグ表示
	DrawFormatString(0, 20, 0xffffff, "プレイヤー座標(%2f,%2f,%2f)", m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 40, 0xffffff, "hp:%f",m_hp);

	// 当たり判定描画
	DrawCapsule3D(m_col.hitTopPos, m_col.hitBottomPos, kHitRadius, 1, 0x0000ff, 0xffffff, false);
	DrawCapsule3D(m_col.armStartPos, m_col.armEndPos, kHitAimRadius, 1, 0xff00ff, 0xffffff, false);
	DrawCapsule3D(m_col.legStartPos, m_col.legEndPos, kHitLegRadius, 1, 0xffff00, 0xffffff, false);
#endif
}


/// <summary>
/// ダメージを受けたとき
/// </summary>
void Player::OnDamage()
{
	DrawString(0, 80, "当たった！", 0xfffffff);

	m_hp = std::min(m_hp, kMaxHp);
}


/// <summary>
/// 敵との当たり判定をチェックする
/// </summary>
/// <param name="enemy">敵の参照</param>
/// <param name="eCapPosTop">敵のカプセルの上位置</param>
/// <param name="eCapPosBottom">敵のカプセルの下位置</param>
/// <param name="CapRadius">敵の当たり判定の半径</param>
void Player::CheckHitEnemyCol(EnemyBase& enemy, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius)
{
	// 当たり判定カプセルの位置を計算する
	VECTOR pCapPosTop = VGet(m_pos.x, m_pos.y + kHitHeight, m_pos.z);

	// プレイヤーと敵の当たり判定を行う
	bool hit = HitCheck_Capsule_Capsule(pCapPosTop, m_pos, kHitRadius, eCapPosTop, eCapPosBottom, kHitRadius);
	// パンチ
	bool hitPunch = HitCheck_Capsule_Capsule(m_col.armStartPos, m_col.armEndPos, kHitAimRadius, eCapPosTop, eCapPosBottom, kHitRadius);
	// キック
	bool hitKick = HitCheck_Capsule_Capsule(m_col.legStartPos, m_col.legEndPos, kHitAimRadius, eCapPosTop, eCapPosBottom, kHitRadius);
	// キック

	// パンチが当たった場合
	if (hitPunch && m_currentState == State::kPunch)
	{
		// パンチが当たった場合
		enemy.OnDamage(kPunchPower);
		// TODO:攻撃が当たったらゲージを増やす
		m_gauge += 3.0f;

	}
	// キックが当たった場合
	else if (hitKick && m_currentState == State::kKick)
	{
		// キックが当たった場合
		if (m_currentState == State::kKick)
		{
			enemy.OnDamage(kKickPower);
			m_gauge += 5.0f;
		}
	// 攻撃中でなく、敵に当たった場合
	else if(hit)
	{
		// プレイヤーの位置を補正する
		VECTOR collisionNormal = VSub(m_pos, enemy.GetPos());
		collisionNormal = VNorm(collisionNormal);

		const float kAdj = 1.0f;
		m_pos = VAdd(m_pos, VScale(collisionNormal, kAdj));
	}
	}

	// 掴みが決まらなかった場合
	if(!hit && m_currentState == State::kGrab)
	{
		// 掴み失敗のアニメーションを再生する
	}

	// ゲージ量の調整
	m_gauge = std::min(m_gauge, kMaxHp);
}


/// <summary>
/// プレイヤーの当たり判定の位置を更新する
/// </summary>
void Player::UpdateCol()
{
	// プレイヤーの向きをもとに回転行列を取得する
	MATRIX rotationMatrix = MGetRotY(m_angle);

	// プレイヤー全体の当たり判定位置を更新
	m_col.hitTopPos = VAdd(m_pos, VTransform(VGet(0.0f, kHitHeight, 0.0f), rotationMatrix));
	m_col.hitBottomPos = m_pos;

	// 腕の当たり判定位置を更新
	VECTOR armOffset = VGet(5.0f, 40.0f, 2.0f);  // 腕のオフセット
	VECTOR armEndOffset = VGet(0.0f, 0.0f, 3.0f);  // 腕の終了位置オフセット
	m_col.armStartPos = VAdd(m_pos, VTransform(armOffset, rotationMatrix));
	m_col.armEndPos = VAdd(m_col.armStartPos, VTransform(armEndOffset, rotationMatrix));

	// 脚の当たり判定位置を更新
	VECTOR legOffset = VGet(-2.0f, -5.0f, 0.0f);  // 足のオフセット
	VECTOR legEndOffset = VGet(0.0f, 0.0f, -3.0f);  // 足の終了位置オフセット
	m_col.legStartPos = VAdd(m_pos, VTransform(legOffset, rotationMatrix));
	m_col.legEndPos = VAdd(m_col.legStartPos, VTransform(legEndOffset, rotationMatrix));
}


/// <summary>
/// プレイヤーの移動処理
/// </summary>
void Player::Move(const VECTOR& MoveVector, Stage& stage)
{
	if (fabs(MoveVector.x) > 0.0f || fabs(MoveVector.z) > 0.0f)
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
/// 攻撃処理
/// </summary>
/// <param name="input">入力処理</param>
/// <returns>現在の状態</returns>
Player::State Player::Attack(const Input& input)
{
	State nextState = m_currentState;

	if (!m_isAttack)
	{
		// パンチ攻撃
		if (input.IsTriggered("punch"))
		{
			m_isAttack = true;
			nextState = State::kPunch;
			PlayAnim(AnimKind::kPunch);
		}
		// キック攻撃
		else if (input.IsTriggered("kick"))
		{
			m_isAttack = true;
			nextState = State::kKick;
			PlayAnim(AnimKind::kKick);
		}
	}

	return nextState;
}


/// <summary>
/// 回避処理
/// </summary>
/// <param name="input">入力処理</param>
/// <returns>現在の状態</returns>
Player::State Player::Avoidance(const Input& input, VECTOR& moveVec)
{
	// 攻撃中の場合は何もしない
	if (m_currentState == State::kPunch || m_currentState == State::kKick) return m_currentState;

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

	// 攻撃中でない場合
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
	// 攻撃中は状態を更新しない
	if (m_isAttack) return;

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
		if (m_isAttack)
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
		if (m_isAttack)
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