#include "Cube2.h"

/// <summary>
/// コンストラクタ
/// </summary>
Cube2::Cube2():
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_scale(VGet(0.3f, 0.1f, 0.1f))
{
	m_handle = MV1LoadModel("data/cube2.mv1");

	MV1SetScale(m_handle, m_scale);
	MV1SetPosition(m_handle, m_pos);
}


/// <summary>
/// 描画
/// </summary>
void Cube2::Draw()
{
	MV1DrawModel(m_handle);
}
