#include "Capsule2.h"

/// <summary>
/// コンストラクタ
/// </summary>
Capsule2::Capsule2():
	m_pos1(VGet(10.0f, 0.0f, 0.0f)),
	m_pos2(VGet(30.0f, 0.0f, 20.0f)),
	m_v3Direction(VSub(m_pos2, m_pos1)),
	m_centerPos(VScale(VAdd(m_pos1, m_pos2), 0.5f)),
	m_radius(kRadius)
{
}


/// <summary>
/// 描画
/// </summary>
void Capsule2::Draw()
{
	// カプセルを描画
	DrawCapsule3D(m_pos1, m_pos2, 10.0f, 8, 0xffffff, 0x000000, true);
}
