#include "DxLib.h"
#include "Vec2.h"
#include "Game.h"
#include "Input.h"
#include "UIProduction.h"
#include "Player.h"
#include "EnemyNinja.h"
#include "EnemyChef.h"
#include "EnemyAbe.h"
#include "Camera.h"
#include "Stage.h"
#include "ScenePause.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStage2.h"

namespace
{
	const char* const kFightTextPath = "data/UI/Fight!.png";	// "Fight"�̃e�L�X�g�摜�̃t�@�C���ʒu
	const Vec2 kFightTextPos = { 960, 500 };					// "Fight"�̃e�L�X�g�ʒu
	constexpr float kFightTextScele = 0.6f;						// "Fight"�̃e�L�X�g�T�C�Y
	constexpr int kFightTextDispStart = 80;						// "Fight"�̃e�L�X�g��\�����n�߂鎞��

	constexpr int kMaxBattleNum = 3;							// �ő�o�g����
	constexpr int kNextBattleTime = 150;						// ���̎������n�܂�܂ł̎���
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[�Q��</param>
/// <param name="camera">�J�����Q��</param>
/// <param name="pStage">�X�e�[�W�Q��</param>
SceneStage2::SceneStage2(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage)
{
	m_pPlayer = pPlayer;
	m_pCamera = pCamera;
	m_pStage = pStage;
	m_pEnemy = std::make_shared<EnemyNinja>();
	m_battleNum = 0;
	m_nextBattleTime = kNextBattleTime;
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneStage2::~SceneStage2()
{
}


/// <summary>
/// ������
/// </summary>
void SceneStage2::Init()
{
	SceneStageBase::Init();
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <returns>�J�ڐ�̃V�[��</returns>
std::shared_ptr<SceneBase> SceneStage2::Update(Input& input)
{
#ifdef _DEBUG	// �f�o�b�O���[�h
	// P�L�[�Ń|�[�Y�A�|�[�Y����P�ŃR�}����
	if (m_debugState == DebugState::Normal && input.IsTriggered("debug_pause"))
	{
		m_debugState = DebugState::Pause;
	}
	if (m_debugState == DebugState::Pause && input.IsTriggered("debug_enter"))
	{
		m_debugState = DebugState::Normal;
	}
	if (m_debugState != DebugState::Pause || input.IsTriggered("debug_pause"))
#endif
	{
		// �|�[�Y��ʂ��J��
		if (input.IsTriggered("pause"))
		{
			return std::make_shared<ScenePause>(shared_from_this());
		}

		m_nextBattleTime--;

		m_pCamera->Update(input, *m_pPlayer);
		m_pPlayer->Update(input, *m_pCamera, *m_pEnemy, *m_pStage);
		m_pEnemy->Update(*m_pPlayer, *m_pStage, *this);
		if (m_nextBattleTime > 0) return shared_from_this();

		m_elapsedTime++; // �o�ߎ��Ԃ�i�߂�

		// �G��HP��0�ɂȂ����ꍇ
		if (m_pEnemy->GetHp() <= 0)
		{
			m_clearTime.push_back(m_elapsedTime);
			m_elapsedTime = 0;

			// ���̓G��o�ꂳ����
			switch (m_battleNum)
			{
			case 0:	// 2���
				m_pEnemy = nullptr;
				m_pEnemy = std::make_shared<EnemyChef>();
				UpdateNextBattle();
				break;
			case 1:	// 3���
				m_pEnemy = nullptr;
				m_pEnemy = std::make_shared<EnemyAbe>();
				UpdateNextBattle();
				break;
			case 2: // ������
				return std::make_shared<SceneClear>(m_clearTime);
				break;
			default:
				break;
			}

			m_battleNum++;
		}

		// �v���C���[��HP��0�ɂȂ����ꍇ
		if (m_pPlayer->GetHp() <= 0)
		{
			return std::make_shared<SceneGameover>();
		}
	}

#ifdef _DEBUG
	// �G��HP��0�ɂ���
	m_pEnemy->DebugDamage(input);
	// �V�[���J��
	if (input.IsTriggered("debug_clear"))
	{
		return std::make_shared<SceneClear>();
	}
	else if (m_pPlayer->GetHp() <= 0.0f || input.IsTriggered("debug_gameover"))
	{
		return std::make_shared<SceneGameover>();
	}
#endif

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneStage2::Draw()
{
	SceneStageBase::Draw();
	// ���oUI��\��
	m_pUIProduction->DrawStartProduction(m_nextBattleTime, m_battleNum, kMaxBattleNum);

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�X�e�[�W2", 0xffffff);
	DrawFormatString(0, 200, 0xffffff, "%d", m_elapsedTime);
#endif
}


/// <summary>
/// �G��|���Ď��������n�܂�O�̏���
/// </summary>
void SceneStage2::UpdateNextBattle()
{
	// TODO:�v���C���[�̈ʒu�A�J�����ʒu���ŏ��̏�Ԃɖ߂�
	m_pPlayer->Recovery();
	m_pPlayer->Init();
	m_pCamera->Init();
	m_pEnemy->Init();
	m_nextBattleTime = kNextBattleTime;
}
