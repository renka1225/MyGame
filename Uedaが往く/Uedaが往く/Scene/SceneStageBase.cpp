#include "DxLib.h"
#include "Input.h"
#include "UI.h"
#include "UIProduction.h"
#include "Sound.h"
#include "Light.h"
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
	constexpr int kChangeColorTime = 150;						  // ��ʂ̕\����ύX���鎞��
	constexpr int kClearStagingTime = 180;						  // ��ʂ̕\����ύX���鎞��
	constexpr int kNextBattleTime = 150;						  // ���̎������n�܂�܂ł̎���
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneStageBase::SceneStageBase() :
	m_battleNum(0),
	m_nextBattleTime(kNextBattleTime),
	m_clearStagingTime(kClearStagingTime),
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
	m_clearStagingTime(0),
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
	m_pUI->DrawOperation();
}


/// <summary>
/// �N���A���o���s��
/// </summary>
void SceneStageBase::ClearStaging()
{
	// SE��炷
	if (!CheckSoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kClearCheers)]))
	{
		PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kClearCheers)], DX_PLAYTYPE_BACK);
	}

	if (m_clearStagingTime >= kClearStagingTime - kChangeColorTime)
	{
		// ��ʂ̐F��ς���
		SetLightDifColor(GetColorF(0.3f, 0.7f, 1.0f, 0.0f));
		m_clearStagingTime--;
		return;
	}

	// �N���A���o�����Z�b�g
	m_clearStagingTime = 0;
	SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
	StopSoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kClearCheers)]);
}


/// <summary>
/// �G��|���Ď��������n�܂�O�̏���
/// </summary>
void SceneStageBase::UpdateNextBattle()
{
	m_nextBattleTime = kNextBattleTime;
	m_clearStagingTime = kClearStagingTime;
	// �v���C���[�̈ʒu�A�J�����ʒu���ŏ��̏�Ԃɖ߂�
	m_pPlayer->Recovery();
	Init();
}
