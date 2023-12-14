#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "Bg.h"

#include "RecoveryBase.h"
#include "RecoverySmallHp.h"
#include "RecoveryGreatHp.h"
#include "RecoveryFullHp.h"
#include "RecoverySmallShot.h"
#include "RecoveryGreatShot.h"
#include "RecoveryLife.h"

#include "Player.h"

#include "ShotBase.h"

#include "Matasaburo.h"
#include <cassert>

namespace
{
	// ��ʓ���1�x�ɏo����e��
	constexpr int kShotMax = 3;
	// 1�x�ɓo��ł���G��
	constexpr int kEnemyMax = 5;
	// ��ʓ���1�x�ɏo����񕜃A�C�e����
	constexpr int kRecoveryMax = 20;
}

SceneMain::SceneMain():
	m_isSceneEnd(false)
{
	// �v���C���[�̃O���t�B�b�N���[�h
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);
	m_bgHandle = LoadGraph("data/image/backGround.png");
	assert(m_bgHandle != -1);
	m_mapHandle = LoadGraph("data/image/map.png");
	assert(m_mapHandle != -1);
	m_enemyHandle = LoadGraph("data/image/Enemy/matasaburo.png");
	assert(m_bgHandle != -1);

	// �w�i�̃������m��
	m_pBg = new Bg;
	m_pBg->SetHandle(m_bgHandle);
	m_pBg->SetMapHandle(m_mapHandle);

	// �v���C���[�̃������m��
	m_pPlayer = new Player{ this, m_pBg };
	m_pPlayer->SetHandle(m_playerHandle);	// Player�ɃO���t�B�b�N�̃n���h����n��

	// �V���b�g�̏�����
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr; // ���g�p��Ԃɂ���
	}

	// �G�̏�����
	m_pEnemy.resize(kEnemyMax);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = nullptr; // ���g�p��Ԃɂ���
	}

	// �񕜃A�C�e���̏�����
	m_pRecovery.resize(kRecoveryMax);
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		m_pRecovery[i] = nullptr; // ���g�p��Ԃɂ���
	}
}

SceneMain::~SceneMain()
{
	// ����������O���t�B�b�N���폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_enemyHandle);

	// �w�i�̃��������
	delete m_pBg;
	m_pBg = nullptr;

	// �v���C���[�̃��������
	delete m_pPlayer;
	m_pPlayer = nullptr;

	// �V���b�g�̃��������
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])
		{
			// nullptr�łȂ��ꍇ�Anullptr������
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}

	// �G�̃��������
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			// nullptr�łȂ��ꍇ�Anullptr������
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;
		}
	}

	// �񕜃A�C�e���̃��������
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (m_pRecovery[i])
		{
			// nullptr�łȂ��ꍇ�Anullptr������
			delete m_pRecovery[i];
			m_pRecovery[i] = nullptr;
		}
	}
}

