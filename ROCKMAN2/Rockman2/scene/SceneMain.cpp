#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "Bg.h"
#include "ScenePause.h"

#include "RecoverySmallHp.h"
#include "RecoveryGreatHp.h"
#include "RecoverySmallShot.h"
#include "RecoveryGreatShot.h"
#include "RecoveryLife.h"
#include "RecoveryFullHp.h"

#include "Player.h"
#include "ShotBase.h"

#include "Matasaburo.h"
#include "EnemyCat.h"
#include "EnemyBird.h"
#include "EnemyBear.h"
#include <cassert>

namespace
{
	// ��ʓ���1�x�ɏo����e��
	constexpr int kShotMax = 3;
	// ��ʓ���1�x�ɏo����񕜃A�C�e����
	constexpr int kRecoveryMax = 5;

	// �o�ꂷ��G��
	constexpr int kEnemyMax = 8;

	// �v���C���[�̉摜�T�C�Y
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 64;

	// �}�b�v�`�b�v�̃T�C�Y
	constexpr int kMapChipWidth = 32;
	constexpr int kMapChipHeight = 32;

	/*�|�[�Y���*/
	// �|�[�Y��ʂ̕����\���ʒu
	constexpr int kTextPosX = 840;
	constexpr int kTextPosY = 400;
	// �e���\���ʒu
	constexpr int kBarPosX = 860;
	constexpr int kBarPosY = 400;
	// �e���\���Ԋu
	constexpr int kBarInterval = 8;
	// �e���\���T�C�Y
	constexpr int kPauseShotNumWidth = 5;
	constexpr int kPauseShotNumHeightt = 20;
	// �e���\���Ԋu
	constexpr int kIntervalY = 70;

	/*�Q�[����*/
	// ���g�̃T�C�Y
	constexpr int kFrameSize = 200;
	// �c�@�A�G���\���ʒu
	constexpr int kInfoTextPosX = 30;	// ��
	constexpr int kInfoTextPosY = 300;	// �c
	// �e���\���ʒu
	constexpr int kShotNumDisPosX = Game::kScreenWidth - kFrameSize + 10;	// ��
	constexpr int kShotNumDisPosY = 300;									// �c
	// �e���\���Ԋu
	constexpr int kShotNumIntervalX = 8;	// ��
	constexpr int kShotNumIntervalY = 100;	// �c
	// �e���\���T�C�Y
	constexpr int kShotDisWidth = 3;	// ��
	constexpr int kShotDisHeight = 20;	// �c
}

SceneMain::SceneMain():
	m_drawValue(0),
	m_isGetFullHpRecovery(false),
	m_enemyTotalNum(kEnemyMax),
	m_isExistLineMove(false),
	m_isSceneGameOver(false),
	m_isSceneClear(false),
	m_fadeAlpha(255)
{
	// �v���C���[�̃������m��
	m_pPlayer = new Player{ this };

	// �w�i�̃������m��
	m_pBg = new Bg;
	m_pBg->SetPlayer(m_pPlayer);
	m_pPlayer->SetBg(m_pBg);

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
	CreateEnemy();

	// �񕜃A�C�e���̏�����
	m_pRecovery.resize(kRecoveryMax);
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		m_pRecovery[i] = nullptr; // ���g�p��Ԃɂ���
	}
}

