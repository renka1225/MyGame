#include "ScenePlaying.h"
#include "SceneClear.h"
#include "ManagerFont.h"
#include "ManagerResult.h"
#include "Player.h"
#include "Camera.h"
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
	m_pPlayer = std::make_shared<Player>();
	m_pCamera = std::make_shared<Camera>();
}


/// <summary>
/// ������
/// </summary>
void ScenePlaying::Init()
{
	m_pResult->Load();
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
		m_pResult->Save(m_time);	// �N���A�^�C����ۑ�
		return std::make_shared<SceneClear>(m_time);
	}

	// �v���C���[�̍X�V
	m_pPlayer->Update(input);
	// �J�����̍X�V
	m_pCamera->Update(m_pPlayer);

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
	// MEMO:XYZ���f�o�b�N�\��
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0.0f, 0), VGet(lineSize, 0.0f, 0.0f), 0xff0000);
	DrawLine3D(VGet(0.0f, -lineSize, 0.0f), VGet(0.0f, lineSize, 0.0f), 0x00ff00);
	DrawLine3D(VGet(0.0f, 0.0f, -lineSize), VGet(0.0f, 0.0f, lineSize), 0x0000ff);

	// MEMO:�f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�v���C���");
	DrawFormatString(0, 20, 0xffffff, "���͉�:%d", m_pushCount);
	DrawFormatString(0, 40, 0xffffff, "�^�C�� %02d:%03d", sec, milliSec);
#endif

	// �v���C���[�̕`��
	m_pPlayer->Draw();
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
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
	}
	if (m_nowCommand == B)
	{
		if (input.IsTriggered("B"))
		{
			m_pushCount++;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
	}
	if (m_nowCommand == X)
	{
		if (input.IsTriggered("X"))
		{
			m_pushCount++;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
	}
	if (m_nowCommand == Y)
	{
		if (input.IsTriggered("Y"))
		{
			m_pushCount++;
			m_pPlayer->Move();
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
		DrawFormatStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5f), 200, 0xff0000, m_pFont->GetFont(), "A");
	}
	if (m_nowCommand == B)
	{
		DrawFormatStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5f), 200, 0x00ff00, m_pFont->GetFont(), "B");
	}
	if (m_nowCommand == X)
	{
		DrawFormatStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5f), 200, 0x0000ff, m_pFont->GetFont(), "X");
	}
	if (m_nowCommand == Y)
	{
		DrawFormatStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5f), 200, 0xff00ff, m_pFont->GetFont(), "Y");
	}
}
