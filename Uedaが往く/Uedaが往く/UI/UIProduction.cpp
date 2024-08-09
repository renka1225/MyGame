#include "DxLib.h"
#include "Vec2.h"
#include "UIProduction.h"
#include "Game.h"

// �萔
namespace
{
	/*�����J�n��*/
	const char* const kFightTextPath = "data/UI/Fight!.png"; // "Fight"�̃e�L�X�g�摜�ʒu
	const char* const kNumTextPath = "data/UI/number.png";	 // �����̉摜�ʒu

	constexpr int kFightTextDispStart = 80;					// "Fight"�̃e�L�X�g��\�����n�߂鎞��
	const Vec2 kFightTextPos = { 960, 550 };				// "Fight"�̃e�L�X�g�ʒu
	constexpr float kFightTextScele = 0.6f;					// "Fight"�̃e�L�X�g�T�C�Y
	const Vec2 kMatcheNumTextPos = { 850, 600 };			// ���݂̎������\���ʒu
	constexpr int kMatchNumTextWidth = 260;					// 1������̃e�L�X�g�̕�
	constexpr int kMatchNumTextInterval = 70;				// �e�L�X�g�̕\���Ԋu
	constexpr int kTextAdj= 60;								// �e�L�X�g�̕\���Ԋu����
	constexpr float kMatchNumTextScele = 0.5f;				// �������̃e�L�X�g�T�C�Y

	/*����������*/
	const Vec2 kOperationFramePos = { 40.0f, 340.0f };		// �g�\���ʒu
	constexpr float kOperationWidth = 200.0f;				// �g�̉���
	constexpr float kOperationHeight = 500.0f;				// �g�̏c��
	constexpr int kOperationBackColor = 0x000000;			// �g�̔w�i�F
	const Vec2 kOperationTextPos = { 90.0f, 390.0f };		// �e�L�X�g�̕\���ʒu
	constexpr float kOperationTextInterval = 50.0f;		// �e�L�X�g�̕\���Ԋu
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
UIProduction::UIProduction()
{
	m_fightTextHandle = LoadGraph(kFightTextPath);
	m_numTextHandle = LoadGraph(kNumTextPath);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
UIProduction::~UIProduction()
{
	DeleteGraph(m_fightTextHandle);
	DeleteGraph(m_numTextHandle);
}


/// <summary>
/// �X�V
/// </summary>
void UIProduction::Update()
{
}


/// <summary>
///  �X�^�[�g���̉��o��\��
/// </summary>
/// <param name="time">���̎������n�܂�܂ł̎���</param>
/// <param name="matchNum">���݂̎�����</param>
/// <param name="maxMatch">�ő�̎�����</param>
void UIProduction::DrawStartProduction(int time, int matchNum, int maxMatch)
{
	if (time > kFightTextDispStart)
	{
		int sizeW, sizeH;
		GetGraphSize(m_numTextHandle, &sizeW, &sizeH);
		// ���݂̎�������\��
		DrawRectRotaGraphF(kMatcheNumTextPos.x, kMatcheNumTextPos.y, 
			kMatchNumTextWidth * matchNum, 0, kMatchNumTextWidth, sizeH,
			kMatchNumTextScele, 0.0f, m_numTextHandle, true);
		// /�\��
		DrawRectRotaGraphF(kMatcheNumTextPos.x + kMatchNumTextInterval, kMatcheNumTextPos.y, 
			sizeW - kMatchNumTextWidth, 0, kMatchNumTextWidth, sizeH,
			kMatchNumTextScele, 0.0f, m_numTextHandle, true);
		// �ő厎������\��
		DrawRectRotaGraphF(kMatcheNumTextPos.x + kMatchNumTextInterval * 2 + kTextAdj, kMatcheNumTextPos.y, 
			kMatchNumTextWidth * (maxMatch - 1), 0, kMatchNumTextWidth, sizeH,
			kMatchNumTextScele, 0.0f, m_numTextHandle, true);
	}
	// "Fight!"�̕�����\��
	else if (time < kFightTextDispStart && time > 0)
	{
		int sizeW, sizeH;
		GetGraphSize(m_fightTextHandle, &sizeW, &sizeH);
		DrawRectRotaGraphF(kFightTextPos.x, kFightTextPos.y, 0, 0, sizeW, sizeH, kFightTextScele, 0.0f, m_fightTextHandle, true);
	}
}


/// <summary>
/// ���������\������
/// </summary>
void UIProduction::DrawOperation()
{
	// �w�i�𔖂��\������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxAA(kOperationFramePos.x, kOperationFramePos.y, kOperationFramePos.x + kOperationWidth, kOperationFramePos.y + kOperationHeight, kOperationBackColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// TODO:�e�L�X�g�\��
	DrawString(kOperationTextPos.x, kOperationTextPos.y + kOperationTextInterval * kLSButton, "�ړ� : LS" , 0xfffffff);
	DrawString(kOperationTextPos.x, kOperationTextPos.y + kOperationTextInterval* kRSButton, "�J�����ړ� : RS" , 0xfffffff);
	DrawString(kOperationTextPos.x, kOperationTextPos.y + kOperationTextInterval * kXButton, "�p���` : X" , 0xfffffff);
	DrawString(kOperationTextPos.x, kOperationTextPos.y + kOperationTextInterval * kYButton, "�L�b�N : Y" , 0xfffffff);
	DrawString(kOperationTextPos.x, kOperationTextPos.y + kOperationTextInterval * kAButton, "��� : A" , 0xfffffff);
	DrawString(kOperationTextPos.x, kOperationTextPos.y + kOperationTextInterval * kLBButton, "�K�[�h : LB" , 0xfffffff);
	DrawString(kOperationTextPos.x, kOperationTextPos.y + kOperationTextInterval * kRBButton, "���b�N�I�� : RB" , 0xfffffff);
	DrawString(kOperationTextPos.x, kOperationTextPos.y + kOperationTextInterval * kLineButton, "�|�[�Y : start" , 0xfffffff);
}
