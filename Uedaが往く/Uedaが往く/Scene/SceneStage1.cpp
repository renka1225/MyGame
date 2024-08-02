#include "DxLib.h"
#include "Player.h"
#include "EnemyTuto.h"
#include "Camera.h"
#include "Input.h"
#include "Vec2.h"
#include "Stage.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStage1.h"

namespace
{
	const char* const kFightTextPath = "data/UI/Fight!.png";	// "Fight"�̃e�L�X�g�摜�̃t�@�C���ʒu
	const Vec2 kFightTextPos = { 900, 500 };					// "Fight"�̃e�L�X�g�ʒu
	constexpr float kFightTextScele = 0.6f;						// "Fight"�̃e�L�X�g�T�C�Y
	constexpr int kFightTextDispStart = 80;						// "Fight"�̃e�L�X�g��\�����n�߂鎞��

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
	m_battleNum = kMaxBattleNum;
	m_nextBattleTime = kNextBattleTime;
	m_fightTextHandle = LoadGraph(kFightTextPath);
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
		m_pPlayer->Update(input, *m_pCamera, *m_pEnemy, *m_pStage);
		m_pCamera->Update(input, *m_pPlayer);
		m_pEnemy->Update(*m_pPlayer, *m_pStage);

		// �G��HP��0�ɂȂ����ꍇ
		if (m_pEnemy->GetHp() <= 0)
		{
			return std::make_shared<SceneClear>();
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
void SceneStage1::Draw()
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
	DrawString(0, 0, "�X�e�[�W1", 0xffffff);
#endif
}