#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "Input.h"
#include "EnemyBase.h"
#include <fstream>
#include <sstream>

// 定数
namespace
{
	// アニメーション情報
	constexpr float kAnimBlendMax = 1.0f;	 // アニメーションブレンドの最大値
	constexpr float kAnimBlendSpeed = 0.2f;	 // アニメーションブレンドの変化速度
}


/// <summary>
/// コンストラクタ
/// </summary>
EnemyBase::EnemyBase() :
	m_stopTime(0),
	m_angleIntervalTime(0),
	m_intervalTime(0),
	m_eToPDirVec(VGet(0.0f, 0.0f, 0.0f))
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
/// 敵の状態を更新する
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="upMoveVec">上方向への移動ベクトル</param>
/// <param name="leftMoveVec">左方向への移動ベクトル</param>
/// <param name="moveVec">移動ベクトル</param>
/// <returns>現在の状態</returns>
EnemyBase::CharacterBase::State EnemyBase::UpdateState(Player& player, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	CharacterBase::State nextState = m_currentState;

	// このフレームでの移動ベクトルを初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// 攻撃中または移動中は状態を更新しない
	bool isKeepState = m_intervalTime > 0 || m_isAttack || m_isMove || m_isGuard;
	if (isKeepState) return nextState;

	// エネミーとプレイヤーの距離を計算
	float distance = VSize(m_eToPDirVec);

	// プレイヤーが一定距離離れた場合
	if (distance > m_enemyInfo.approachRange)
	{
		// 数秒たったらプレイヤーに近づく
		if (m_stopTime < 0)
		{
			m_eToPDirVec = VNorm(m_eToPDirVec);
			moveVec = VScale(m_eToPDirVec, m_moveSpeed);

			// 待機状態の場合
			nextState = CharacterBase::State::kRun; // 移動状態にする
		}
		else
		{
			m_stopTime--;
		}
	}

	// プレイヤーが攻撃範囲に入った場合
	else if (distance <= m_enemyInfo.attackRange)
	{
		// 確率で攻撃を行う
		int randNum = GetRand(m_enemyInfo.maxProb);
		// キック攻撃
		if (randNum <= m_enemyInfo.kickProb)
		{
			nextState = kick();
		}
		// パンチ攻撃
		else if (randNum <= m_enemyInfo.kickProb + m_enemyInfo.punchProb)
		{
			nextState = Punch();
		}
		// 回避
		else if (randNum <= m_enemyInfo.kickProb + m_enemyInfo.punchProb + m_enemyInfo.avoidProb)
		{
			nextState = Avoid();
		}
		// ガード
		else if (randNum <= m_enemyInfo.kickProb + m_enemyInfo.punchProb + m_enemyInfo.avoidProb + m_enemyInfo.guardProb)
		{
			nextState = Guard();
		}
		// 待機状態
		else
		{
			nextState = Fighting();
		}
	}
	else
	{
		m_stopTime = m_enemyInfo.minStopTime + GetRand(m_enemyInfo.maxStopTime);	// プレイヤーに近づくまでの時間をランダムで計算する
		nextState = CharacterBase::State::kFightIdle;								// 待機状態にする
	}

	return nextState;
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
/// パンチ攻撃
/// </summary>
/// <returns>現在の状態</returns>
CharacterBase::State EnemyBase::Punch()
{
	CharacterBase::State nextState = m_currentState;

	// パンチできない場合
	if (m_punchCoolTime > 0)
	{
		m_punchCoolTime--;
		return m_currentState;
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
		PlayAnim(AnimKind::kPunch1);
		nextState = CharacterBase::State::kPunch1;
		break;
	case 1:
		m_punchComboTime = m_status.punchReceptionTime;
		m_isAttack = true;
		m_isFighting = false;
		PlayAnim(AnimKind::kPunch2);
		nextState = CharacterBase::State::kPunch2;
		break;
	case 2:
		m_punchComboTime = m_status.punchReceptionTime;
		m_isAttack = true;
		m_isFighting = false;
		PlayAnim(AnimKind::kPunch3);
		nextState = CharacterBase::State::kPunch3;
		break;
	case 3:
		m_isAttack = false;
		m_punchCount = 0;
		m_punchCoolTime = m_status.punchCoolTime;	// クールダウンタイムを設定
		nextState = CharacterBase::State::kFightIdle;
		break;
	default:
		break;
	}

	return nextState;
}


/// <summary>
/// キック攻撃
/// </summary>
/// <returns>現在の状態</returns>
CharacterBase::State EnemyBase::kick()
{
	// キック攻撃
	m_isAttack = true;
	m_isFighting = false;
	PlayAnim(AnimKind::kKick);
	return CharacterBase::State::kKick;
}


/// <summary>
/// 回避処理
/// </summary>
/// <param name="moveVec">移動ベクトル</param>
CharacterBase::State EnemyBase::Avoid()
{
	// 回避できない場合
	if (m_avoidCoolTime > 0)
	{
		m_avoidCoolTime--;
		return m_currentState;
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
		// 向いている方向と逆方向に移動する
		VECTOR backMoveVec = VScale(VNorm(m_eToPDirVec), -1.0f * m_status.avoidDist);
		m_pos = VAdd(m_pos,backMoveVec);
		return CharacterBase::State::kAvoid;
	}
}


/// <summary>
/// 構え処理
/// </summary>
CharacterBase::State  EnemyBase::Fighting()
{
	m_isFighting = true;
	PlayAnim(AnimKind::kFightWalk);
	return CharacterBase::State::kFightWalk;

}


/// <summary>
/// ガード処理
/// </summary>
CharacterBase::State EnemyBase::Guard()
{
	m_isGuard = true;
	PlayAnim(AnimKind::kGuard);
	return CharacterBase::State::kGuard;
}


/// <summary>
/// ガード状態を解除
/// </summary>
CharacterBase::State EnemyBase::OffGuard()
{
	m_isGuard = false;
	PlayAnim(AnimKind::kFightIdle);
	return CharacterBase::State::kFightIdle;
}


/// <summary>
/// 敵の角度を更新
/// </summary>
void EnemyBase::UpdateAngle()
{
	m_angleIntervalTime++;

	// 移動中は常にプレイヤーの方向を向くようにする
	if(m_currentState == CharacterBase::State::kRun || m_currentState == CharacterBase::State::kAvoid)
	{
		m_angle = atan2f(m_eToPDirVec.x, m_eToPDirVec.z);
	}
	// 一定時間経過したら
	else if (m_angleIntervalTime >= m_enemyInfo.changeAngleFrame)
	{
		// ランダムでプレイヤーの方向を向く
		int randNum = GetRand(m_enemyInfo.maxProb);
		if (randNum <= m_enemyInfo.changeAngleProb)
		{
			m_angle = atan2f(m_eToPDirVec.x, m_eToPDirVec.z);
		}
		m_angleIntervalTime = 0;
	}

	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));
}


