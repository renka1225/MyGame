#include "DxLib.h"
#include "UIGauge.h"

// �萔
namespace
{
	// �v���C���[UI
	constexpr float kPHpDispL = 30.0f;		// HP�o�[���\���ʒu
	constexpr float kPHpDispT = 40.0f;		// HP�o�[��\���ʒu
	constexpr float kPHpWidth = 400.0f;		// HP�o�[�̉���
	constexpr float kPHpHeight = 20.0f;		// HP�o�[�̏c��
	constexpr int kPHpColor = 0xff0000;		// HP�o�[�̐F
	constexpr float kpGaugeDispL = 30.0f;	// �Q�[�W�o�[���\���ʒu
	constexpr float kpGaugeDispT = 80.0f;	// �Q�[�W�o�[��\���ʒu
	constexpr float kpGaugeWidth = 400.0f;	// �Q�[�W�o�[�̉���
	constexpr float kpGaugeHeight = 20.0f;  // �Q�[�W�o�[�̏c��
	constexpr int kpGaugeColor = 0x0000ff;	// HP�o�[�̐F

	// �GUI
	constexpr float kEHpDispL = 550.0f;		// HP�o�[���\���ʒu
	constexpr float kEHpDispT = 950.0f;		// HP�o�[��\���ʒu
	constexpr float kEHpWidth = 770.0f;		// HP�o�[�̉���
	constexpr float kEHpHeight = 30.0f;		// HP�o�[�̏c��
	constexpr int kEHpColor = 0xff0000;		// HP�o�[�̐F
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
UIGauge::UIGauge()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UIGauge::~UIGauge()
{
}


/// <summary>
/// ������
/// </summary>
void UIGauge::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
void UIGauge::Update()
{
}


/// <summary>
/// �v���C���[��HP�o�[�\��
/// </summary>
/// <param name="currentHp">���݂�HP</param>
/// <param name="MaxHp">�ő�HP</param>
void UIGauge::DrawPlayerHP(float currentHp, float MaxHp)
{
	// �\������Q�[�W�ʂ��v�Z����
	float hpRatio = currentHp / MaxHp;
	float hpLength = kPHpWidth* hpRatio;

	// TODO:�o�[�̔w�i�����͉摜�ɂ���
	DrawBoxAA(kPHpDispL, kPHpDispT, kPHpDispL + kPHpWidth, kPHpDispT + kPHpHeight, 0xffffff, false);
	DrawBoxAA(kPHpDispL, kPHpDispT, kPHpDispL + hpLength, kPHpDispT + kPHpHeight, kPHpColor, true);
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

	// TODO:�o�[�̔w�i�����͉摜�ɂ���
	DrawBoxAA(kpGaugeDispL, kpGaugeDispT, kpGaugeDispL + kpGaugeWidth, kpGaugeDispT + kpGaugeHeight, 0xffffff, false);
	DrawBoxAA(kpGaugeDispL, kpGaugeDispT, kpGaugeDispL + hpLength, kpGaugeDispT + kpGaugeHeight, kpGaugeColor, true);
}


/// <summary>
/// �G��HP�o�[��\��
/// </summary>
/// <param name="currentHp"></param>
/// <param name="MaxHp"></param>
void UIGauge::DrawEnemyHp(float currentHp, float MaxHp)
{
	// �\������Q�[�W�ʂ��v�Z����
	float hpRatio = currentHp / MaxHp;
	float hpLength = kEHpWidth * hpRatio;

	// TODO:�o�[�̔w�i�����͉摜�ɂ���
	DrawBoxAA(kEHpDispL, kEHpDispT, kEHpDispL + kEHpWidth, kEHpDispT + kEHpHeight, 0xffffff, false);
	DrawBoxAA(kEHpDispL, kEHpDispT, kEHpDispL + hpLength, kEHpDispT + kEHpHeight, kEHpColor, true);
}
