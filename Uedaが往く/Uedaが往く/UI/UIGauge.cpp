#include "DxLib.h"
#include "UIGauge.h"

// �萔
namespace
{
	// �v���C���[UI
	constexpr float kPHpDispL = 30.0f;		 // HP�o�[���\���ʒu
	constexpr float kPHpDispT = 40.0f;		 // HP�o�[��\���ʒu
	constexpr float kPHpWidth = 400.0f;		 // HP�o�[�̉���
	constexpr float kPHpHeight = 20.0f;		 // HP�o�[�̏c��

	constexpr float kpGaugeDispL = 30.0f;	 // �Q�[�W�o�[���\���ʒu
	constexpr float kpGaugeDispT = 80.0f;	 // �Q�[�W�o�[��\���ʒu
	constexpr float kpGaugeWidth = 400.0f;	 // �Q�[�W�o�[�̉���
	constexpr float kpGaugeHeight = 20.0f;   // �Q�[�W�o�[�̏c��
	constexpr int kpGaugeColor = 0x0000ff;	 // �Q�[�W�o�[�̐F

	// �GUI
	constexpr float kEHpDispL = 550.0f;		 // HP�o�[���\���ʒu
	constexpr float kEHpDispT = 950.0f;		 // HP�o�[��\���ʒu
	constexpr float kEHpWidth = 770.0f;		 // HP�o�[�̉���
	constexpr float kEHpHeight = 30.0f;		 // HP�o�[�̏c��

	constexpr int kHpColor = 0xff0000;		 // HP�o�[�̐F
	constexpr int kDamageHpColor = 0xffd700; // �_���[�W����HP�o�[�̐F


	// HP�o�[����������܂ł̎���
	constexpr int kIntervalTime = 30;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
UIGauge::UIGauge(float maxHp):
	m_decreaseHp(maxHp),
	m_currentHp(maxHp),
	m_maxHp(maxHp),
	m_damage(0.0f),
	m_intervalTime(0)
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
UIGauge::~UIGauge()
{
}


/// <summary>
/// �X�V
/// </summary>
void UIGauge::UpdateHpBar()
{
	if (m_intervalTime >= 0)
	{
		m_intervalTime--;
	}
	if (m_intervalTime < 0)
	{
		m_currentHp -= m_damage;
		m_damage = 0.0f;
	}
}


/// <summary>
/// �v���C���[��HP�o�[�\��
/// </summary>
/// <param name="currentHp">���݂�HP</param>
/// <param name="MaxHp">�ő�HP</param>
void UIGauge::DrawPlayerHP(float currentHp, float damage)
{
	// �\������Q�[�W�ʂ��v�Z����
	// TODO:m_intervalTime��0�ɂȂ�����ԃo�[�̒�����ύX����
	float hpRatio = currentHp / m_maxHp;
	float decreaseHpRatio = (currentHp + m_damage) / m_maxHp;
	float hpLength = kpGaugeWidth * hpRatio;
	float decreaseHpLength = kPHpWidth * decreaseHpRatio;

	// TODO:�o�[�̔w�i�����͉摜�ɂ���
	// �o�[�̔w�i����
	DrawBoxAA(kPHpDispL, kPHpDispT, kPHpDispL + kPHpWidth, kPHpDispT + kPHpHeight, 0xffffff, false);
	// �_���[�W���󂯂����̃o�[
	if (m_intervalTime > 0)
	{
		DrawBoxAA(kPHpDispL, kPHpDispT, kPHpDispL + decreaseHpLength, kPHpDispT + kPHpHeight, kDamageHpColor, true);
	}
	// ���݂�HP�o�[
	DrawBoxAA(kPHpDispL, kPHpDispT, kPHpDispL + hpLength, kPHpDispT + kPHpHeight, kHpColor, true);

#ifdef _DEBUG
	DrawFormatString(0, 160, 0xffffff, "�_���[�W��:%f", m_damage);
	DrawFormatString(0, 180, 0xffffff, "�o�[�̒���:%f", decreaseHpLength);
#endif
}


/// <summary>
/// �v���C���[�̃Q�[�W�o�[�\��
/// </summary>
/// <param name="currentGauge">���݂̃Q�[�W��</param>
/// <param name="MaxGauge">�ő�Q�[�W��</param>
void UIGauge::DrawPlayerGauge(float currentGauge, float MaxGauge)
{
	// �\������Q�[�W�ʂ��v�Z����
	float hpRatio = currentGauge / MaxGauge;
	float hpLength = kpGaugeWidth * hpRatio;

	DrawBoxAA(kpGaugeDispL, kpGaugeDispT, kpGaugeDispL + kpGaugeWidth, kpGaugeDispT + kpGaugeHeight, 0xffffff, false);
	DrawBoxAA(kpGaugeDispL, kpGaugeDispT, kpGaugeDispL + hpLength, kpGaugeDispT + kpGaugeHeight, kpGaugeColor, true);
}


/// <summary>
/// �G��HP�o�[��\��
/// </summary>
/// <param name="currentHp"></param>
/// <param name="MaxHp"></param>
void UIGauge::DrawEnemyHp(float currentHp, float damage)
{
	// �\������Q�[�W�ʂ��v�Z����
	float hpRatio = currentHp / m_maxHp;
	float hpLength = kEHpWidth * hpRatio;
	float decreaseHpRatio = m_decreaseHp / m_maxHp;
	float decreaseHpLength = kPHpWidth * decreaseHpRatio;

	DrawBoxAA(kEHpDispL, kEHpDispT, kEHpDispL + kEHpWidth, kEHpDispT + kEHpHeight, 0xffffff, false);
	// �_���[�W���󂯂����̃o�[
	if (m_intervalTime > 0)
	{
		DrawBoxAA(kEHpDispL, kEHpDispT, kEHpDispL + decreaseHpLength, kEHpDispT + kEHpHeight, kDamageHpColor, true);
	}
	DrawBoxAA(kEHpDispL, kEHpDispT, kEHpDispL + hpLength, kEHpDispT + kEHpHeight, kHpColor, true);
}


/// <summary>
/// �_���[�W���󂯂��ۂɃ^�C�}�[���Z�b�g����
/// </summary>
void UIGauge::SetDamageTimer()
{
	if (m_intervalTime <= 0)
	{
		m_intervalTime = kIntervalTime;
	}
}


/// <summary>
/// �_���[�W���󂯂����̏���
/// </summary>
/// <param name="damage">�󂯂��_���[�W��</param>
void UIGauge::OnDamage(float damage)
{
	m_damage += damage;
	SetDamageTimer();
}
