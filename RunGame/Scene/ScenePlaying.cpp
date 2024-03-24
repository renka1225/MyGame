#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "ManagerModel.h"
#include "Background.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Input.h"
#include "Game.h"
#include <memory>


/// <summary>
/// �R���X�g���N�^
/// </summary>
ScenePlaying::ScenePlaying():
	m_time(0),
	m_enemyPos(VGet(0.0f, 0.0f, 0.0f))
{
	m_pModel = std::make_shared<ManagerModel>();
	m_pBackground = std::make_shared<Background>(m_pModel);
	m_pPlayer = std::make_shared<Player>(m_pModel);
	m_pCamera = std::make_shared<Camera>();

	m_pEnemy.resize(kEnemyNum);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = std::make_shared<Enemy>(m_pModel);
	}
}


/// <summary>
/// ������
/// </summary>
void ScenePlaying::Init()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i]->Init(VGet(i * 100, 0.0f, 0.0f));
	}
}


/// <summary>
/// �X�V
/// </summary>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	// �^�C���X�V
	m_time++;

	// �N���A
	if (m_time >= kClearTime)
	{
		return std::make_shared<SceneClear>();
	}

	// �w�i�̍X�V
	m_pBackground->Update();
	// �v���C���[�̍X�V
	m_pPlayer->Update(input);
	// �J�����̍X�V
	m_pCamera->Update(m_pPlayer);
	// �G�̍X�V
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// �G�̍X�V
		m_pEnemy[i]->Update();
	}

#if _DEBUG
	// MEMO:�f�o�b�N�p�{�^��
	if (input.IsTriggered("debug"))
	{
		return std::make_shared<SceneClear>();
	}
	else if (input.IsTriggered("OK"))
	{
		return std::make_shared<SceneGameover>();
	}
#endif

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePlaying::Draw()
{
	// �w�i�̕`��
	m_pBackground->Draw();

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// �G�̕`��
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i]->Draw();
	}

	// �o�ߎ��Ԃ̕`��
	int milliSec = m_time * 1000 / 60;
	int sec = (milliSec / 1000) % 120;
	milliSec %= 1000;
	DrawFormatString(0, 50, 0xffffff, "time:%03d:%03d", sec, milliSec);

#if _DEBUG
	DrawFormatString(0, 0, 0xffffff, "�v���C���");
#endif
}


/// <summary>
/// �I��
/// </summary>
void ScenePlaying::End()
{
}
