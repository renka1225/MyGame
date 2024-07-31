#include "DxLib.h"
#include "Player.h"
#include "EnemyNinja.h"
#include "EnemyChef.h"
#include "EnemyAbe.h"
#include "Camera.h"
#include "Input.h"
#include "Vec2.h"
#include "Stage.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStage2.h"

namespace
{
	const char* const kFightTextPath = "data/UI/Fight!.png";	// "Fight"�̃e�L�X�g�摜�̃t�@�C���ʒu
	const Vec2 kFightTextPos = { 900, 500 };					// "Fight"�̃e�L�X�g�ʒu
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
	m_fightTextHandle = LoadGraph(kFightTextPath);
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
		m_nextBattleTime--;

		m_pCamera->Update(input, *m_pPlayer);
		m_pPlayer->Update(input, *m_pCamera, *m_pEnemy, *m_pStage);
		m_pEnemy->Update(*m_pPlayer, *m_pStage);
		if (m_nextBattleTime > 0) return shared_from_this();

		// �G��HP��0�ɂȂ����ꍇ
		if (m_pEnemy->GetHp() <= 0)
		{
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
			case 2: // �G�����ׂē|������
				// TODO:�N���A�����Ɉڍs����
				return std::make_shared<SceneClear>();
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

	if (m_nextBattleTime < kFightTextDispStart && m_nextBattleTime > 0)
	{
		int sizeW, sizeH;
		GetGraphSize(m_fightTextHandle, &sizeW, &sizeH);
		DrawRectRotaGraphF(kFightTextPos.x, kFightTextPos.y, 0, 0, sizeW, sizeH, kFightTextScele, 0.0f, m_fightTextHandle, true);
	}

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�X�e�[�W2", 0xffffff);
#endif
}


/// <summary>
/// �G��|���Ď��������n�܂�O�̏���
/// </summary>
void SceneStage2::UpdateNextBattle()
{
	m_pPlayer->Recovery();
	m_nextBattleTime = kNextBattleTime;
}
