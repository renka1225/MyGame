#include "Triangle.h"


/// <summary>
/// コンストラクタ
/// </summary>
Triangle::Triangle():
	m_pos1(VGet(-30.0f, 0.0f, -50.0f)),
	m_pos2(VGet(0.0f, 0.0f, 20.0f)),
	m_pos3(VGet(30.0f, 0.0f, 0.0f))
{
}


/// <summary>
/// 描画
/// </summary>
void Triangle::Draw()
{
	DrawTriangle3D(m_pos1, m_pos2, m_pos3, 0xffffff, true);
}
