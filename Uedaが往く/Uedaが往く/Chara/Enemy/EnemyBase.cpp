#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"

// 定数
namespace
{
	constexpr float kApproachRange = 70.0f;	 // プレイヤーに近づく範囲
	constexpr float kAttackRange = 100.0f;	 // プレイヤーを攻撃する範囲
	constexpr int kStopMinTime = 30;		 // 最小の停止時間
	constexpr int kStopMaxTime = 150;		 // 最大の停止時間

	constexpr int kMaxProb = 100;			 // 最大確率%
	constexpr int kChangeAngleProb = 30;	 // 角度を更新する確率%
	constexpr int kChangeAngleFrame = 30;	 // 角度を更新するフレーム数

	// アニメーション情報
	constexpr float kAnimBlendMax = 1.0f;	 // アニメーションブレンドの最大値
	constexpr float kAnimBlendSpeed = 0.2f;	 // アニメーションブレンドの変化速度
}


/// <summary>
/// コンストラクタ
/// </summary>
EnemyBase::EnemyBase() :
	m_isMove(false),
	m_isAttack(false),
	m_stopTime(0),
	m_angleIntervalTime(0),
	m_intervalTime(0)
{
	m_currentState = CharacterBase::State::kFightIdle;
}


/// <summary>
/// デストラクタ
/// </summary>
EnemyBase::~EnemyBase()
{
}


/// <summary>
/// 移動処理
/// </summary>
/// <param name="MoveVec"></param>
/// <param name="stage"></param>
void EnemyBase::Move(const VECTOR& moveVec, Player& player, Stage& stage)
{
	if (fabs(moveVec.x) > 0.0f || fabs(moveVec.z) > 0.0f)
	{
		m_isMove = true;
	}
	else
	{
		m_isMove = false;
	}

	// ステージと当たり判定を行って座標を保存する
	m_pos = stage.CheckEnemyCol(*this, moveVec);

	// プレイヤーの座標を更新する
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// 移動パラメータを設定する
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="upMoveVec">上方向への移動ベクトル</param>
/// <param name="leftMoveVec">左方向への移動ベクトル</param>
/// <param name="moveVec">移動ベクトル</param>
/// <returns>現在の状態</returns>
EnemyBase::CharacterBase::State EnemyBase::UpdateMoveParameter(Player& player, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	CharacterBase::State nextState = m_currentState;
	
	// このフレームでの移動ベクトルを初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// 攻撃中でない場合
	if (!m_isAttack)
	{
		// エネミーとプレイヤーの距離を計算
		VECTOR dir = VSub(player.GetPos(), m_pos);
		float distance = VSize(dir);

		// プレイヤーが一定距離離れた場合
		if (distance > kApproachRange)
		{
			// 数秒たったらエネミーを移動させる
			if (m_stopTime <= 0)
			{
				dir = VNorm(dir);
				moveVec = VScale(dir, m_moveSpeed);

				// 待機状態の場合
				if (m_currentState == CharacterBase::State::kFightIdle)
				{
					nextState = CharacterBase::State::kRun; // 移動状態にする
				}
			}
			else
			{
				m_stopTime--;
			}
		}
		// プレイヤーが攻撃範囲に入った場合
		else if(distance <= kAttackRange)
		{
			nextState = CharacterBase::State::kKick;	// 攻撃状態にする
		}
		else
		{
			m_stopTime = kStopMinTime + GetRand(kStopMaxTime);	// 停止時間をランダムで計算する
			nextState = CharacterBase::State::kFightIdle;	// 待機状態にする
		}
	}

	return nextState;
}


/// <summary>
/// パンチ攻撃
/// </summary>
void EnemyBase::Punch()
{
	m_isAttack = true;
	m_currentState = CharacterBase::State::kPunch1;
	PlayAnim(AnimKind::kPunch1);
}


/// <summary>
/// キック攻撃
/// </summary>
void EnemyBase::kick()
{
	m_isAttack = true;
	m_currentState = CharacterBase::State::kKick;
	PlayAnim(AnimKind::kKick);
}


/// <summary>
/// 敵の角度を更新
/// </summary>
void EnemyBase::UpdateAngle(Player& player)
{
	m_angleIntervalTime++;

	// 敵の位置からプレイヤー位置までのベクトルを求める
	VECTOR dir = VSub(player.GetPos(), m_pos);

	// 一定時間たったらエネミーの角度を更新する
	if (m_angleIntervalTime >= kChangeAngleFrame)
	{
		// ランダムでプレイヤーの方向を向く
		int randNum = GetRand(kMaxProb);
		if (randNum <= kChangeAngleProb)
		{
			m_angle = atan2f(dir.x, dir.z);
		}
		m_angleIntervalTime = 0;
	}

	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));
}


