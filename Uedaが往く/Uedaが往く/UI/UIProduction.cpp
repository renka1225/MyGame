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