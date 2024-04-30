#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "SceneResult.h"
#include "ManagerFont.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle():
	m_select(kStart)
{
	m_titleLogo = LoadGraph("data/UI/title.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogo);
}


/// <summary>
/// ������
/// </summary>
void SceneTitle::Init()
{
	// �����Ȃ�
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">�{�^������</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	UpdateSelect(input);	// �I����ԍX�V

	if (input.IsTriggered("sceneChange"))
	{
		if (m_select == kStart)
		{
			return std::make_shared<ScenePlaying>();	// �Q�[���V�[���Ɉړ�
		}
		else if (m_select == kResult)
		{
			return std::make_shared<SceneResult>();		// ���ʊm�F��ʂɈړ�
		}
		else if (m_select == kEnd)
		{
			DxLib_End();	// �Q�[���I��
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneTitle::Draw()
{
	// �^�C�g���\��
	DrawGraph(kTitleLogoPosX, kTitleLogoPosY, m_titleLogo, true);

	// �I�����ڂ�\��
	DrawSelect();

	// �N���W�b�g�\�L
	DrawFormatStringToHandle(900, 690, 0xffffff, m_pFont->GetCreditFont(), "���p�\�t�g/VOICEVOX:�i�[�X���{�Q�^�C�v�s");

#ifdef _DEBUG
	// �f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�^�C�g�����");
	// ���S��
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0xfffff);
#endif
}


/// <summary>
/// �I����Ԃ̍X�V
/// </summary>
void SceneTitle::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1������
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + 2) % kSelectNum;	// �I����Ԃ�1�グ��
	}
}


/// <summary>
/// �I�����ڂ�\��
/// </summary>
void SceneTitle::DrawSelect()
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

	// �e�L�X�g�\��
	DrawFormatStringToHandle(kStartTextPosX, kStartTextPosY, 0xffffff, m_pFont->GetTextFont(), "�X�^�[�g");
	DrawFormatStringToHandle(kResultTextPosX, kResultTextPosY, 0xffffff, m_pFont->GetTextFont(), "�����L���O");
	DrawFormatStringToHandle(kEndTextPosX, kEndTextPosY, 0xffffff, m_pFont->GetTextFont(), "�����");
}
