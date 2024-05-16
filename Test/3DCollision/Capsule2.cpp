#include "Capsule2.h"

/// <summary>
/// �R���X�g���N�^
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
/// �`��
/// </summary>
void Capsule2::Draw()
{
	// �J�v�Z����`��
	DrawCapsule3D(m_pos1, m_pos2, 10.0f, 8, 0xffffff, 0x000000, true);
}
