#include "DxLib.h"
#include "ScenePlaying.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"

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
}


/// <summary>
/// ������
/// </summary>
void ScenePlaying::Init()
{
	m_pPlayer->Init();
	m_pCamera->Init();
	m_pStage->Init();
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">����</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	// �J�����X�V
	m_pCamera->Update(input);

	// �X�e�[�W�X�V
	m_pStage->Update();

	// �v���C���[�X�V
	m_pPlayer->SetCameraAngle(m_pCamera->GetAngle());
	m_pPlayer->Update(input, m_pStage);

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
	m_pStage->Draw();

	// �v���C���[�`��
	m_pPlayer->Draw(m_pDrawDebug);
}
