#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "FontManager.h"
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
	constexpr int kEnemyMax = 10;

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
	constexpr int kBarPosX = 840;
	constexpr int kBarPosY = 430;
	// �e���\���Ԋu
	constexpr int kBarInterval = 10;
	// �e���\���T�C�Y
	constexpr int kPauseShotNumWidth = 18;
	constexpr int kPauseShotNumHeight = 20;
	// �e���\���Ԋu
	constexpr int kIntervalY = 70;

	/*�Q�[����*/
	// ���g�̃T�C�Y
	constexpr int kFrameSize = 270;
	// �c�@�A�G���\���ʒu
	constexpr int kInfoTextPosX = 30;	// ��
	constexpr int kInfoTextPosY = 300;	// �c
	// �e���\���ʒu
	constexpr int kShotNumDisPosX = Game::kScreenWidth - kFrameSize + 10;	// ��
	constexpr int kShotNumDisPosY = 300;									// �c
	// �e���\���Ԋu
	constexpr int kShotNumIntervalX = 25;	// ��
	constexpr int kShotNumIntervalY = 100;	// �c
	// �e���\���T�C�Y
	constexpr int kShotDisWidth = 18;	// ��
	constexpr int kShotDisHeight = 20;	// �c
}

SceneMain::SceneMain():
	m_drawValue(0),
	m_isGetFullHpRecovery(false),
	m_enemyTotalNum(kEnemyMax),
	m_isExistLineMove(false),
	m_isSceneGameOver(false),
	m_isSceneClear(false),
	m_isSceneEnd(false),
	m_fadeAlpha(255),
	m_startDisplayX(0.0f)
{
	// �v���C���[�̃������m��
	m_pPlayer = new Player{ this };

	// �w�i�̃������m��
	m_pBg = new Bg;
	m_pBg->SetPlayer(m_pPlayer);
	m_pPlayer->SetBg(m_pBg);

	// �t�H���g
	m_pFont = new FontManager;

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

	// ���ǂݍ���
	m_bgm = LoadSoundMem("data/sound/BGM/stage1.mp3");
	m_enemyDeadSE = LoadSoundMem("data/sound/SE/enemyDamage.mp3");

	// ��������̉摜
	m_exHandle = LoadGraph("data/image/UI/ex.png");
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

	DeleteSoundMem(m_bgm);
	DeleteSoundMem(m_enemyDeadSE);
	DeleteGraph(m_exHandle);
}

