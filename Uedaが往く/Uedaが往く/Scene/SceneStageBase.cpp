#include "DxLib.h"
#include "Input.h"
#include "UIProduction.h"
#include "Light.h"
#include "EffectManager.h"
#include "Player.h"
#include "EnemyBase.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStageBase.h"

namespace
{
	const VECTOR kPlayerInitPos = VGet(2600.0f, 69.0f, 4240.0f);  // �v���C���[�̏����ʒu
	const VECTOR kEnemyInitPos = VGet(2660, 69.0f, 4280.0f);	  // �G�̏����ʒu
	constexpr int kNextBattleTime = 150;						  // ���̎������n�܂�܂ł̎���
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneStageBase::SceneStageBase():
	m_battleNum(0),
	m_nextBattleTime(kNextBattleTime),
	m_elapsedTime(0)
{
	m_pUIProduction = std::make_shared<UIProduction>();
	m_pEffect = std::make_shared<EffectManager>();
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
	m_pPlayer->Init(kPlayerInitPos);
	m_pCamera->Init();
	m_pEnemy->Init(kEnemyInitPos);
	m_pEffect->Init();
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
	// �G�t�F�N�g�`��
	m_pEffect->Draw();

	// ���������\��
	//m_pUIProduction->DrawOperation();
}


/// <summary>
/// �G��|���Ď��������n�܂�O�̏���
/// </summary>
void SceneStageBase::UpdateNextBattle()
{
	m_nextBattleTime = kNextBattleTime;
	// ��ʏ�Ɏc�����G�t�F�N�g���폜����
	m_pEffect->ClearEffect();
	// �v���C���[�̈ʒu�A�J�����ʒu���ŏ��̏�Ԃɖ߂�
	m_pPlayer->Recovery();
	Init();
}
