#include "Rigidbody.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Rigidbody::Rigidbody():
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_dir(VGet(0.0f, 0.0f, 0.0f)),
	m_velocity(VGet(0.0f, 0.0f, 0.0f))
{
}

/// <summary>
/// ������
/// </summary>
void Rigidbody::Init()
{
}


/// <summary>
/// Velocity��Dir���v�Z����
/// </summary>
/// <param name="set"></param>
void Rigidbody::SetVelocity(const VECTOR& set)
{
	m_velocity = set;
	if (VSquareSize(m_velocity) > 0)
	{
		m_dir = VNorm(m_velocity);
	}
}
