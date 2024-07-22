#include "DxLib.h"
#include "Camera.h"
#include "Stage.h"
#include "EnemyBase.h"
#include "UIGauge.h"
#include "Input.h"
#include "LoadData.h"
#include "Player.h"

// 定数
namespace
{
	// プレイヤー情報
	const char* const kfileName = "data/Model/player.mv1";	// プレイヤーのファイル名
	constexpr float kMaxGauge = 100.0f;						// 最大ゲージ量
	constexpr float kGaugeCharge = 0.3f;					// 1回の攻撃で増えるゲージ量
	constexpr float kAcceleration = 0.7f;					// プレイヤーの加速度
	constexpr float kDeceleration = 0.7f;					// プレイヤーの減速度
	constexpr int kMaxPunchCount = 3;						// 最大コンボ数
	constexpr int kPunchComboTime = 40;						// パンチコンボの入力受付時間
	constexpr int kPunchCoolTime = 20;						// パンチできるようになるまでの時間
	constexpr float kAvoidDist = 30.0f;						// 回避の距離
	constexpr int kMaxAvoidCount = 3;						// 連続で回避できる回数
	constexpr int kAvoidCoolTime = 30;						// 回避できるようになるまでの時間
	constexpr float kFightWalkSpeed = 1.8f;					// 構え中の移動速度
	constexpr float kGuardAnimTime = 10.0f;					// ガード中のアニメーションを止める時間
	constexpr float kAngleSpeed = 0.2f;						// プレイヤー角度の変化速度
	constexpr float kVelocity = 6.0f;						// ジャンプの高さ
	constexpr float kGravity = -0.25f;						// 重力
	constexpr float kScale = 0.3f;							// プレイヤーモデルの拡大率
	const VECTOR kInitDir = VGet(0.0f, 0.0f, 0.0f);			// 初期方向
	const VECTOR kInitPos = VGet(0.0f, 0.0f, -20.0f);		// 初期位置

