#include "Rigidbody.h"

/// <summary>
/// コンストラクタ
/// </summary>
Rigidbody::Rigidbody():
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_dir(VGet(0.0f, 0.0f, 0.0f)),
	m_velocity(VGet(0.0f, 0.0f, 0.0f))
{
}

/// <summary>
/// 初期化
/// </summary>
void Rigidbody::Init()
{
}


/// <summary>
/// VelocityのDirを計算する
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
