#include "DxLib.h"
#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "Input.h"

// �萔
namespace
{
	// �|�[�Y���
	constexpr int kPausePosX = 600;		// �\���ʒuX
	constexpr int kPausePosY = 100;		// �\���ʒuY
	constexpr int kPauseWidth = 800;	// ����
	constexpr int kPauseHeight = 400;	// �c��
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
ScenePlaying::ScenePlaying():
	m_select(Select::kBack),
	m_isPause(false)
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
	if (input.IsPressing("sceneChange"))
	{
		return std::make_shared<SceneClear>();	// �N���A��ʂɈړ�
	}
	// P�L�[�Ń|�[�Y�A�|�[�Y����P�ŃR�}����
	if (m_debugState == DebugState::Normal && input.IsPressing("debug_pause"))
	{
		m_debugState = DebugState::Pause;
	}
	if (m_debugState == DebugState::Pause && input.IsPressing("debug_enter"))
	{
		m_debugState = DebugState::Normal;
	}
	if (m_debugState != DebugState::Pause || input.IsPressing("debug_pause"))
#endif
	{
		// �{�^������������|�[�Y��ʂ��J��
		if (m_isPause)
		{
			// �I����Ԃ��X�V
			UpdateSelect(input);

			// �V�[���؂�ւ�
			if (input.IsTriggered("OK"))
			{
				if (m_select == Select::kBack)
				{
					m_isPause = false;
				}
				else if (m_select == Select::kRetry)
				{
					return std::make_shared<ScenePlaying>(); // ���g���C����
				}
				else if (m_select == Select::kTitle)
				{
					return std::make_shared<SceneTitle>();	// �^�C�g����ʂɈړ�
				}
			}

			// �|�[�Y��ʂ����
			if (input.IsTriggered("pause"))
			{
				m_isPause = false;
			}
		}
		else
		{
			// �|�[�Y��ʂ�\��
			if (input.IsPressing("pause"))
			{
				m_isPause = true;
			}

			// �v���C���[�X�V
			m_pPlayer->Update(input, *m_pCamera, *m_pStage);

			// �J�����X�V
			m_pCamera->Update(input, *m_pPlayer, *m_pStage);
		}

		// �v���C���[���S�[��������N���A��ʂɈړ�
		if (m_pPlayer->GetIsGoal())
		{
			return std::make_shared<SceneClear>();
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePlaying::Draw()
{
	// �X�e�[�W�`��
	m_pStage->Draw();

	// �v���C���[�`��
	m_pPlayer->Draw(m_pDrawDebug);

	// �|�[�Y��ʕ\��
	if (m_isPause)
	{
		DrawPause();
	}

#ifdef _DEBUG	// �f�o�b�O�\��
	// �O���b�h�\��
	//m_pDrawDebug.DrawGrid();
	// ���݂̃V�[��
	DrawString(0, 0, "�v���C���", 0xffffff);
#endif
}


/// <summary>
/// �I����Ԃ��X�V
/// </summary>
/// <param name="input">����</param>
void ScenePlaying::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1������
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select - 1) % kSelectNum;	// �I����Ԃ�1�グ��
	}
}

/// <summary>
/// �|�[�Y��ʂ�\��
/// </summary>
void ScenePlaying::DrawPause()
{
	// �|�[�Y��ʂ�\��
	DrawBox(kPausePosX, kPausePosY, kPausePosX + kPauseWidth, kPausePosX + kPauseHeight, 0xff00000, true);

#ifdef _DEBUG
	DrawString(0, 10, "�|�[�Y��", 0xffffff);
#endif // _DEBUG
}