void SceneMain::Init()
{
	// ��ʑJ�ڂ̏�����
	m_isSceneGameOver = false;
	m_isSceneClear = false;
	m_isSceneTitle = false;
	m_isSceneEnd = false;
	m_isExistLineMove = false;

	m_enemyTotalNum = kEnemyMax;

	// TODO:�X�^�[�g���̉��o
	StartStaging();

	// �|�[�Y��ʂ̏�����
	m_pPause->Init();

	// �v���C���[�̏�����
	assert(m_pPlayer);	// m_pPlayer == nullptr�̏ꍇ�~�܂�
	m_pPlayer->Init();

	// �w�i�̏�����
	m_pBg->Init();

	// �G�̏�����
	CreateEnemy();

	// �񕜃A�C�e���̏�����
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (m_pRecovery[i])
		{
			m_pRecovery[i]->Init(m_pBg);
		}
	}
	m_isGetFullHpRecovery = false;

	// BGM��炷
	// TODO: BGM�ύX�\��
	//PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	// �v���C���[�̎c�@��0�����̏ꍇ
	if (m_pPlayer->GetLife() < 0)
	{
		// 1�b�ԑҋ@
		WaitTimer(1000);

		m_isSceneGameOver = true; // �Q�[���I�[�o�[��ʂɑJ��
		StopSoundMem(m_bgm);
	}

	// �G�����ׂē|������N���A��ʂɑJ��
	if (m_enemyTotalNum <= 0)
	{
		m_isSceneClear = true;
		StopSoundMem(m_bgm);

		// 1�b��ɑJ��
		WaitTimer(1000);
	}

	// �p�b�h�̓��͏�Ԃ��擾
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �|�[�Y��ʂ̍X�V
	m_pPause->Update();

	// ����؂�ւ���ʂ��\������Ă���ꍇ��ʂ��~�߂�
	if (m_pPause->IsSelectShotExist())
	{
		return;
	}

	// �|�[�Y��ʂ��\������Ă���ꍇ��ʂ��~�߂�
	if (m_pPause->IsPause())
	{
		// ���g���C���I�����ꂽ�珉��������
		if (m_pPause->IsSelectRetry())
		{
			m_isSceneEnd = true;
		}
		// �^�C�g���ɖ߂��I��
		else if (m_pPause->IsSelectTitle())
		{
			// �^�C�g����ʂɑJ��
			m_isSceneTitle = true;
			StopSoundMem(m_bgm);

			// 1�b��ɑJ��
			WaitTimer(1000);
		}
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

	// E�ʂ�\��
	if (!m_isGetFullHpRecovery)
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
		m_pEnemy[i]->Update();

		// �g�p�ς݂̓G�L�����N�^�[���폜
		if (!m_pEnemy[i]->IsExist())
		{
			// ���Ŏ�SE��炷
			PlaySoundMem(m_enemyDeadSE, DX_PLAYTYPE_BACK, true);

			// �G�̍��v�������炷
			m_enemyTotalNum--;

			// �m���ŃA�C�e�����h���b�v
			CreateItem(i);
			
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

		//m_pRecovery[i]->SetBg(m_pBg);
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
		StopSoundMem(m_bgm);
	}
#endif

}

void SceneMain::Draw()
{
	// �`���X�N���[�����N���A����
	ClearDrawScreen();

	// TODO:�X�^�[�g���̕`��
	//// �l�p��`��
	//DrawBox(m_startDisplayX, Game::kScreenHeight * 0.5 - 10, 
	//	m_startDisplayX + 400, Game::kScreenHeight * 0.5 + 10,
	//	0xffffff, true);

	//// �����`��
	//DrawFormatString(
	//	m_startDisplayX, Game::kScreenHeight * 0.5 - 10,
	//	0x000000, "�G��%d�̓|���I", m_enemyTotalNum);

	// �w�i�̕`��
	m_pBg->Draw();

	// TODO:��������̕\��
	DrawEx();

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

	// �|�[�Y��ʁA����؂�ւ���ʂ̕\��
	m_pPause->Draw();

	/*����؂�ւ���ʕ\����*/
	if (m_pPause->IsSelectShotExist())
	{
		DrawShotChange();
	}
	/*�|�[�Y��ʕ\����*/
	if (m_pPause->IsPause())
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
			m_pRecovery[i]->Init(m_pBg);
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
			m_pRecovery[i]->Init(m_pBg);
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
			m_pRecovery[i]->Init(m_pBg);
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
			m_pRecovery[i]->Init(m_pBg);
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
			m_pRecovery[i]->Init(m_pBg);
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
			m_pRecovery[i]->Start({ 900, 500 }); // �A�C�e���̈ʒu��ݒ�
			m_pRecovery[i]->Init(m_pBg);
			return;
		}
	}
}