SceneMain::~SceneMain()
{
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
	m_isSceneGameOver = false;
	m_isSceneClear = false;
	m_isExistLineMove = false;

	m_enemyTotalNum = kEnemyMax;

	// �|�[�Y��ʂ̏�����
	m_pPause->Init();

	// �v���C���[�̏�����
	assert(m_pPlayer);	// m_pPlayer == nullptr�̏ꍇ�~�܂�
	m_pPlayer->Init();

	// �w�i�̏�����
	m_pBg->Init();
	

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
	m_isGetFullHpRecovery = false;
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	// �v���C���[�̎c�@��0�����̏ꍇ
	if (m_pPlayer->GetLife() < 0)
	{
		m_isSceneGameOver = true; // �Q�[���I�[�o�[��ʂɑJ��
	}

	// TODO:�G�����ׂē|������N���A��ʂɑJ��
	if (m_enemyTotalNum <= 0)
	{
		m_isSceneClear = true;
	}

	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

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

	// �v���C���[�̌��ݒn���擾
	m_playerPos = m_pPlayer->GetPos();
	// �v���C���[�̓����蔻��
	Rect playerRect = m_pPlayer->GetColRect();

	// �v���C���[����ʓ��Ɉړ�������E�ʂ�\������
	if (m_playerPos.x >= 100 && !m_isGetFullHpRecovery)
	{
		DropFullHpRecovery();
	}

	// �e�̍X�V
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pShot[i]) continue;

		m_pShot[i]->SetBg(m_pBg);
		m_pShot[i]->Update();

		// �A�C�e��2���̏ꍇ
		if (m_pShot[i]->GetShotType() == ShotType::kShotLineMove)
		{
			// ��ʏ�ɑ��݂��邩
			if (m_pShot[i]->IsExist())
			{
				m_isExistLineMove = true;
			}
			else
			{
				m_isExistLineMove = false;
			}

			// �e�̓����蔻��
			Rect shotRect = m_pShot[i]->GetColRect();
			if (playerRect.IsCollision(shotRect))
			{
				m_pPlayer->RideLineMove(shotRect);
			}
		}

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
		if (!m_pEnemy[i]) continue;
		m_pEnemy[i]->SetBg(m_pBg);
		m_pEnemy[i]->Update();

		// �g�p�ς݂̓G�L�����N�^�[���폜
		if (!m_pEnemy[i]->IsExist())
		{
			// �G�̍��v�������炷
			m_enemyTotalNum--;

			// �m���ŃA�C�e�����h���b�v
			int getRandDrop = GetRand(100);

			if (getRandDrop <= 5)
			{
				DropHpSmallRecovery(i); // HP��(��)
			}
			else if (getRandDrop <= 8)
			{
				DropHpGreatRecovery(i);	// HP��(��)
			}
			else if (getRandDrop <= 13)
			{
				DropShotSmallRecovery(i); // �e�G�l���M�[(��)
			}
			else if (getRandDrop <= 16)
			{
				DropShotGreatRecovery(i); // �e�G�l���M�[(��)
			}
			else if (getRandDrop <= 19)
			{
				DropLifeRecovery(i);	// �c�@
			}
			
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
				// �A�C�e���Q���̏ꍇ�͓G�Ƃ̓����蔻��𖳎�����
				if (m_pShot[j]->GetShotType() != ShotType::kShotLineMove)
				{
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
	}

	// �񕜃A�C�e���̍X�V
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pRecovery[i]) continue;

		m_pRecovery[i]->SetBg(m_pBg);
		m_pRecovery[i]->Update();

		Rect recoveryRect = m_pRecovery[i]->GetColRect();	// �񕜃A�C�e���̓����蔻��
		// �v���C���[�Ɖ񕜃A�C�e���̓����蔻��
		if (playerRect.IsCollision(recoveryRect))
		{
			if (dynamic_cast<RecoverySmallHp*>(m_pRecovery[i])) // HP����
			{
				m_pPlayer->HpSmallRecovery();
			}
			else if (dynamic_cast<RecoveryGreatHp*>(m_pRecovery[i])) // HP���
			{
				m_pPlayer->HpGreatRecovery();
			}
			else if (dynamic_cast<RecoverySmallShot*>(m_pRecovery[i])) // �e����
			{
				m_pPlayer->ShotSmallRecovery();
			}
			else if (dynamic_cast<RecoveryGreatShot*>(m_pRecovery[i])) // �e���
			{
				m_pPlayer->ShotGreatRecovery();
			}
			else if (dynamic_cast<RecoveryLife*>(m_pRecovery[i])) // �c�@��
			{
				m_pPlayer->LifeRecovery();
			}
			else if (dynamic_cast<RecoveryFullHp*>(m_pRecovery[i])) // HP�S��
			{
				if (!m_isGetFullHpRecovery)  // E�ʂ��擾���ĂȂ��ꍇ
				{
					m_pPlayer->GetHpFullRecovery();
					m_isGetFullHpRecovery = true;
				}
			}

			// �擾������A�C�e��������
			delete m_pRecovery[i];
			m_pRecovery[i] = nullptr;
		}
	}

#ifdef _DEBUG
	// C�L�[�ŃN���A��ʂɈړ�����悤�ɂ���
	if (Pad::IsTrigger(pad & PAD_INPUT_3))
	{
		m_isSceneClear = true; // �N���A��ʂɑJ��
	}
#endif

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

	/*��ʉ��ɏ��\��*/
	DrawInfo();
	
	// �|�[�Y��ʂ̕\��
	m_pPause->Draw();

	/*�|�[�Y��ʕ\����*/
	if (m_pPause->IsExist())
	{
		DrawPause();
	}
}

/*�e�̐���*/
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

/*�A�C�e���h���b�v*/
void SceneMain::DropHpSmallRecovery(int enemyIndex) // HP����
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoverySmallHp;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropHpGreatRecovery(int enemyIndex) // HP���
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryGreatHp;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropShotSmallRecovery(int enemyIndex) // �e����
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoverySmallShot;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropShotGreatRecovery(int enemyIndex) // �e���
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryLife;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropLifeRecovery(int enemyIndex) // �c�@��
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryGreatShot;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropFullHpRecovery() // HP�S��
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryFullHp;
			m_pRecovery[i]->Start({ 500, 500 }); // �A�C�e���̈ʒu��ݒ�
			m_pRecovery[i]->Init();
			return;
		}
	}
}

