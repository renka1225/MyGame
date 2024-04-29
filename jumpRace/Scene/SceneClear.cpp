#include "SceneClear.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "ManagerFont.h"
#include "ManagerResult.h"
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
	DrawFormatStringToHandle(kStartTextPosX, kStartTextPosY, 0xffffff, m_pFont->GetFont(), "����1��");
	DrawFormatStringToHandle(kTitleTextPosX, kTitleTextPosY, 0xffffff, m_pFont->GetFont(), "�^�C�g���ɂ��ǂ�");

	// �N���A�^�C���\��
	int milliSec = m_clearTime * 1000 / 60;
	int sec = (milliSec / 1000) % 90;
	milliSec %= 1000;
	DrawFormatString(kClearTimePosX, kClearTimePosY, 0xffffff, "�N���A�^�C��:%02d:%03d", sec, milliSec);

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