/// <summary>
/// プレイヤーとの当たり判定をチェックする
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="eCapPosTop">敵の当たり判定カプセルの頂点位置</param>
/// <param name="eCapPosBottom">敵の当たり判定カプセルの頂点位置</param>
/// <param name="eCapRadius">敵の当たり判定カプセルの半径</param>
void EnemyBase::CheckHitPlayerCol(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius)
{
	// プレイヤーと敵の当たり判定を行う
	bool isHit = HitCheck_Capsule_Capsule(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius, eCapPosTop, eCapPosBottom, eCapRadius);
	// パンチ
	bool isHitPunch = HitCheck_Capsule_Capsule(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius, eCapPosTop, eCapPosBottom, eCapRadius);
	// キック
	bool isHitKick = HitCheck_Capsule_Capsule(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius, eCapPosTop, eCapPosBottom, eCapRadius);

	// 背後から攻撃したかどうか
	m_eToPDirVec = VNorm(m_eToPDirVec);
	bool isBackAttack = VDot(player.GetDir(), m_eToPDirVec) < 0.0f;

	// パンチ状態かどうか
	bool isStatePunch = m_currentState == CharacterBase::State::kPunch1 || m_currentState == CharacterBase::State::kPunch2 || m_currentState == CharacterBase::State::kPunch3;
	// パンチが当たった場合
	if (isHitPunch && isStatePunch)
	{
		// プレイヤーがガードしていないか、背後から攻撃した場合
		if (isBackAttack || !player.GetIsGuard())
		{
			// 1コンボ目
			if (m_currentState == CharacterBase::State::kPunch1)
			{
				player.OnDamage(m_status.punchPower);
			}
			// 2コンボ目
			if (m_currentState == CharacterBase::State::kPunch2)
			{
				player.OnDamage(m_status.secondPunchPower);
			}
			// 3コンボ目
			if (m_currentState == CharacterBase::State::kPunch3)
			{
				player.OnDamage(m_status.thirdPunchPower);
			}
		}
		else
		{
			player.OnDamage(0.0f);
		}
	}
	// キックが当たった場合
	else if (isHitKick && m_currentState == CharacterBase::State::kKick)
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

	// 掴みが決まらなかった場合
	if (!isHit && m_currentState == CharacterBase::State::kGrab)
	{
		// 掴み失敗のアニメーションを再生する
		PlayAnim(CharacterBase::AnimKind::kStumble);
	}
}


#ifdef _DEBUG
/// <summary>
/// デバッグ用
/// </summary>
void EnemyBase::DebugDamage(Input& input)
{
	if (input.IsTriggered("debug_damage"))
	{
		m_hp = 0;
	}
}
#endif
