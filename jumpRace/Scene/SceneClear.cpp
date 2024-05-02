#include "SceneClear.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "ManagerFont.h"
#include "ManagerResult.h"
#include "ConversionTime.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneClear::SceneClear(int time):
	m_clearTime(time),
	m_select(kStart)
{
	m_fadeAlpha = kStartFadeAlpha;
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneClear::~SceneClear()
{
}


/// <summary>
/// ������
/// </summary>
void SceneClear::Init(std::shared_ptr<ManagerResult> pResult)
{
	m_pResult = pResult;
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">�{�^������</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	FadeOut();	// �t�F�[�h�A�E�g

	UpdateSelect(input);	// �I����ԍX�V

	if (input.IsTriggered("sceneChange"))
	{
		FadeIn();	// �t�F�[�h�C��

		if (m_select == kStart)
		{
			return std::make_shared<ScenePlaying>();	// �Q�[���V�[���Ɉړ�
		}
		else if (m_select == kTitle)
		{
			return std::make_shared<SceneTitle>();		//�^�C�g����ʂɈړ�
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneClear::Draw()
{
	DrawSelect();	// �I�����ڂ�\��
	DrawResult();	// ���ʕ\��

	DrawFade();		// �t�F�[�h

#ifdef _DEBUG
	// �f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�N���A���");
	// ���S��
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0xfffff);
#endif
}


/// <summary>
/// �I����Ԃ̍X�V
/// </summary>
void SceneClear::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1������
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1�グ��
	}
}


/// <summary>
/// �I�����ڕ\��
/// </summary>
void SceneClear::DrawSelect()
{
	// �I�𒆂̍��ڂɐF������
	DrawBox(kNowSelectPosX, kNowSelectPosY + kSelectMove * m_select,
		kNowSelectPosX + kNowSelectWidth, kNowSelectPosY + kSelectMove * m_select + kNowSelectHeight,
		0x4289A3, true);

	// �g�\��
	for (int i = 0; i < kSelectNum; i++)
	{
		DrawGraph(kFramePosX, kFramePosY + kSelectMove * i, m_frameHandle, true);
	}

	DrawFormatStringToHandle(kStartTextPosX, kStartTextPosY, 0xffffff, m_pFont->GetTextFont(), "����1��");
	DrawFormatStringToHandle(kTitleTextPosX, kTitleTextPosY, 0xffffff, m_pFont->GetTextFont2(), "�^�C�g���ɂ��ǂ�");
}


/// <summary>
/// ���ʕ\��
/// </summary>
void SceneClear::DrawResult()
{
	// �N���A�^�C���\��
	m_pConversionTime->Change(m_clearTime);	// �^�C���ϊ�
	DrawFormatStringToHandle(kClearTimePosX, kClearTimePosY, 0xffffff, m_pFont->GetResultTimeFont(), 
		"�N���A�^�C��:%02d:%03d", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	for (int i = 0; i < kDisplayRanking; i++)
	{
		m_pConversionTime->Change(m_pResult->GetRanking()[i]); // �^�C���ϊ�
		DrawFormatStringToHandle(kTimePosX, kTimePosY + kIntervalY * i, 0xffffff, m_pFont->GetResultTimeFont(),
			"%d��:%02d:%03d\n", (i + 1), m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
	}
}