/// <summary>
/// プレイヤーとの当たり判定をチェックする
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="eCapPosTop">当たり判定カプセルの頂点位置</param>
/// <param name="eCapPosBottom">当たり判定カプセルの頂点位置</param>
/// <param name="eCapRadius">当たり判定カプセルの半径</param>
void EnemyBase::CheckHitPlayerCol(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius)
{
	// プレイヤーと敵の当たり判定を行う
	bool hit = HitCheck_Capsule_Capsule(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius, eCapPosTop, eCapPosBottom, eCapRadius);
	// パンチ
	bool hitPunch = HitCheck_Capsule_Capsule(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius, eCapPosTop, eCapPosBottom, eCapRadius);
	// キック
	bool hitKick = HitCheck_Capsule_Capsule(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius, eCapPosTop, eCapPosBottom, eCapRadius);

	// プレイヤーとエネミーの位置ベクトルを求める
	VECTOR pToEVec = VSub(m_pos, player.GetPos());
	pToEVec = VNorm(pToEVec);
	// 背後から攻撃したか
	bool isBackAttack = VDot(player.GetDir(), pToEVec) < 0.0f;

	// パンチが当たった場合
	if (hitPunch && m_currentState == CharacterBase::State::kPunch1)
	{
		// プレイヤーがガードしていないか、背後から攻撃した場合
		if (isBackAttack || !player.GetIsGuard())
		{
			player.OnDamage(m_status.punchPower);
		}
		else
		{
			player.OnDamage(0.0f);
		}
	}
	// キックが当たった場合
	else if (hitKick && m_currentState == CharacterBase::State::kKick)
	{
		// キックが当たった場合
		if (player.GetIsGuard())
		{
			player.OnDamage(m_status.kickPower);
		}
		else
		{
			player.OnDamage(0.0f);
		}
	}
	// 攻撃中でなく、プレイヤーに当たった場合
	else if (hit)
	{
		// エネミーの位置を補正する
		VECTOR collisionNormal = VSub(m_pos, player.GetPos());
		collisionNormal = VNorm(collisionNormal);

		const float kAdj = 1.0f;
		m_pos = VAdd(m_pos, VScale(collisionNormal, kAdj));
	}

	// 掴みが決まらなかった場合
	if (!hit && m_currentState == CharacterBase::State::kGrab)
	{
		// 掴み失敗のアニメーションを再生する
	}
}


/// <summary>
/// アニメーション処理
/// </summary>
void EnemyBase::UpdateAnim()
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
			m_currentAnimCount += m_animSpeed.punch1;
		}
		else
		{
			m_currentAnimCount += m_animSpeed.fightIdle;
		}

		// アニメーションの再生時間をループ
		if (m_currentAnimCount > animTotalTime)
		{
			// 攻撃アニメーションが終了したら待機状態に移行
			if (m_isAttack)
			{
				m_isAttack = false;
				m_currentState = CharacterBase::State::kFightIdle;
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
			m_prevAnimCount += m_animSpeed.punch1;
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