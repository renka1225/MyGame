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
void EnemyBase::CheckCollision(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius)
{

}
