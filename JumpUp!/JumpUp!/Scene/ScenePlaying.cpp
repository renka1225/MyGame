#include "DxLib.h"
#include "ScenePlaying.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "Input.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ScenePlaying::ScenePlaying()
{
	m_pPlayer = std::make_shared<Player>();
	m_pCamera = std::make_shared<Camera>();
	m_pStage = std::make_shared<Stage>();
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ScenePlaying::~ScenePlaying()
{
	// �����Ȃ�
}


/// <summary>
/// ������
/// </summary>
void ScenePlaying::Init()
{
	m_pPlayer->Init();
	m_pCamera->Init();
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">����</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
#ifdef _DEBUG	// �f�o�b�O���[�h
	// P�L�[�Ń|�[�Y�A�|�[�Y����P�ŃR�}����
	if (m_debugState == DebugState::Normal && input.IsPressing("debug_pause"))
	{
		m_debugState = DebugState::Pause;
	}
	if (m_debugState == DebugState::Pause && input.IsPressing("debug_enter"))
	{
		m_debugState = DebugState::Normal;
	}
	if(m_debugState != DebugState::Pause || input.IsPressing("debug_pause"))
#endif
	{
		// �v���C���[�X�V
		m_pPlayer->Update(input, *m_pCamera, *m_pStage);

		// �J�����X�V
		m_pCamera->Update(input, *m_pPlayer, *m_pStage);
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePlaying::Draw()
{
#ifdef _DEBUG	// �f�o�b�O�\��
	// �O���b�h�\��
	m_pDrawDebug.DrawGrid();
	// ���݂̃V�[��
	DrawString(0, 0, "�v���C���", 0xffffff);
	// �|�[�Y�\��
	if (m_debugState == DebugState::Pause)
	{
		DrawString(0, 20, "�|�[�Y��", 0xffffff);
	}
#endif

	// �X�e�[�W�`��
	m_pStage->Draw();

	// �v���C���[�`��
	m_pPlayer->Draw(m_pDrawDebug);
}