void SceneMain::Init()
{
	// ��ʑJ�ڂ̏�����
	m_isSceneEnd = false;

	// �w�i�̏�����
	m_pBg->Init();

	// �v���C���[�̏�����
	assert(m_pPlayer);	// m_pPlayer == nullptr�̏ꍇ�~�܂�
	m_pPlayer->Init();
	

	// �G�̏�����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			m_pEnemy[i]->Init();
		}
	}

	// �񕜃A�C�e���̏�����
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (m_pRecovery[i])
		{
			m_pRecovery[i]->Init();
		}
	}
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	// �v���C���[�̎c�@��0�����̏ꍇ
	if (m_pPlayer->GetLife() < 0)
	{
		m_isSceneEnd = true; // �Q�[���I�[�o�[��ʂɑJ��
	}

	// �w�i�̍X�V
	m_pBg->Update();

	// �v���C���[�̍X�V
	m_pPlayer->Update();

	Rect playerRect = m_pPlayer->GetColRect();	// �v���C���[�̓����蔻��
	Vec2 playerPos = m_pPlayer->GetPos();		// �v���C���[�̌��ݒn���擾

	// �v���C���[����ʒ����Ɉړ�������G��o�ꂳ����
	if (playerPos.x == Game::kScreenWidth / 2)
	{
		CreateMatasaburo();
	}

	// �e�̍X�V
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pShot[i]) continue;

		m_pShot[i]->Update();

		// ��ʊO�ɏo���烁�������������
		if (!m_pShot[i]->IsExist())
		{
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}

	// �G�̍X�V
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pEnemy[i]) continue;
		m_pEnemy[i]->Update();

		// �g�p�ς݂̓G�L�����N�^�[���폜
		if (!m_pEnemy[i]->IsExist())
		{
			// ���������������
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;	// nullptr������
		}
		else
		{
			// �G�ƃv���C���[�̓����蔻��
			Rect enemyRect = m_pEnemy[i]->GetColRect();
			if (playerRect.IsCollision(enemyRect))
			{
				m_pPlayer->OnDamage();
			}

			for (int j = 0; j < m_pShot.size(); j++)
			{
				// nullptr�Ȃ珈���͍s��Ȃ�
				if (!m_pShot[j]) continue;

				// �G�ƒe�̓����蔻��
				Rect shotRect = m_pShot[j]->GetColRect(); // �e�̓����蔻��
				if (shotRect.IsCollision(enemyRect))
				{
					m_pEnemy[i]->OnDamage();
				}
				if (enemyRect.IsCollision(shotRect))
				{
					// �e���폜
					delete m_pShot[j];
					m_pShot[j] = nullptr;
				}
			}
		}
	}

	// �񕜃A�C�e���̍X�V
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pRecovery[i]) continue;

		m_pRecovery[i]->Update();

		// ��ʊO�ɏo���烁�������������
		if (!m_pRecovery[i]->IsExist())
		{
			delete m_pRecovery[i];
			m_pRecovery[i] = nullptr;
		}
	}
}

void SceneMain::Draw()
{
	// �`���X�N���[�����N���A����
	ClearDrawScreen();

	// �w�i�̕`��
	m_pBg->Draw();

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// �e�̕`��
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pShot[i])continue;
		m_pShot[i]->Draw();
	}

	// �G�̕`��
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pEnemy[i])continue;
		m_pEnemy[i]->Draw();
	}

	// �񕜃A�C�e���̕`��
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pRecovery[i])continue;
		m_pRecovery[i]->Draw();
	}

	// ���݂�HP��\��
	DrawFormatString(8, 8, 0xffffff, "HP:%.2f", m_pPlayer->GetHp());
	// ���݂̎c�@����\��
	DrawFormatString(8, 28, 0xffffff, "�c�@��:%d", m_pPlayer->GetLife());
	// ���݂̒e�G�l���M�[����\��
	DrawFormatString(8, 48, 0xffffff, "���^��: %.2f", m_pPlayer->GetMetalEnergy());
	DrawFormatString(8, 68, 0xffffff, "�t�@�C���[: %.2f", m_pPlayer->GetFireEnergy());
	DrawFormatString(8, 88, 0xffffff, "�A�C�e��2��: %.2f", m_pPlayer->GetLineEnergy());

}

// �e�̐���
bool SceneMain::AddShot(ShotBase* pShot)
{
	// nullptr��n���ꂽ��~�܂�
	assert(pShot);

	for (int i = 0; i < m_pShot.size(); i++)
	{
		// �g�p���Ȃ玟�̃`�F�b�N���s��
		if (m_pShot[i])continue;

		// m_pShot[i] == nullptr�Ȃ̂ŐV�����o�^����
		m_pShot[i] = pShot;
		// �o�^������I��
		return true;
	}

	// m_pShot�Ƀ|�C���^��o�^�ł��Ȃ�����
	delete pShot;
	return false;
}

bool SceneMain::AddItem(RecoveryBase* pRecovery)
{
	// nullptr��n���ꂽ��~�܂�
	assert(pRecovery);

	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// �g�p���Ȃ玟�̃`�F�b�N���s��
		if (m_pRecovery[i]) continue;

		// m_pRecovery[i] == nullptr�Ȃ̂ŐV�����o�^����
		m_pRecovery[i] = pRecovery;
		// �o�^������I��
		return true;
	}
}

// �G�̐���
void SceneMain::CreateMatasaburo()
{
	//�g���Ă��Ȃ��ꏊ�ɃA�h���X��ۑ�����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	// nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			m_pEnemy[i] = new Matasaburo;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	// 1�̕����������m�ۂł����炻�̎��_�ŏI��
		}
	}
}
