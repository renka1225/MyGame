#include "DxLib.h"
#include "Player.h"
#include "EnemyBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyBase::EnemyBase()
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
