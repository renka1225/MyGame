#include "DxLib.h"
#include "UIGauge.h"
#include "EnemyBase.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyBase::EnemyBase():
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_hp(0.0f),
	m_modelHandle(-1)
{
	m_pUIGauge = std::make_shared<UIGauge>();
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBase::~EnemyBase()
{
}


/// <summary>
/// �U�����󂯂��ۂ̏���
/// </summary>
void EnemyBase::OnDamage(float damage)
{
	m_hp -= damage;
}

