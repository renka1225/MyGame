#include "Sphere2.h"

/// <summary>
/// コンストラクタ
/// </summary>
Sphere2::Sphere2():
	m_pos(VGet(30.0f, 0.0f, 0.0f))
{
}

/// <summary>
/// 描画
/// </summary>
void Sphere2::Draw()
{
	// 球を描画
	DrawSphere3D(m_pos, 10.0f, 8, 0xffffff, 0x000000, true);
}