/*�G�̐���*/
void SceneMain::CreateEnemy()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		switch (i)
		{
		case 0:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(300.0f, 600.0f);
			m_pEnemy[i]->Init();
			break;
		case 1:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(500.0f, 600.0f);
			m_pEnemy[i]->Init();
			break;
		case 2:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(1000.0f, 600.0f);
			m_pEnemy[i]->Init();
			break;
		case 3:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(400.0f, 600.0f);
			m_pEnemy[i]->Init();
			break;
		case 4:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(2000.0f, 600.0f);
			m_pEnemy[i]->Init();
			break;
		case 5:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(800.0f, 200.0f);
			m_pEnemy[i]->Init();
			break;
		case 6:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(1500.0f, 400.0f);
			m_pEnemy[i]->Init();
			break;
		case 7:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(2400.0f, 100.0f);
			m_pEnemy[i]->Init();
			break;
		case 8:
			m_pEnemy[i] = new EnemyBear;
			m_pEnemy[i]->Start(2300.0f, 300.0f);
			m_pEnemy[i]->Init();
			break;
		default:
			break;
		}
	}
}

/*�e���A�G���\��*/
void SceneMain::DrawInfo()
{
	DrawBox(0, 0, kFrameSize, Game::kScreenHeight, 0x000000, true); // ����
	DrawBox(Game::kScreenWidth - kFrameSize, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true); // �E��

	/*�c�@�AE�ʐ��A�c��G���������ɕ\��*/
	// E�ʐ��\��
	DrawFormatString(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY, 0xffffff, "E : %d", m_pPlayer->GetFullHpRecovery());
	// �c�@���\��
	DrawFormatString(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY * 2, 0xffffff, "�c�@��:%d", m_pPlayer->GetLife());
	// �G���\��
	DrawFormatString(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY * 3, 0xffffff, "�G��:%d / %d", m_enemyTotalNum, kEnemyMax);

	/*HP�A����̒e�����E���ɕ\��*/
	// HP
	DrawFormatString(kShotNumDisPosX, kShotNumDisPosY - 20, 0xffffff, "HP :");
	// ���݂�HP�������l�p��`�悷��
	for (int i = 0; i < m_pPlayer->GetHp(); i++)
	{
		DrawBox(kShotNumDisPosX + kShotNumIntervalX * i,
			kShotNumDisPosY,
			(kShotNumDisPosX + kShotNumIntervalX * i) + kShotDisWidth,
			kShotNumDisPosY + kPauseShotNumHeightt,
			0xeee8aa, true);
	}

	// TODO:�I�𒆂̕��킪������悤�ɂ���

	// ���^��
	DrawFormatString(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY - 20, 0xffffff, "M :");
	for (int i = 0; i < m_pPlayer->GetMetalEnergy(); i++)
	{
		DrawBox(kShotNumDisPosX + kShotNumIntervalX * i,
			kShotNumDisPosY + kShotNumIntervalY,
			(kShotNumDisPosX + kShotNumIntervalX * i) + kShotDisWidth,
			kShotNumDisPosY + kShotNumIntervalY + kPauseShotNumHeightt,
			0xc0c0c0, true);
	}

	// �t�@�C�A
	DrawFormatString(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY * 2 - 20, 0xffffff, "F :");
	for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++)
	{
		DrawBox(kShotNumDisPosX + kShotNumIntervalX * i,
			kShotNumDisPosY + kShotNumIntervalY * 2,
			(kShotNumDisPosX + kShotNumIntervalX * i) + kShotDisWidth,
			kShotNumDisPosY + kShotNumIntervalY * 2 + kPauseShotNumHeightt,
			0xff4500, true);
	}

	// 2��
	DrawFormatString(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY * 3 - 20, 0xffffff, "L :");
	for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++)
	{
		DrawBox(kShotNumDisPosX + kShotNumIntervalX * i,
			kShotNumDisPosY + kShotNumIntervalY * 3,
			(kShotNumDisPosX + kShotNumIntervalX * i) + kShotDisWidth,
			kShotNumDisPosY + kShotNumIntervalY * 3 + kPauseShotNumHeightt,
			0xb22222, true);
	}
}

void SceneMain::DrawPause()
{
	// ���݂�HP��\��
	DrawFormatString(kTextPosX, kTextPosY, 0xffffff, "P :");
	for (int i = 0; i < m_pPlayer->GetHp(); i++) // ���݂�HP�������l�p��`�悷��
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kPauseShotNumHeightt,
			0xeee8aa, true);
	}

	// ���݂̒e�G�l���M�[����\��
	// ���^��
	DrawFormatString(kTextPosX, kTextPosY + kIntervalY, 0xffffff, "M :");
	for (int i = 0; i < m_pPlayer->GetMetalEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY + kPauseShotNumHeightt,
			0xc0c0c0, true);
	}

	// �t�@�C�A�[
	DrawFormatString(kTextPosX, kTextPosY + kIntervalY * 2, 0xffffff, "F :");
	for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY * 2,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY * 2 + kPauseShotNumHeightt,
			0xff4500, true);
	}

	// �A�C�e��2��
	DrawFormatString(kTextPosX, kTextPosY + kIntervalY * 3, 0xffffff, "L :");
	for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY * 3,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY * 3 + kPauseShotNumHeightt,
			0xb22222, true);
	}

	// ���݂�E�ʐ���\��
	DrawFormatString(kTextPosX, kTextPosY + kIntervalY * 4, 0xffffff, "E : %d", m_pPlayer->GetFullHpRecovery());
}
