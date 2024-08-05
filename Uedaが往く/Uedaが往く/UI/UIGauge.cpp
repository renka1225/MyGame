#include "DxLib.h"
#include "Vec2.h"
#include "CharacterBase.h"
#include "UIGauge.h"

// �萔
namespace
{
	const Vec2 kESilhouettePos = { 1700.0f, 870.0f };		// �G�L�����N�^�[�̃V���G�b�g�ʒu
	constexpr int kSilhouetteWidth = 268;					// �L�����N�^�[�̃V���G�b�g�摜��
	constexpr int kSilhouetteHeight = 213;					// �L�����N�^�[�̃V���G�b�g�摜����
	
	constexpr int kHpColor = 0xff0000;						// HP�o�[�̐F
	constexpr int kDamageHpColor = 0xffd700;				// �_���[�W����HP�o�[�̐F
	constexpr int kpGaugeColor = 0x0000ff;					// �Q�[�W�o�[�̐F
	constexpr int kIntervalTime = 50;						// HP�o�[����������܂ł̎���

	// �v���C���[UI
	const Vec2 kPlayerHpBarLT = { 25.0f, 50.0f };			// HP�o�[����ʒu
	const Vec2 kPlayerHpBarRB = { 1000.0f, 80.0f };			// HP�o�[�E���ʒu
	const Vec2 kPlayerCurrentHpLT = { 50.0f, 56.0f };		// ���݂�HP����ʒu
	constexpr float kPlayerHpWidth = 907.0f;				// HP�o�[�̉���
	constexpr float kPlayerHpHeight = 18.0f;				// HP�o�[�̏c��
		
	const Vec2 kPlayerGaugeBarLT = { 25.0f, 95.0f };		// �Q�[�W�o�[����ʒu
	const Vec2 kPlayerGaugeBarRB = { 800.0f, 120.0f };		// �Q�[�W�o�[�E���ʒu
	const Vec2 kPlayerCurrentGaugeLT = { 40.0f, 100.0f };	// ���݂̃Q�[�W�ʍ���ʒu
	constexpr float kPlayerGaugeWidth = 727.0f;				// �Q�[�W�o�[�̉���
	constexpr float kPlayerGaugeHeight = 15.0f;				// �Q�[�W�o�[�̏c��

	// �GUI
	const Vec2 kEnemyHpBarLT = { 850.0f, 970.0f };			// HP�o�[����ʒu
	const Vec2 kEnemyHpBarRB = { 1850.0f, 1000.0f };		// HP�o�[�E���ʒu
	const Vec2 kEnemyCurrentHpLT = { 885.0f, 976.0f };		// ���݂�HP����ʒu
	constexpr float kEnemyHpWidth = 920.0f;					// HP�o�[�̉���
	constexpr float kEnemyHpHeight = 17.0f;					// HP�o�[�̏c��
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
	m_silhouetteHandle = LoadGraph("data/UI/silhouette.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
UIGauge::~UIGauge()
{
	DeleteGraph(m_gaugeBarHandle);
	DeleteGraph(m_silhouetteHandle);
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
	// �_���[�W���󂯂��ۂɕ\������
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
/// <param name="currentHp">���݂�HP</param>
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
/// �V���G�b�g�`��
/// </summary>
void UIGauge::DrawSilhouette(int charType)
{
	DrawRectRotaGraphF(kESilhouettePos.x, kESilhouettePos.y, kSilhouetteWidth * charType, 0, kSilhouetteWidth, kSilhouetteHeight, 1.0f, 0.0f, m_silhouetteHandle, true);
}


/// <summary>
/// �_���[�W���󂯂��ۂɃ^�C�}�[���Z�b�g����
/// </summary>
void UIGauge::SetDamageTimer()
{
	if (m_intervalTime < 0)
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
