#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "Bg.h"
#include "ScenePause.h"

#include "RecoveryBase.h"
#include "RecoverySmallHp.h"
#include "RecoverySmallShot.h"

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

	// �|�[�Y��ʂ̕����\���ʒu
	constexpr int kTextPosX = 510;
	// �o�[�̕\���ʒu
	constexpr int kBarPosX = 540;
	// �o�[�̕\���Ԋu
	constexpr int kBarInterval = 8;

	// �o�[�̎l�p�̃T�C�Y
	constexpr int kBarWidth = 5;
	constexpr int kBarHeight = 20;

	// Y���W�̕\���ʒu�̊Ԋu
	constexpr int kInterval = 60;
	// �����A�o�[�̕\���ʒu
	constexpr int kDisPosY = 200;
}

SceneMain::SceneMain():
	m_drawValue(0),
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

	// �|�[�Y��ʂ̃������m��
	m_pPause = new ScenePause{ m_pPlayer };

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

	// �|�[�Y��ʂ̃������m��
	delete m_pPause;
	m_pPause = nullptr;

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

	// �|�[�Y��ʂ̏�����
	m_pPause->Init();

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

	// �|�[�Y��ʂ̍X�V
	m_pPause->Update();

	// �|�[�Y��ʂ��\������Ă���ꍇ��ʂ��~�߂�
	if (m_pPause->IsExist())
	{
		return;
	}

	// �w�i�̍X�V
	m_pBg->Update();

	// �v���C���[�̍X�V
	m_pPlayer->Update();

	Vec2 playerPos = m_pPlayer->GetPos();		// �v���C���[�̌��ݒn���擾
	Rect playerRect = m_pPlayer->GetColRect();	// �v���C���[�̓����蔻��
	Rect mapChipRect = m_pBg->GetColRect(playerPos.x / 32, playerPos.y / 32); // �}�b�v�`�b�v�̓����蔻����擾����
		

	// �v���C���[�������W�ɓ��B������G��o�ꂳ����
	/*if (playerPos.x == 30)
	{
		CreateMatasaburo();
	}*/

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
			// �A�C�e���h���b�v
			DropItem();

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

		Rect recoveryRect = m_pRecovery[i]->GetColRect();	// �񕜃A�C�e���̓����蔻��

		// �v���C���[�Ɖ񕜃A�C�e���̓����蔻��
		if (playerRect.IsCollision(recoveryRect))
		{
			m_pPlayer->HpSmallRecovery();

			// �擾������A�C�e��������
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

	// ���݂�HP�������l�p��`�悷��
	for (int i = 0; i < m_pPlayer->GetHp(); i++)
	{
		DrawBox(10, 10 + 10 * i, 40, (10 + 10 * i) + 5, 0xeee8aa, true);
	}

	// ���ݑI�𒆂̕���̒e��������ɕ\��
	if (m_pPlayer->IsMetal()) // ���^��
	{
		for (int i = 0; i < m_pPlayer->GetMetalEnergy(); i++)
		{
			DrawBox(50, 10 + 10 * i, 80, (10 + 10 * i) + 5, 0xc0c0c0, true);
		}
	}
	if (m_pPlayer->IsFire()) // �t�@�C�A
	{
		for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++)
		{
			DrawBox(50, 10 + 10 * i, 80, (10 + 10 * i) + 5, 0xff4500, true);
		}
	}
	if (m_pPlayer->IsLineMove()) // 2��
	{
		for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++)
		{
			DrawBox(50, 10 + 10 * i, 80, (10 + 10 * i) + 5, 0xb22222, true);
		}
	}

	// �|�[�Y��ʂ̕\��
	m_pPause->Draw();

	/*�|�[�Y��ʕ\����*/
	if (m_pPause->IsExist())
	{
		// ���݂�HP��\��
		DrawFormatString(kTextPosX, kDisPosY, 0xffffff, "P :");
		for (int i = 0; i < m_pPlayer->GetHp(); i++) // ���݂�HP�������l�p��`�悷��
		{
			DrawBox(kBarPosX + kBarInterval * i, kDisPosY, (kBarPosX + kBarInterval * i) + kBarWidth, kDisPosY + kBarHeight, 0xeee8aa, true);
		}

		// ���݂̒e�G�l���M�[����\��
		// ���^��
		DrawFormatString(kTextPosX, kDisPosY + kInterval, 0xffffff, "M :");
		for (int i = 0; i < m_pPlayer->GetMetalEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
		{
			DrawBox(kBarPosX + kBarInterval * i, kDisPosY + kInterval, (kBarPosX + kBarInterval * i) + kBarWidth, kDisPosY + kInterval + kBarHeight, 0xeee8aa, true);
		}

		// �t�@�C�A�[
		DrawFormatString(kTextPosX, kDisPosY + kInterval * 2, 0xffffff, "F :");
		for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
		{
			DrawBox(kBarPosX + kBarInterval * i, kDisPosY + kInterval * 2, (kBarPosX + kBarInterval * i) + kBarWidth, kDisPosY + kInterval * 2 + kBarHeight, 0xeee8aa, true);
		}

		// �A�C�e��2��
		DrawFormatString(kTextPosX, kDisPosY + kInterval * 3, 0xffffff, "2 :");
		for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
		{
			DrawBox(kBarPosX + kBarInterval * i, kDisPosY + kInterval * 3, (kBarPosX + kBarInterval * i) + kBarWidth, kDisPosY + kInterval * 3 + kBarHeight, 0xeee8aa, true);
		}

		// ���݂̎c�@����\��
		DrawFormatString(kTextPosX, kDisPosY + kInterval * 4, 0xffffff, "�c�@��:%d", m_pPlayer->GetLife());
	}
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

void SceneMain::DropItem()
{
	//�g���Ă��Ȃ��ꏊ�ɃA�h���X��ۑ�����
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])	// nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			// HP��(��)�𐶐�����
			m_pRecovery[i] = new RecoverySmallHp;
			m_pRecovery[i]->Init();
			m_pRecovery[i]->Start(m_pEnemy[i]->GetPos());
			return;
		}
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
