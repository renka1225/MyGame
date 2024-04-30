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
SceneClear::SceneClear(std::shared_ptr<ManagerResult> pResult, int time):
	m_clearTime(time),
	m_select(kStart)
{
	m_pResult = pResult;

	m_pConversionTime->Change(m_pResult->GetHighScore());
	printfDx("%d\n", m_pResult->GetHighScore());
	printfDx("�x�X�g�^�C��:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	m_pConversionTime->Change(m_pResult->GetSecond());
	printfDx("2��:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	m_pConversionTime->Change(m_pResult->GetThird());
	printfDx("3��:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
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
void SceneClear::Init()
{
	// �����Ȃ�
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">�{�^������</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	UpdateSelect(input);	// �I����ԍX�V

	if (input.IsTriggered("sceneChange"))
	{
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
	// �I�����ڂ�\��
	DrawSelect();
	// ���ʕ\��
	DrawResult();

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
		0x00ff00, true);

	// �g�\��
	for (int i = 0; i < kSelectNum; i++)
	{
		DrawGraph(kFramePosX, kFramePosY + kSelectMove * i, m_frameHandle, true);
	}

	DrawFormatStringToHandle(kStartTextPosX, kStartTextPosY, 0xffffff, m_pFont->GetTextFont(), "����1��");
	DrawFormatStringToHandle(kTitleTextPosX, kTitleTextPosY, 0xffffff, m_pFont->GetTextFont(), "�^�C�g���ɂ��ǂ�");
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

	// �n�C�X�R�A�\��
	m_pConversionTime->Change(m_pResult->GetHighScore());	// �^�C���ϊ�
	DrawFormatStringToHandle(kTimePosX, kHighScorePosY, 0xffffff, m_pFont->GetResultTimeFont(),
		"1��:%02d:%03d", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	m_pConversionTime->Change(m_pResult->GetSecond());		// �^�C���ϊ�
	DrawFormatStringToHandle(kTimePosX, kSecondPosY, 0xffffff, m_pFont->GetResultTimeFont(),
		"2��:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	m_pConversionTime->Change(m_pResult->GetThird());		// �^�C���ϊ�
	DrawFormatStringToHandle(kTimePosX, kThirdPosY, 0xffffff, m_pFont->GetResultTimeFont(),
		"3��:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
}
