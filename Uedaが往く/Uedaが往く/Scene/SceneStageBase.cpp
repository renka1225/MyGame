#include "DxLib.h"
#include "Input.h"
#include "UIProduction.h"
#include "Light.h"
#include "Player.h"
#include "EnemyBase.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStageBase.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneStageBase::SceneStageBase():
	m_battleNum(0),
	m_nextBattleTime(0),
	m_elapsedTime(0)
{
	m_pUIProduction = std::make_shared<UIProduction>();
	Light::SetLight();
}


/// <summary>
/// �������R���X�g���N�^
/// </summary>
/// <param name="pPlayer">�v���C���[�Q��</param>
/// <param name="pCamera">�J�����Q��</param>
/// <param name="pStage">�X�e�[�W�Q��</param>
SceneStageBase::SceneStageBase(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage):
	m_pPlayer(pPlayer),
	m_pCamera(pCamera),
	m_pStage(pStage),
	m_pEnemy(nullptr),
	m_battleNum(0),
	m_nextBattleTime(0),
	m_elapsedTime(0)
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneStageBase::~SceneStageBase()
{
	Light::DeleteLight();
}


/// <summary>
/// ������
/// </summary>
void SceneStageBase::Init()
{
	m_pPlayer->Init();
	m_pCamera->Init();
	m_pEnemy->Init();
}


/// <summary>
/// �`��
/// </summary>
void SceneStageBase::Draw()
{
	// �X�e�[�W�`��
	m_pStage->Draw();
	// �v���C���[�`��
	m_pPlayer->Draw();
	// �G�`��
	m_pEnemy->Draw();

	// ���������\��
	//m_pUIProduction->DrawOperation();
}