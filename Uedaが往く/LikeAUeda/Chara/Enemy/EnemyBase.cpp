#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"

// 定数
namespace
{
	constexpr float kApproachRange = 70.0f;	// プレイヤーに近づく範囲
	constexpr int kStopMinTime = 30;		// 最小の停止時間
	constexpr int kStopMaxTime = 150;		// 最大の停止時間

	// アニメーション情報
	constexpr float kAnimBlendMax = 1.0f;	 // アニメーションブレンドの最大値
	constexpr float kAnimBlendSpeed = 0.2f;	 // アニメーションブレンドの変化速度
}


/// <summary>
/// コンストラクタ
/// </summary>
EnemyBase::EnemyBase():
	m_isMove(false),
	m_isAttack(false),
	m_stopFrame(0),
	m_currentState(EnemyState::kFightIdle)
{
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

	// 当たり判定を行って座標を保存する
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
EnemyBase::EnemyState EnemyBase::UpdateMoveParameter(Player& player, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	EnemyState nextState = m_currentState;
	
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
			if (m_stopFrame <= 0)
			{
				dir = VNorm(dir);
				moveVec = VScale(dir, m_moveSpeed);

				// 待機状態の場合
				if (m_currentState == EnemyState::kFightIdle)
				{
					nextState = EnemyState::kRun; // 移動状態にする
				}
			}
			else
			{
				m_stopFrame--;
			}
		}
		else
		{
			m_stopFrame = kStopMinTime + GetRand(kStopMaxTime);	// 停止時間をランダムで計算する
			nextState = EnemyState::kFightIdle;	// 待機状態にする
		}
	}

	return nextState;
}


/// <summary>
/// 攻撃処理
/// </summary>
/// <param name="input">入力状態</param>
/// <returns>現在の状態</returns>
EnemyBase::EnemyState EnemyBase::Attack()
{
	EnemyState nextState = m_currentState;

	// TODO:ランダムで攻撃を行う
	if (!m_isAttack)
	{
		int randNum = GetRand(10);

		// パンチ攻撃
		if (randNum <= 5)
		{
			m_isAttack = true;
			nextState = EnemyState::kPunch;
			PlayAnim(AnimKind::kPunch);
		}
		// キック攻撃
		else
		{
			m_isAttack = true;
			nextState = EnemyState::kKick;
			PlayAnim(AnimKind::kKick);
		}
	}

	return nextState;
}


/// <summary>
/// 敵の角度を更新
/// </summary>
void EnemyBase::UpdateAngle(Player& player)
{
	// 敵の位置からプレイヤーの位置のベクトルを求める
	VECTOR dir = VSub(player.GetPos(), m_pos);
	m_angle = atan2f(dir.x, dir.z);
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));
}


/// <summary>
///  プレイヤーとの当たり判定をチェックする
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="eCapPosTop">当たり判定カプセルの頂点位置</param>
/// <param name="eCapPosBottom">当たり判定カプセルの頂点位置</param>
/// <param name="eCapRadius">当たり判定カプセルの半径</param>
void EnemyBase::CheckHitPlayerColl(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius)
{
	// プレイヤーと敵の当たり判定を行う
	bool hit = HitCheck_Capsule_Capsule(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius, eCapPosTop, eCapPosBottom, eCapRadius);
	// パンチ
	bool hitPunch = HitCheck_Capsule_Capsule(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius, eCapPosTop, eCapPosBottom, eCapRadius);
	// キック
	bool hitKick = HitCheck_Capsule_Capsule(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius, eCapPosTop, eCapPosBottom, eCapRadius);

	// パンチが当たった場合
	if (hitPunch && m_currentState == EnemyState::kPunch)
	{
		// パンチが当たった場合
		player.OnDamage(m_status.punchPower);
	}
	// キックが当たった場合
	else if (hitKick && m_currentState == EnemyState::kKick)
	{
		// キックが当たった場合
		if (m_currentState == EnemyState::kKick)
		{
			player.OnDamage(m_status.kickPower);
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
	if (!hit && m_currentState == EnemyState::kGrab)
	{
		// 掴み失敗のアニメーションを再生する
	}
}


/// <summary>
/// アニメーションステートの更新
/// </summary>
/// <param name="prevState"></param>
void EnemyBase::UpdateAnimState(EnemyState prevState)
{
	// 攻撃中は状態を更新しない
	if (m_isAttack) return;

	// 待機状態から
	if (prevState == EnemyState::kFightIdle)
	{
		// 移動アニメーションを再生
		if (m_currentState == EnemyState::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == EnemyState::kPunch)PlayAnim(AnimKind::kPunch);
		// キックアニメーションを再生
		if (m_currentState == EnemyState::kKick)	PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == EnemyState::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// 移動状態から
	else if (prevState == EnemyState::kRun)
	{
		// 待機アニメーションを再生
		if (m_currentState == EnemyState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// パンチアニメーションを再生
		if (m_currentState == EnemyState::kPunch) PlayAnim(AnimKind::kPunch);
		// キックアニメーションを再生
		if (m_currentState == EnemyState::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == EnemyState::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// パンチ状態から
	else if (prevState == EnemyState::kPunch)
	{
		// 待機アニメーションを再生
		if (m_currentState == EnemyState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == EnemyState::kRun) PlayAnim(AnimKind::kRun);
		// キックアニメーションを再生
		if (m_currentState == EnemyState::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == EnemyState::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// キック状態から
	else if (prevState == EnemyState::kKick)
	{
		// 待機アニメーションを再生
		if (m_currentState == EnemyState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == EnemyState::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == EnemyState::kPunch) PlayAnim(AnimKind::kPunch);
		// 回避アニメーションを再生
		if (m_currentState == EnemyState::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// 回避状態から
	else if (prevState == EnemyState::kAvoid)
	{
		// 待機アニメーションを再生
		if (m_currentState == EnemyState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == EnemyState::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == EnemyState::kPunch) PlayAnim(AnimKind::kPunch);
		// キックアニメーションを再生
		if (m_currentState == EnemyState::kKick) PlayAnim(AnimKind::kKick);
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
			m_currentAnimCount += m_animSpeed.punch;
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
				m_currentState = EnemyState::kFightIdle;
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