	// アニメーション情報
	constexpr float kAnimBlendMax = 1.0f;	 // アニメーションブレンドの最大値
	constexpr float kAnimBlendSpeed = 0.2f;	 // アニメーションブレンドの変化速度
}


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player():
	m_gauge(0.0f),
	m_punchCount(0),
	m_punchComboTime(0),
	m_punchCoolTime(0),
	m_avoidCount(0),
	m_avoidCoolTime(0),
	m_isMove(false),
	m_isFighting(false),
	m_targetMoveDir(kInitDir),
	m_currentState(PlayerState::kFightIdle)
{
	// キャラクター情報を読み込む
	m_pLoadData = std::make_shared<LoadData>(*this, static_cast<int>(CharaType::kPlayer));

	m_hp = m_status.maxHp;
	m_pos = kInitPos;
	m_moveSpeed = 0.0f;
	m_angle = 0.0f;
	m_modelHandle = MV1LoadModel(kfileName);

	m_animBlendRate = kAnimBlendMax;

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
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	MV1SetPosition(m_modelHandle, m_pos);
	PlayAnim(AnimKind::kFightIdle);
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力コマンド</param>
/// <param name="stage">ステージ情報参照</param>
void Player::Update(const Input& input, const Camera& camera, EnemyBase& enemy, Stage& stage)
{
	// パッド入力によって移動パラメータを設定する
	VECTOR	upMoveVec;		// 上ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	leftMoveVec;	// 左ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	moveVec;		// このフレームの移動ベクトル

	// プレイヤーの状態を更新
	PlayerState prevState = m_currentState;

	// 攻撃処理
	m_currentState = Punch(input);
	m_currentState = Kick(input);
	// 回避処理
	m_currentState = Avoidance(input, moveVec);
	// 構え処理
	m_currentState = Fighting(input);
	// ガード処理
	m_currentState = Guard(input);
	// 移動処理
	m_currentState = UpdateMoveParameter(input, camera, upMoveVec, leftMoveVec, moveVec);

	// エネミーとの当たり判定をチェックする
	enemy.CheckHitPlayerCol(*this, VGet(m_pos.x, m_pos.y + m_colInfo.bodyHeight, m_pos.z), m_pos, m_colInfo.bodyRadius);

	// アニメーション状態を更新
	UpdateAnimState(prevState);

	// プレイヤーの移動方向を設定
	UpdateAngle(enemy);

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
	m_pUIGauge->DrawPlayerHP(m_hp, m_status.maxHp);
	m_pUIGauge->DrawPlayerGauge(m_gauge, kMaxGauge);

#ifdef _DEBUG	// デバッグ表示
	DrawFormatString(0, 20, 0xffffff, "プレイヤー座標(%0.2f,%0.2f,%0.2f)", m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 40, 0xffffff, "hp:%0.2f",m_hp);

	// 当たり判定描画
	DrawCapsule3D(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius, 1, 0x0000ff, 0xffffff, false);	// 全身
	DrawCapsule3D(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius, 1, 0xff00ff, 0xffffff, false);		// 腕
	DrawCapsule3D(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius, 1, 0xffff00, 0xffffff, false);		// 脚
#endif
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
	// プレイヤーと敵の当たり判定を行う
	bool hit = HitCheck_Capsule_Capsule(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius, eCapPosTop, eCapPosBottom, eCapRadius);
	// パンチ
	bool hitPunch = HitCheck_Capsule_Capsule(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius, eCapPosTop, eCapPosBottom, eCapRadius);
	// キック
	bool hitKick = HitCheck_Capsule_Capsule(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius, eCapPosTop, eCapPosBottom, eCapRadius);

	// パンチが当たった場合
	if (hitPunch && m_currentState == PlayerState::kPunch)
	{
		// パンチが当たった場合
		enemy.OnDamage(m_status.punchPower);
		// TODO:攻撃が当たったらゲージを増やす
		m_gauge += kGaugeCharge;

	}
	// キックが当たった場合
	else if (hitKick && m_currentState == PlayerState::kKick)
	{
		// キックが当たった場合
		if (m_currentState == PlayerState::kKick)
		{
			enemy.OnDamage(m_status.kickPower);
			m_gauge += kGaugeCharge;
		}
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

	// 掴みが決まらなかった場合
	if(!hit && m_currentState == PlayerState::kGrab)
	{
		// 掴み失敗のアニメーションを再生する
	}

	// ゲージ量の調整
	m_gauge = std::min(m_gauge, kMaxGauge);
}


/// <summary>
/// プレイヤーの移動処理
/// </summary>
/// <param name="MoveVec">移動ベクトル</param>
/// <param name="stage">ステージ参照</param>
void Player::Move(const VECTOR& moveVec, Stage& stage)
{
	if (fabs(moveVec.x) > 0.0f || fabs(moveVec.z) > 0.0f)
	{
		m_isMove = true;
	}
	else
	{
		m_isMove = false;
	}

	// 当たり判定を行って座標を保存する
	m_pos = stage.CheckPlayerCol(*this, moveVec);

	// プレイヤーの座標を更新する
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// パンチ攻撃処理
/// </summary>
/// <param name="input">入力処理</param>
/// <returns>現在の状態</returns>
Player::PlayerState Player::Punch(const Input& input)
{
	PlayerState nextState = m_currentState;

	// 攻撃中はスキップ
	if (m_isAttack) return nextState;

	// パンチできない場合
	if (m_punchCoolTime > 0)
	{
		m_punchCoolTime--;
		return nextState;
	}

	// コンボ入力の受付時間の更新
	m_punchComboTime--;

	if (input.IsTriggered("punch"))
	{
		// コンボ入力受付時間内にボタンが押された場合
		if (m_punchComboTime > 0)
		{
			m_punchCount++;
		}
		else
		{
			m_punchCount = 0;
		}

		// コンボ数が最大になった場合
		if (m_punchCount > kMaxPunchCount)
		{
			m_punchCount = 0;
			m_punchCoolTime = kPunchCoolTime;	// クールダウンタイムを設定
		}
		else
		{
			m_punchComboTime = kPunchComboTime; // コンボ入力の受付時間をリセット
			m_isAttack = true;
			nextState = PlayerState::kPunch;
			PlayAnim(AnimKind::kPunch);
		}
	}

	return nextState;
}


/// <summary>
/// キック攻撃処理
/// </summary>
/// <param name="input">入力処理</param>
/// <returns>現在の状態</returns>
Player::PlayerState Player::Kick(const Input& input)
{
	PlayerState nextState = m_currentState;

	// 攻撃中はスキップ
	if (m_isAttack) return nextState;

	// キック攻撃
	else if (input.IsTriggered("kick"))
	{
		m_isAttack = true;
		nextState = PlayerState::kKick;
		PlayAnim(AnimKind::kKick);
	}

	return nextState;
}


/// <summary>
/// 回避処理
/// </summary>
/// <param name="input">入力処理</param>
/// <returns>現在の状態</returns>
Player::PlayerState Player::Avoidance(const Input& input, VECTOR& moveVec)
{
	PlayerState nextState = m_currentState;

	// 回避できない場合
	if (m_avoidCoolTime > 0)
	{
		m_avoidCoolTime--;
		return nextState;
	}

	if (input.IsTriggered("avoidance"))
	{
		m_avoidCount++;
		// 回避数が最大になった場合
		if (m_avoidCount > kMaxAvoidCount)
		{
			m_avoidCount = 0;
			m_avoidCoolTime = kAvoidCoolTime;	// クールダウンタイムを設定
		}
		else
		{
			nextState = PlayerState::kAvoid;
			// 移動ベクトルを設定する
			VECTOR backMoveVec = VScale(m_targetMoveDir, -1.0f);
			m_pos = VAdd(m_pos, VScale(backMoveVec, kAvoidDist));
		}
	}

	return nextState;
}


/// <summary>
/// 構え中処理
/// </summary>
/// <param name="input">入力処理</param>
/// <param name="enemy">敵情報参照</param>
/// <returns>現在の状態</returns>
Player::PlayerState Player::Fighting(const Input& input)
{
	PlayerState nextState = m_currentState;

	if (input.IsTriggered("fighting"))
	{
		m_isFighting = true;
		nextState = PlayerState::kFightWalk;
		PlayAnim(AnimKind::kFightWalk);
	}
	else if(input.IsReleased("fighting"))
	{
		m_isFighting = false;
		nextState = PlayerState::kFightIdle;
		PlayAnim(AnimKind::kFightIdle);
	}

	return nextState;
}


/// <summary>
/// ガード処理
/// </summary>
/// <param name="input">入力処理</param>
/// <returns>現在の状態</returns>
Player::PlayerState Player::Guard(const Input& input)
{
	PlayerState nextState = m_currentState;

	if (input.IsTriggered("guard"))
	{
		m_isGuard = true;
		nextState = PlayerState::kGuard;
		PlayAnim(AnimKind::kGuard);
	}
	else if (input.IsReleased("guard"))
	{
		m_isGuard = false;
		nextState = PlayerState::kFightIdle;
		PlayAnim(AnimKind::kFightIdle);
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
Player::PlayerState Player::UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	PlayerState nextState = m_currentState;

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

	// 攻撃中、ガード中でない場合
	if (!m_isAttack && !m_isGuard)
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
			if (m_currentState == PlayerState::kFightIdle)
			{
				nextState = PlayerState::kRun; // 移動状態にする
			}

			// プレイヤーが向く方向を設定する
			m_targetMoveDir = VNorm(moveVec);

			// プレイヤーの加速度を設定する
			if (m_moveSpeed < m_status.maxMoveSpeed)
			{
				m_moveSpeed += kAcceleration;
				m_moveSpeed = (std::min)(m_moveSpeed, m_status.maxMoveSpeed);
			}
			// プレイヤーの移動ベクトルを設定する
			// 構え中は移動速度を遅くする
			if (m_isFighting)
			{
				moveVec = VScale(m_targetMoveDir, kFightWalkSpeed);
			}
			else
			{
				moveVec = VScale(m_targetMoveDir, m_moveSpeed);
			}
		}
		// 移動しない場合
		else
		{
			// 移動状態の場合
			if (m_currentState == PlayerState::kRun)
			{
				// 待機状態にする
				nextState = PlayerState::kFightIdle;
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
void Player::UpdateAngle(EnemyBase& enemy)
{
	// プレイヤーの角度を更新
	if (m_isFighting)
	{
		// 敵の方を見続ける
		VECTOR dir = VSub(enemy.GetPos(), m_pos);
		m_angle = atan2f(dir.x, dir.z);
	}
	else
	{
		m_angle = atan2f(m_targetMoveDir.x, m_targetMoveDir.z);
	}
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));
}


/// <summary>
/// アニメーション状態の更新
/// </summary>
/// <param name="prevState">現在のアニメーション状態</param>
void Player::UpdateAnimState(PlayerState prevState)
{
	// 攻撃中は状態を更新しない
	if (m_isAttack) return;

	// 待機状態から
	if (prevState == PlayerState::kFightIdle)
	{
		// 移動アニメーションを再生
		if(m_currentState == PlayerState::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == PlayerState::kPunch)PlayAnim(AnimKind::kPunch);
		// キックアニメーションを再生
		if (m_currentState == PlayerState::kKick)	PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == PlayerState::kAvoid) PlayAnim(AnimKind::kAvoid);
		// 構えアニメーションを再生
		if(m_currentState == PlayerState::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// ガードアニメーションを再生
		if (m_currentState == PlayerState::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// 移動状態から
	else if (prevState == PlayerState::kRun)
	{
		// 待機アニメーションを再生
		if(m_currentState == PlayerState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// パンチアニメーションを再生
		if (m_currentState == PlayerState::kPunch) PlayAnim(AnimKind::kPunch);
		// キックアニメーションを再生
		if (m_currentState == PlayerState::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == PlayerState::kAvoid) PlayAnim(AnimKind::kAvoid);
		// 構えアニメーションを再生
		if (m_currentState == PlayerState::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// ガードアニメーションを再生
		if (m_currentState == PlayerState::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// パンチ状態から
	else if (prevState == PlayerState::kPunch)
	{
		// 待機アニメーションを再生
		if (m_currentState == PlayerState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == PlayerState::kRun) PlayAnim(AnimKind::kRun);
		// キックアニメーションを再生
		if (m_currentState == PlayerState::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == PlayerState::kAvoid) PlayAnim(AnimKind::kAvoid);
		// 構えアニメーションを再生
		if (m_currentState == PlayerState::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// ガードアニメーションを再生
		if (m_currentState == PlayerState::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// キック状態から
	else if (prevState == PlayerState::kKick)
	{
		// 待機アニメーションを再生
		if (m_currentState == PlayerState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == PlayerState::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == PlayerState::kPunch) PlayAnim(AnimKind::kPunch);
		// 回避アニメーションを再生
		if (m_currentState == PlayerState::kAvoid) PlayAnim(AnimKind::kAvoid);
		// 構えアニメーションを再生
		if (m_currentState == PlayerState::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// ガードアニメーションを再生
		if (m_currentState == PlayerState::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// 回避状態から
	else if (prevState == PlayerState::kAvoid)
	{
		// 待機アニメーションを再生
		if (m_currentState == PlayerState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == PlayerState::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == PlayerState::kPunch) PlayAnim(AnimKind::kPunch);
		// キックアニメーションを再生
		if (m_currentState == PlayerState::kKick) PlayAnim(AnimKind::kKick);
		// 構えアニメーションを再生
		if (m_currentState == PlayerState::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// ガードアニメーションを再生
		if (m_currentState == PlayerState::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// 構え状態から
	else if (prevState == PlayerState::kFightWalk)
	{
		// 待機アニメーションを再生
		if (m_currentState == PlayerState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == PlayerState::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == PlayerState::kPunch) PlayAnim(AnimKind::kPunch);
		// キックアニメーションを再生
		if (m_currentState == PlayerState::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == PlayerState::kAvoid) PlayAnim(AnimKind::kAvoid);
		// ガードアニメーションを再生
		if (m_currentState == PlayerState::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// ガード状態から
	else if (prevState == PlayerState::kGuard)
	{
		// 待機アニメーションを再生
		if (m_currentState == PlayerState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == PlayerState::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == PlayerState::kPunch) PlayAnim(AnimKind::kPunch);
		// キックアニメーションを再生
		if (m_currentState == PlayerState::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == PlayerState::kAvoid) PlayAnim(AnimKind::kAvoid);
		// 構えアニメーションを再生
		if (m_currentState == PlayerState::kFightWalk) PlayAnim(AnimKind::kFightWalk);
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
		m_animBlendRate = std::min(m_animBlendRate, kAnimBlendMax);
	}

	// 現在再生中のアニメーションの処理
	if (m_currentPlayAnim != -1)
	{
		// アニメーションの総時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_currentPlayAnim);

		// アニメーションによって再生スピードを変える
		if (m_currentState == PlayerState::kPunch)
		{
			m_currentAnimCount += m_animSpeed.punch;
		}
		else if (m_currentState == PlayerState::kKick)
		{
			m_currentAnimCount += m_animSpeed.kick;
		}
		else if(m_currentState == PlayerState::kAvoid)
		{
			m_currentAnimCount += m_animSpeed.avoid;
		}
		else if (m_currentState == PlayerState::kFightWalk)
		{
			// 移動時のみアニメーションを再生
			if (m_isMove)
			{
				m_currentAnimCount += m_animSpeed.fightWalk;
			}
			else
			{
				m_currentAnimCount = 0.0f;
			}
		}
		else if (m_currentState == PlayerState::kGuard)
		{
			// 一度のみアニメーションを再生
			m_currentAnimCount += m_animSpeed.guard;
			m_currentAnimCount = std::min(m_currentAnimCount, kGuardAnimTime);

			// ガードアニメーションが終わったら待機状態に移行
			if (!m_isGuard)
			{
				m_currentState = PlayerState::kFightIdle;
				PlayAnim(AnimKind::kFightIdle);
			}
		}
		else
		{
			m_currentAnimCount += m_animSpeed.fightIdle;
		}

		
		// パンチコンボの場合
		if (m_currentAnimCount >= kPunchComboTime && m_punchCount > 0 && m_currentState == PlayerState::kPunch)
		{
			// パンチコンボの場合
			m_currentAnimCount = 0.0f;
			m_punchCount--;
			PlayAnim(AnimKind::kPunch);
		}
		if (m_currentAnimCount > animTotalTime)
		{
			// 攻撃アニメーションが終了したら待機状態に移行
			if (m_isAttack)
			{
				m_isAttack = false;
				m_currentState = PlayerState::kFightIdle;
				PlayAnim(AnimKind::kFightIdle);
			}
			// 回避アニメーションが終わったら待機状態に移行
			else if (m_currentState == PlayerState::kAvoid)
			{
				m_currentState = PlayerState::kFightIdle;
				PlayAnim(AnimKind::kFightIdle);
			}
			else
			{
				// アニメーションの再生時間をループ
				m_currentAnimCount = static_cast<float>(fmod(m_currentAnimCount, animTotalTime));
			}
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
			m_prevAnimCount += m_animSpeed.punch;
		}
		else
		{
			m_prevAnimCount += m_animSpeed.fightIdle;
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