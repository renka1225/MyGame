#include "DxLib.h"
#include "LoadData.h"
#include "UIGauge.h"
#include "CharacterBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CharacterBase::CharacterBase():
	m_hp(0.0f),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_moveSpeed(0.0f),
	m_angle(0.0f),
	m_modelHandle(-1),
	m_currentPlayAnim(-1),
	m_currentAnimCount(0.0f),
	m_prevPlayAnim(-1),
	m_prevAnimCount(0.0f),
	m_animBlendRate(0.0f)
{
	m_pUIGauge = std::make_shared<UIGauge>();
}


/// <summary>
/// �_���[�W���󂯂��ۂ̏���
/// </summary>
void CharacterBase::OnDamage(float damage)
{
	m_hp -= damage;
}