#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"
#include <fstream>
#include <sstream>

// 定数
namespace
{
	constexpr float kApproachRange = 70.0f;	 // プレイヤーに近づく範囲
	constexpr float kAttackRange = 100.0f;	 // プレイヤーを攻撃する範囲
	constexpr int kStopMinTime = 30;		 // 最小の停止時間
	constexpr int kStopMaxTime = 150;		 // 最大の停止時間

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
/// <param name="MoveVec">移動量</param>
/// <param name="stage">ステージ情報参照</param>
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
		//else if(distance <= kAttackRange)
		//{
		//	nextState = CharacterBase::State::kKick;	// 攻撃状態にする
		//}
		else
		{
			m_stopTime = kStopMinTime + GetRand(kStopMaxTime);	// 停止時間をランダムで計算する
			nextState = CharacterBase::State::kFightIdle;		// 待機状態にする
		}
	}

	return nextState;
}


/// <summary>
/// パンチ攻撃
/// </summary>
void EnemyBase::Punch()
{
	// 攻撃中はスキップ
	if (m_isAttack) return;

	// パンチできない場合
	if (m_punchCoolTime > 0)
	{
		m_punchCoolTime--;
		return;
	}

	// コンボ入力の受付時間の更新
	m_punchComboTime--;

	// コンボ入力受付時間内にボタンが押された場合
	if (m_punchComboTime > 0)
	{
		m_punchCount++;
	}
	else
	{
		m_punchCount = 0;
	}

	// コンボ数によってパンチを変える
	switch (m_punchCount)
	{
	case 0:
		m_punchComboTime = m_status.punchReceptionTime; // コンボ入力の受付時間をリセット
		m_isAttack = true;
		m_isFighting = false;
		m_currentState = CharacterBase::State::kPunch1;
		PlayAnim(AnimKind::kPunch1);
		break;
	case 1:
		m_punchComboTime = m_status.punchReceptionTime;
		m_isAttack = true;
		m_isFighting = false;
		m_currentState = CharacterBase::State::kPunch2;
		PlayAnim(AnimKind::kPunch2);
		break;
	case 2:
		m_punchComboTime = m_status.punchReceptionTime;
		m_isAttack = true;
		m_isFighting = false;
		m_currentState = CharacterBase::State::kPunch3;
		PlayAnim(AnimKind::kPunch3);
		break;
	case 3:
		m_punchCount = 0;
		m_punchCoolTime = m_status.punchCoolTime;	// クールダウンタイムを設定
		break;
	default:
		break;
	}
}


/// <summary>
/// キック攻撃
/// </summary>
void EnemyBase::kick()
{
	//m_isAttack = true;
	//m_currentState = CharacterBase::State::kKick;
	//PlayAnim(AnimKind::kKick);

	// 攻撃中はスキップ
	if (m_isAttack) return;

	// キック攻撃
	m_isAttack = true;
	m_isFighting = false;
	m_currentState = CharacterBase::State::kKick;
	PlayAnim(AnimKind::kKick);
}


/// <summary>
/// 回避処理
/// </summary>
/// <param name="moveVec">移動ベクトル</param>
void EnemyBase::Avoidance(VECTOR& moveVec)
{
	// 回避できない場合
	if (m_avoidCoolTime > 0)
	{
		m_avoidCoolTime--;
		return;
	}

	m_isFighting = false;
	m_avoidCount++;
	// 回避数が最大になった場合
	if (m_avoidCount > m_status.maxAvoidCount)
	{
		m_avoidCount = 0;
		m_avoidCoolTime = m_status.avoidCoolTime;	// クールダウンタイムを設定
	}
	else
	{
		m_currentState = CharacterBase::State::kAvoid;
		// 移動ベクトルを設定する
		//VECTOR backMoveVec = VScale(m_targetMoveDir, -1.0f);
		//m_pos = VAdd(m_pos, VScale(backMoveVec, m_status.avoidDist));
	}
}


/// <summary>
/// 構え処理
/// </summary>
void EnemyBase::Fighting()
{
	m_isFighting = true;
	m_currentState = CharacterBase::State::kFightWalk;
	PlayAnim(AnimKind::kFightWalk);
}


/// <summary>
/// ガード処理
/// </summary>
void EnemyBase::Guard()
{
	m_isGuard = true;
	m_currentState = CharacterBase::State::kGuard;
	PlayAnim(AnimKind::kGuard);
}


/// <summary>
/// ガード状態を解除
/// </summary>
void EnemyBase::OffGuard()
{
	m_isGuard = false;
	m_currentState = CharacterBase::State::kFightIdle;
	PlayAnim(AnimKind::kFightIdle);
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
	if (m_angleIntervalTime >= m_enemyInfo.changeAngleFrame)
	{
		// ランダムでプレイヤーの方向を向く
		int randNum = GetRand(m_enemyInfo.maxProb);
		if (randNum <= m_enemyInfo.changeAngleProb)
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
		if (!player.GetIsGuard())
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