#include "Sphere2.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Sphere2::Sphere2():
	m_pos(VGet(30.0f, 0.0f, 0.0f))
{
}

/// <summary>
/// �`��
/// </summary>
void Sphere2::Draw()
{
	// ����`��
	DrawSphere3D(m_pos, 10.0f, 8, 0xffffff, 0x000000, true);
}
