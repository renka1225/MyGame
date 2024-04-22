#include "ScenePlaying.h"
#include "SceneClear.h"
#include "ManagerFont.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ScenePlaying::ScenePlaying():
	m_nowCommand(A),
	m_time(0),
	m_pushCount(0)
{
}


/// <summary>
/// ������
/// </summary>
void ScenePlaying::Init()
{
	m_nowCommand = GetRand(Y);
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">�{�^������</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	// �^�C���X�V
	m_time++;

	// ���̓R�}���h���X�V
	UpdateCommand(input);

	// 50����͂ł�����N���A��ʂɑJ��
	if (m_pushCount >= kMaxPush)
	{
		return std::make_shared<SceneClear>();
	}

#ifdef _DEBUG
	// MEMO:�f�o�b�O�p
	if (input.IsTriggered("sceneChange"))
	{
		return std::make_shared<SceneClear>();
	}
#endif

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePlaying::Draw()
{
	// ���̓R�}���h��\��
	DrawCommand();

	// �o�ߎ��Ԃ̕`��
	int milliSec = m_time * 1000 / 60;
	int sec = (milliSec / 1000) % 90;
	milliSec %= 1000;

#ifdef _DEBUG
	// MEMO:�f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�v���C���");
	DrawFormatString(0, 20, 0xffffff, "���͉�:%d", m_pushCount);
	DrawFormatString(0, 40, 0xffffff, "�^�C�� %02d:%03d", sec, milliSec);
#endif
}


/// <summary>
/// ���̓R�}���h�X�V
/// </summary>
void ScenePlaying::UpdateCommand(Input& input)
{
	if (m_nowCommand == A)
	{
		if (input.IsTriggered("A"))
		{
			m_pushCount++;
			m_nowCommand = GetRand(Y);
		}
	}
	if (m_nowCommand == B)
	{
		if (input.IsTriggered("B"))
		{
			m_pushCount++;
			m_nowCommand = GetRand(Y);
		}
	}
	if (m_nowCommand == X)
	{
		if (input.IsTriggered("X"))
		{
			m_pushCount++;
			m_nowCommand = GetRand(Y);
		}
	}
	if (m_nowCommand == Y)
	{
		if (input.IsTriggered("Y"))
		{
			m_pushCount++;
			m_nowCommand = GetRand(Y);
		}
	}
}


/// <summary>
/// ���̓R�}���h��\��
/// </summary>
void ScenePlaying::DrawCommand()
{
	if (m_nowCommand == A)
	{
		DrawFormatStringToHandle(Game::kScreenWidth * 0.5f, 200, 0xff0000, m_pFont->GetFont(), "A");
	}
	if (m_nowCommand == B)
	{
		DrawFormatStringToHandle(Game::kScreenWidth * 0.5f, 200, 0x00ff00, m_pFont->GetFont(), "B");
	}
	if (m_nowCommand == X)
	{
		DrawFormatStringToHandle(Game::kScreenWidth * 0.5f, 200, 0x0000ff, m_pFont->GetFont(), "X");
	}
	if (m_nowCommand == Y)
	{
		DrawFormatStringToHandle(Game::kScreenWidth * 0.5f, 200, 0xff00ff, m_pFont->GetFont(), "Y");
	}
}
