#include "DxLib.h"
#include "MyLib.h"
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
	m_pPhysics = std::make_shared<Physics>();
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
	m_pPlayer->Init(m_pPhysics);
	m_pCamera->Init();
	m_pStage->Init(m_pPhysics);
}


/// <summary>
/// �I������
/// </summary>
void ScenePlaying::Final()
{
	m_pPlayer->Final(m_pPhysics);
	m_pStage->Final(m_pPhysics);
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">����</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
#ifdef _DEBUG
	// �f�o�b�O���[�h
	// P�L�[�Ń|�[�Y�A�|�[�Y����P�ŃR�}����
	if (debugState == DebugState::Normal && input.IsPressing("debug_pause"))
	{
		debugState = DebugState::Pause;
	}
	if (debugState == DebugState::Pause && input.IsPressing("debug_enter"))
	{
		debugState = DebugState::Normal;
	}
	if(debugState != DebugState::Pause || input.IsPressing("debug_pause"))
	{
#endif

		// �J�����X�V
		m_pCamera->Update(input, *m_pPlayer);

		// �X�e�[�W�X�V
		m_pStage->Update();

		// �v���C���[�X�V
		m_pPlayer->SetCameraAngle(m_pCamera->GetAngle());
		m_pPlayer->Update(input, *m_pStage);

		// ���������X�V
		m_pPhysics->Update();
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePlaying::Draw()
{
#ifdef _DEBUG		// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawFormatString(0, 0, 0xffffff, "�v���C���");
	// �O���b�h�\��
	m_pDrawDebug.DrawGrid();
#endif

	// �X�e�[�W�`��
	m_pStage->Draw(m_pDrawDebug);

	// �v���C���[�`��
	m_pPlayer->Draw(m_pDrawDebug);
}
