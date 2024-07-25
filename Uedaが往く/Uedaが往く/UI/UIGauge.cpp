#include "DxLib.h"
#include "Vec2.h"
#include "UIGauge.h"

// �萔
namespace
{
	// �v���C���[UI
	const Vec2 kPlayerHpBarLT = { 25.0f, 40.0f };			// HP�o�[����ʒu
	const Vec2 kPlayerHpBarRB = { 600.0f, 100.0f };			// HP�o�[�E���ʒu
	const Vec2 kPlayerCurrentHpLT = { 40.0f, 55.0f };		// ���݂�HP����ʒu
	constexpr float kPlayerHpWidth = 540.0f;				// HP�o�[�̉���
	constexpr float kPlayerHpHeight = 32.0f;				// HP�o�[�̏c��
		
	const Vec2 kPlayerGaugeBarLT = { 25.0f, 110.0f };		// �Q�[�W�o�[����ʒu
	const Vec2 kPlayerGaugeBarRB = { 600.0f, 140.0f };		// �Q�[�W�o�[�E���ʒu
	const Vec2 kPlayerCurrentGaugeLT = { 40.0f, 118.0f };	// ���݂̃Q�[�W�ʍ���ʒu
	constexpr float kPlayerGaugeWidth = 520.0f;				// �Q�[�W�o�[�̉���
	constexpr float kPlayerGaugeHeight = 16.0f;				// �Q�[�W�o�[�̏c��
	constexpr int kpGaugeColor = 0x0000ff;					// �Q�[�W�o�[�̐F

	// �GUI
	const Vec2 kEnemyHpBarLT = { 535.0f, 935.0f };		// HP�o�[����ʒu
	const Vec2 kEnemyHpBarRB = { 1300.0f, 1000.0f };	// HP�o�[�E���ʒu
	const Vec2 kEnemyCurrentHpLT = { 560.0f, 952.0f };	// ���݂�HP����ʒu
	constexpr float kEnemyHpWidth = 710.0f;				// HP�o�[�̉���
	constexpr float kEnemyHpHeight = 32.0f;				// HP�o�[�̏c��

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
	m_gaugeBarHandle = LoadGraph("data/UI/Gauge.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
UIGauge::~UIGauge()
{
	DeleteGraph(m_gaugeBarHandle);
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
void UIGauge::DrawPlayerHP(float currentHp)
{
	// �\������Q�[�W�ʂ��v�Z����
	float hpRatio = currentHp / m_maxHp;
	float decreaseHpRatio = (currentHp + m_damage) / m_maxHp;
	float hpLength = kPlayerHpWidth * hpRatio;
	float decreaseHpLength = kPlayerHpWidth * decreaseHpRatio;

	// �o�[�̔w�i����
	DrawExtendGraphF(kPlayerHpBarLT.x, kPlayerHpBarLT.y, kPlayerHpBarRB.x, kPlayerHpBarRB.y, m_gaugeBarHandle, true);
	// �_���[�W���󂯂����̃o�[
	if (m_intervalTime > 0)
	{
		DrawBoxAA(kPlayerCurrentHpLT.x, kPlayerCurrentHpLT.y, kPlayerCurrentHpLT.x + decreaseHpLength, kPlayerCurrentHpLT.y + kPlayerHpHeight, kDamageHpColor, true);
	}
	// ���݂�HP�o�[
	DrawBoxAA(kPlayerCurrentHpLT.x, kPlayerCurrentHpLT.y, kPlayerCurrentHpLT.x + hpLength, kPlayerCurrentHpLT.y + kPlayerHpHeight, kHpColor, true);
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
	float hpLength = kPlayerGaugeWidth * hpRatio;

	// �o�[�̔w�i����
	DrawExtendGraphF(kPlayerGaugeBarLT.x, kPlayerGaugeBarLT.y, kPlayerGaugeBarRB.x, kPlayerGaugeBarRB.y, m_gaugeBarHandle, true);
	DrawBoxAA(kPlayerCurrentGaugeLT.x, kPlayerCurrentGaugeLT.y, kPlayerCurrentGaugeLT.x + hpLength, kPlayerCurrentGaugeLT.y + kPlayerGaugeHeight, kpGaugeColor, true);
}


/// <summary>
/// �G��HP�o�[��\��
/// </summary>
/// <param name="currentHp"></param>
/// <param name="MaxHp"></param>
void UIGauge::DrawEnemyHp(float currentHp)
{
	// �\������Q�[�W�ʂ��v�Z����
	float hpRatio = currentHp / m_maxHp;
	float decreaseHpRatio = (currentHp + m_damage) / m_maxHp;
	float hpLength = kEnemyHpWidth * hpRatio;
	float decreaseHpLength = kEnemyHpWidth * decreaseHpRatio;

	// �o�[�̔w�i����
	DrawExtendGraphF(kEnemyHpBarLT.x, kEnemyHpBarLT.y, kEnemyHpBarRB.x, kEnemyHpBarRB.y, m_gaugeBarHandle, true);
	// �_���[�W���󂯂����̃o�[
	if (m_intervalTime > 0)
	{
		DrawBoxAA(kEnemyCurrentHpLT.x, kEnemyCurrentHpLT.y, kEnemyCurrentHpLT.x + decreaseHpLength, kEnemyCurrentHpLT.y + kEnemyHpHeight, kDamageHpColor, true);
	}
	DrawBoxAA(kEnemyCurrentHpLT.x, kEnemyCurrentHpLT.y, kEnemyCurrentHpLT.x + hpLength, kEnemyCurrentHpLT.y + kEnemyHpHeight, kHpColor, true);
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
