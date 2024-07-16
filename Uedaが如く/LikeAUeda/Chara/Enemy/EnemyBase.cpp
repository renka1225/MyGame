#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyBase::EnemyBase():
	m_isMove(false)
{
	m_hp = 0.0f;
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
void EnemyBase::Move(const VECTOR& MoveVec, Player& player, Stage& stage)
{
	if (fabs(MoveVec.x) > 0.0f || fabs(MoveVec.z) > 0.0f)
	{
		m_isMove = true;
	}
	else
	{
		m_isMove = false;
	}

	// プレイヤーの方向に向かう
	VECTOR dir = VSub(player.GetPos(), m_pos);

	// 当たり判定を行って座標を保存する
	m_pos = stage.CheckEnemyCol(*this, MoveVec);

	// プレイヤーの座標を更新する
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// 移動処理
/// </summary>
/// <param name="upMoveVec">上方向への移動ベクトル</param>
/// <param name="leftMoveVec">左方向への移動ベクトル</param>
/// <param name="moveVec">移動ベクトル</param>
/// <returns>現在の状態</returns>
EnemyBase::EnemyState EnemyBase::UpdateMoveParameter(VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	EnemyState nextState = m_currentState;

	// このフレームでの移動ベクトルを初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);


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
