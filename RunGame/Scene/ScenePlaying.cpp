#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"
#include <memory>

/// <summary>
/// �萔
/// </summary>
namespace
{
	// �Q�[������
	constexpr int kClearTime = 60 * 120;
}

ScenePlaying::ScenePlaying():
	m_time(0)
{
	m_pPlayer = std::make_shared<Player>();
	m_pEnemy = std::make_shared<Enemy>();
	m_pCamera = std::make_shared<Camera>();
}


/// <summary>
/// ������
/// </summary>
void ScenePlaying::Init()
{
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

	// �v���C���[�̍X�V
	m_pPlayer->Update(input);
	// �G�̍X�V
	m_pEnemy->Update();
	// �J�����̍X�V
	m_pCamera->Update(m_pPlayer);

#if _DEBUG
	// MEMO:�f�o�b�N�p
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
	// �o�ߎ��Ԃ̕`��
	int milliSec = m_time * 1000 / 60;
	int sec = (milliSec / 1000) % 120;
	milliSec %= 1000;
	DrawFormatString(0, 50, 0xffffff, "time:%03d:%03d", sec, milliSec);

	// �v���C���[�̕`��
	m_pPlayer->Draw();
	// �G�̕`��
	m_pEnemy->Draw();

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