/*�X�^�[�g���o*/
void SceneMain::StartStaging()
{
	// TODO:�X�^�[�g�ƃN���A�����̕\��
	//m_startDisplayX = Game::kScreenWidth;
	//m_startDisplayX -= 10.0f;

	WaitTimer(1000); // 1�b�ԑҋ@
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
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 1:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(500.0f, 650.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 2:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(1000.0f, 700.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 3:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(400.0f, 600.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 4:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(2000.0f, 600.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 5:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(800.0f, 200.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 6:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(1500.0f, 400.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 7:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(2400.0f, 100.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 8:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(2000.0f, 50.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 9:
			m_pEnemy[i] = new EnemyBear;
			m_pEnemy[i]->Start(2600.0f, 650.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		default:
			break;
		}
	}
}

/*�񕜃A�C�e���̐���*/
void SceneMain::CreateItem(int enemyIndex)
{
	int getRandDrop = GetRand(100);
	if (getRandDrop <= 5)
	{
		DropHpSmallRecovery(enemyIndex); // HP��(��)
	}
	else if (getRandDrop <= 8)
	{
		DropHpGreatRecovery(enemyIndex);	// HP��(��)
	}
	else if (getRandDrop <= 13)
	{
		DropShotSmallRecovery(enemyIndex); // �e�G�l���M�[(��)
	}
	else if (getRandDrop <= 16)
	{
		DropShotGreatRecovery(enemyIndex); // �e�G�l���M�[(��)
	}
	else if (getRandDrop <= 19)
	{
		DropLifeRecovery(enemyIndex);	// �c�@
	}
}

/*��������̕\��*/
void SceneMain::DrawEx()
{
	// �\���ʒu
	int x = 400;
	int y = 500;

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	DrawGraph(x, y, m_exHandle, true);
}

/*�e���A�G���\��*/
void SceneMain::DrawInfo()
{
	// ��ʉ��Ɏl�p��\��
	DrawBox(0, 0, kFrameSize, Game::kScreenHeight, 0x483d8b, true); // ����
	DrawBox(Game::kScreenWidth - kFrameSize, 0, Game::kScreenWidth, Game::kScreenHeight, 0x483d8b, true); // �E��
	
	/*�c�@�AE�ʐ��A�c��G���������ɕ\��*/
	// E�ʐ��\��
	DrawFormatStringToHandle(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY, 0xffffff, m_pFont->GetFont(), "E : %d", m_pPlayer->GetFullHpRecovery());
	// �c�@���\��
	DrawFormatStringToHandle(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY * 2, 0xffffff, m_pFont->GetFont(), "�c�@��:%d", m_pPlayer->GetLife());
	// �G���\��
	DrawFormatStringToHandle(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY * 3, 0xffffff, m_pFont->GetFont(), "�c�G��:%d / %d", m_enemyTotalNum, kEnemyMax);

	/*HP�A����̒e�����E���ɕ\��*/
	// TODO:�I�𒆂̕��킪������悤�ɂ���
	// HP
	if (m_pPlayer->IsBuster())
	{
		// ����I�𒆂̕\��
		DrawBox(Game::kScreenWidth - kFrameSize,
			kShotNumDisPosY - 10,
			Game::kScreenWidth,
			kShotNumDisPosY + 30,
			0xffd700, false);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY - 40, "HP :" ,0xffffff, m_pFont->GetFont());
	// ���݂�HP�������l�p��`�悷��
	for (int i = 0; i < m_pPlayer->GetHp(); i++)
	{
		DrawBox(kShotNumDisPosX + kShotNumIntervalX * i,
			kShotNumDisPosY,
			(kShotNumDisPosX + kShotNumIntervalX * i) + kShotDisWidth,
			kShotNumDisPosY + kPauseShotNumHeight,
			0xeee8aa, true);
	}

	// ���^��
	if (m_pPlayer->IsMetal())
	{
		// ����I�𒆂̕\��
		DrawBox(Game::kScreenWidth - kFrameSize,
			kShotNumDisPosY - 10 + kShotNumIntervalY,
			Game::kScreenWidth,
			kShotNumDisPosY + 30 + kShotNumIntervalY,
			0xffd700, false);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY - 40, "M :", 0xffffff, m_pFont->GetFont());
	for (int i = 0; i < m_pPlayer->GetMetalEnergy(); i++)
	{
		DrawBox(kShotNumDisPosX + kShotNumIntervalX * i,
			kShotNumDisPosY + kShotNumIntervalY,
			(kShotNumDisPosX + kShotNumIntervalX * i) + kShotDisWidth,
			kShotNumDisPosY + kShotNumIntervalY + kPauseShotNumHeight,
			0xc0c0c0, true);
	}

	// �t�@�C�A
	if (m_pPlayer->IsFire())
	{
		// ����I�𒆂̕\��
		DrawBox(Game::kScreenWidth - kFrameSize,
			kShotNumDisPosY - 10 + kShotNumIntervalY * 2,
			Game::kScreenWidth,
			kShotNumDisPosY + 30 + kShotNumIntervalY * 2,
			0xffd700, false);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY * 2 - 40,  "F :", 0xffffff, m_pFont->GetFont());
	for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++)
	{
		DrawBox(kShotNumDisPosX + kShotNumIntervalX * i,
			kShotNumDisPosY + kShotNumIntervalY * 2,
			(kShotNumDisPosX + kShotNumIntervalX * i) + kShotDisWidth,
			kShotNumDisPosY + kShotNumIntervalY * 2 + kPauseShotNumHeight,
			0xff4500, true);
	}

	// 2��
	if (m_pPlayer->IsLineMove())
	{
		// ����I�𒆂̕\��
		DrawBox(Game::kScreenWidth - kFrameSize,
			kShotNumDisPosY - 10 + kShotNumIntervalY * 3,
			Game::kScreenWidth,
			kShotNumDisPosY + 30 +  kShotNumIntervalY * 3,
			0xffd700, false);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY * 3 - 40, "L :", 0xffffff, m_pFont->GetFont());
	for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++)
	{
		DrawBox(kShotNumDisPosX + kShotNumIntervalX * i,
			kShotNumDisPosY + kShotNumIntervalY * 3,
			(kShotNumDisPosX + kShotNumIntervalX * i) + kShotDisWidth,
			kShotNumDisPosY + kShotNumIntervalY * 3 + kPauseShotNumHeight,
			0xb22222, true);
	}
}

/*����؂�ւ���ʕ\��*/
void SceneMain::DrawShotChange()
{
	// ���݂�HP��\��
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffffff, m_pFont->GetFont(), "P :");
	for (int i = 0; i < m_pPlayer->GetHp(); i++) // ���݂�HP�������l�p��`�悷��
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kPauseShotNumHeight,
			0xeee8aa, true);
	}

	// ���݂̒e�G�l���M�[����\��
	// ���^��
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY, 0xffffff, m_pFont->GetFont(), "M :");
	for (int i = 0; i < m_pPlayer->GetMetalEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY + kPauseShotNumHeight,
			0xc0c0c0, true);
	}

	// �t�@�C�A�[
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 2, 0xffffff, m_pFont->GetFont(), "F :");
	for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY * 2,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY * 2 + kPauseShotNumHeight,
			0xff4500, true);
	}

	// �A�C�e��2��
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 3, 0xffffff, m_pFont->GetFont(), "L :");
	for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY * 3,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY * 3 + kPauseShotNumHeight,
			0xb22222, true);
	}

	// ���݂�E�ʐ���\��
	DrawStringToHandle(kTextPosX, kTextPosY + kIntervalY * 4, "E : ", 0xffffff, m_pFont->GetFont());
	DrawFormatStringToHandle(kTextPosX, kBarPosY + kIntervalY * 4, 0xffffff, m_pFont->GetFont(), "%d", m_pPlayer->GetFullHpRecovery());
}

/*�|�[�Y��ʕ\��*/
void SceneMain::DrawPause()
{
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY, 0xffffff, m_pFont->GetFont(), "�Q�[���ɖ߂�");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 2, 0xffffff, m_pFont->GetFont(), "���g���C");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 3, 0xffffff, m_pFont->GetFont(), "�^�C�g���ɖ߂�");
}
