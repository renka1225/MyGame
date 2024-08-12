#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "UIProduction.h"
#include "EffectManager.h"
#include "Player.h"
#include "EnemyTuto.h"
#include "Camera.h"
#include "Stage.h"
#include "ScenePause.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStage1.h"

namespace
{
	constexpr int kMaxBattleNum = 1;							// �ő�o�g����
	constexpr int kNextBattleTime = 150;						// ���̎������n�܂�܂ł̎���
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneStage1::SceneStage1(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage)
{
	m_pPlayer = pPlayer;
	m_pCamera = pCamera;
	m_pStage = pStage;
	m_pEnemy = std::make_shared<EnemyTuto>();
	m_battleNum = 0;
	m_nextBattleTime = kNextBattleTime;
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneStage1::~SceneStage1()
{
}


/// <summary>
/// ������
/// </summary>
void SceneStage1::Init()
{
	SceneStageBase::Init();
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <returns>�J�ڂ���V�[��</returns>
std::shared_ptr<SceneBase> SceneStage1::Update(Input& input)
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

		m_nextBattleTime--; // ���̎������n�܂�܂ł̎���

		m_pCamera->Update(input, *m_pPlayer);
		m_pPlayer->Update(input, *m_pCamera, *m_pEnemy, *m_pStage);
		m_pEnemy->Update(*m_pPlayer, *m_pStage, *this);
		if (m_nextBattleTime > 0) return shared_from_this();

		m_elapsedTime++; // �o�ߎ��Ԃ�i�߂�

		m_pEffect->Update(input, *m_pPlayer, *m_pEnemy); // �G�t�F�N�g�X�V

		// �G��HP��0�ɂȂ����ꍇ
		if (m_pEnemy->GetHp() <= 0)
		{
			m_clearTime.push_back(m_elapsedTime);
			return std::make_shared<SceneClear>(m_clearTime);
		}
		// �v���C���[��HP��0�ɂȂ����ꍇ
		if (m_pPlayer->GetHp() <= 0)
		{
			return std::make_shared<SceneGameover>(shared_from_this());
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
		return std::make_shared<SceneGameover>(shared_from_this());
	}
#endif

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneStage1::Draw()
{
	SceneStageBase::Draw();

	// ���oUI��\��
	m_pUIProduction->DrawStartProduction(m_nextBattleTime, m_battleNum, kMaxBattleNum);

	//MEMO:�P�x�𒲐�����
	//SetDrawBright(128, 128, 128);


#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�X�e�[�W1", 0xffffff);
	DrawFormatString(0, 200, 0xffffff, "%d", m_elapsedTime);
#endif
}