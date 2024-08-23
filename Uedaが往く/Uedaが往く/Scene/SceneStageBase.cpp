#include "DxLib.h"
#include "Input.h"
#include "Game.h"
#include "UI.h"
#include "UIBattle.h"
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
	const char* kClearBackHandlePath = "data/UI/clearBack.png";	  // �摜�̃p�X
	const VECTOR kPlayerInitPos = VGet(2600.0f, 69.0f, 4240.0f);  // �v���C���[�̏����ʒu
	const VECTOR kEnemyInitPos = VGet(2660, 69.0f, 4280.0f);	  // �G�̏����ʒu
	constexpr int kChangeColorTime = 220;						  // ��ʂ̕\����ύX���鎞��
	constexpr int kClearStagingTime = 240;						  // �N���A���o�̎���
	constexpr int kNextBattleTime = 150;						  // ���̎������n�܂�܂ł̎���
	constexpr int kBattleEndSoundTime = 60;						  // �R���O��SE��炷����
	constexpr int kClearBackColor = 0x0f2699;					  // �N���A���̔w�i�F
	constexpr int kMULAPal = 200;								  // ��Z�u�����h�l
	constexpr int kAddPal = 80;									  // ���Z�u�����h�l

	constexpr int kStartFadeAlpha = 255; // �X�^�[�g���̃t�F�[�h�l
	constexpr int kFadeFrame = 8;		 // �t�F�[�h�ω���
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneStageBase::SceneStageBase() :
	m_battleNum(0),
	m_nextBattleTime(kNextBattleTime),
	m_clearStagingTime(kClearStagingTime),
	m_elapsedTime(0),
	m_isPause(false)
{
	m_fadeAlpha = kStartFadeAlpha;
	m_pUIBattle = std::make_shared<UIBattle>();
	Light::SetLight();
	m_clearBackHandle = LoadGraph(kClearBackHandlePath);
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
	m_elapsedTime(0),
	m_isPause(false),
	m_clearBackHandle(-1)
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneStageBase::~SceneStageBase()
{
	Light::DeleteLight();
	DeleteGraph(m_clearBackHandle);
}


/// <summary>
/// ������
/// </summary>
void SceneStageBase::Init()
{
	if (!m_isPause)
	{
		m_pPlayer->Init(kPlayerInitPos);
		m_pCamera->Init();
		m_pEnemy->Init(kEnemyInitPos);
	}

	m_isPause = false;
}


/// <summary>
/// �`��
/// </summary>
void SceneStageBase::Draw()
{
	m_pStage->Draw();			  // �X�e�[�W�`��

	m_pPlayer->Draw();			  // �v���C���[�`��
	m_pEnemy->Draw();			  // �G�`��

	m_pUIBattle->DrawOperation(); // ���������\��

	// �N���A����ʂ̐F����ς���
	if (m_clearStagingTime < kClearStagingTime && m_clearStagingTime >= 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, kMULAPal);
		DrawGraph(0, 0, m_clearBackHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawBlendMode(DX_BLENDMODE_ADD, kAddPal);
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kClearBackColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	DrawFade();	// �t�F�[�h�C���A�E�g�`��
}


/// <summary>
/// �N���A���o���s��
/// </summary>
void SceneStageBase::ClearStaging()
{
	// SE��炷
	if (m_clearStagingTime >= kClearStagingTime - kBattleEndSoundTime)
	{
		if (!CheckSoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kBattleEnd)]))
		{
			PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kBattleEnd)], DX_PLAYTYPE_BACK);
		}
	}
	else
	{
		if (!CheckSoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kClearCheers)]))
		{
			PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kClearCheers)], DX_PLAYTYPE_BACK);
		}
	}

	if (m_clearStagingTime >= kClearStagingTime - kChangeColorTime)
	{
		// ��ʂ̐F��ς���
		//SetLightDifColor(GetColorF(0.0f, 0.3f, 0.5f, 0.0f));

		m_clearStagingTime--;
		return;
	}

	// �N���A���o�����Z�b�g
	m_clearStagingTime = 0;
	//SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
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

	FadeIn(kFadeFrame); // �t�F�[�h�C��
}