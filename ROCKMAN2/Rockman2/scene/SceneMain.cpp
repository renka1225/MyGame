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

	/*���o*/
	// �X�^�[�g���o����
	constexpr float kStartTime = 120.0f;
	constexpr float kClearTime = 60.0f;
	constexpr float kGameoverTime = 300.0f;

	/*�|�[�Y���*/
	// �|�[�Y��ʂ̕����\���ʒu
	constexpr int kTextPosX = 850;
	constexpr int kTextPosY = 420;
	// �e���\���ʒu
	constexpr int kBarPosX = 850;
	constexpr int kBarPosY = 455;
	// �e���\���Ԋu
	constexpr int kBarInterval = 23;
	// �e���\���T�C�Y
	constexpr int kPauseShotNumWidth = 18;
	constexpr int kPauseShotNumHeight = 20;
	// �e��Y���W�\���Ԋu
	constexpr int kIntervalY = 70;

	/*�Q�[����*/
	// ���g�̃T�C�Y
	constexpr int kFrameSize = 270;
	// �c�@�A�G���A�^�C���\���ʒu
	constexpr int kInfoTextPosX = 30;	// ��
	constexpr int kInfoTextPosY = 290;	// �c
	// �e���\���ʒu
	constexpr int kShotNumDisPosX = Game::kScreenWidth - kFrameSize + 10;	// ��
	constexpr int kShotNumDisPosY = Game::kScreenHeight * 0.5 - 140;		// �c
	// �e���\���Ԋu
	constexpr int kShotNumIntervalX = 25;	// ��
	constexpr int kShotNumIntervalY = 100;	// �c
	// �e���\���T�C�Y
	constexpr int kShotDisWidth = 18;	// ��
	constexpr int kShotDisHeight = 20;	// �c
	// �t���[���̕\���ʒu
	constexpr int kFramePosY = Game::kScreenHeight * 0.5 - 199;
}

SceneMain::SceneMain() :
	m_drawValue(0),
	m_isGetFullHpRecovery(false),
	m_enemyTotalNum(kEnemyMax),
	m_time(0.0f),
	m_isExistLineMove(false),
	m_isSceneGameOver(false),
	m_isSceneClear(false),
	m_isSceneEnd(false),
	m_fadeAlpha(240),
	m_stagingFade(0)
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
	m_recoverySE = LoadSoundMem("data/sound/SE/recovery.mp3");
	m_lineMoveSE = LoadSoundMem("data/sound/SE/shotLine.mp3");
	m_startSE = LoadSoundMem("data/sound/BGM/start.wav");
	m_clearSE = LoadSoundMem("data/sound/SE/clear.wav");

	// �摜
	m_frameHandle = LoadGraph("data/image/UI/frame.png");
	m_shotSelectHandle = LoadGraph("data/image/UI/shotSelect.png");
	m_startHandle = LoadGraph("data/image/UI/start.png");
}

SceneMain::~SceneMain()
{
	// �w�i�̃��������
	delete m_pBg;
	m_pBg = nullptr;

	// �t�H���g
	delete m_pFont;
	m_pFont = nullptr;

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
	DeleteSoundMem(m_recoverySE);
	DeleteSoundMem(m_lineMoveSE);
	DeleteSoundMem(m_startSE);
	DeleteSoundMem(m_clearSE);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_shotSelectHandle);
	DeleteGraph(m_startHandle);
}

void SceneMain::Init()
{
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
}

void SceneMain::Draw()
{
#ifdef _DEBUG
	printfDx("�X�e�[�W�x�[�X");
#endif // _DEBUG
}

/// <summary>
/// �e�̐���
/// </summary>
/// <param name="pShot">�e�̎��</param>
/// <returns></returns>
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

/// <summary>
/// �A�C�e������
/// </summary>
/// <param name="enemyIndex">�G</param>
// HP����
void SceneMain::DropHpSmallRecovery(int enemyIndex)
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoverySmallHp;
			m_pRecovery[i]->Init(m_pBg);
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			return;
		}
	}
}
// HP���
void SceneMain::DropHpGreatRecovery(int enemyIndex)
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryGreatHp;
			m_pRecovery[i]->Init(m_pBg);
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			return;
		}
	}
}
// �e����
void SceneMain::DropShotSmallRecovery(int enemyIndex)
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoverySmallShot;
			m_pRecovery[i]->Init(m_pBg);
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			return;
		}
	}
}
// �e���
void SceneMain::DropShotGreatRecovery(int enemyIndex)
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryLife;
			m_pRecovery[i]->Init(m_pBg);
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			return;
		}
	}
}
// �c�@��
void SceneMain::DropLifeRecovery(int enemyIndex)
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryGreatShot;
			m_pRecovery[i]->Init(m_pBg);
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			return;
		}
	}
}
// HP�S��
void SceneMain::DropFullHpRecovery()
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryFullHp;
			m_pRecovery[i]->Init(m_pBg);
			m_pRecovery[i]->Start({ 1680, 700 }); // �A�C�e���̈ʒu��ݒ�
			return;
		}
	}
}

/// <summary>
/// �G�̐���
/// </summary>
void SceneMain::CreateEnemy()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		switch (i)
		{
		case 0:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(600.0f, 400.0f, 200.0f);
			m_pEnemy[i]->Init(m_pBg, m_pPlayer);
			break;
		case 1:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(1080.0f, 240.0f, 30.0f);
			m_pEnemy[i]->Init(m_pBg, m_pPlayer);
			break;
		case 2:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(1600.0f, 600.0f, 400.0f);
			m_pEnemy[i]->Init(m_pBg, m_pPlayer);
			break;
		case 3:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(2052.0f, 450.0f, 40.0f);
			m_pEnemy[i]->Init(m_pBg, m_pPlayer);
			break;
		case 4:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(2850.0f, 320.0f, 40.0f);
			m_pEnemy[i]->Init(m_pBg, m_pPlayer);
			break;
		case 5:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(3240.0f, 250.0f, 200.0f);
			m_pEnemy[i]->Init(m_pBg, m_pPlayer);
			break;
		case 6:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(4000.0f, 600.0f, 270.0f);
			m_pEnemy[i]->Init(m_pBg, m_pPlayer);
			break;
		case 7:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(4050.0f, 250.0f, 200.0f);
			m_pEnemy[i]->Init(m_pBg, m_pPlayer);
			break;
		case 8:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(4800.0f, 100.0f, 100.0f);
			m_pEnemy[i]->Init(m_pBg, m_pPlayer);
			break;
		case 9:
			m_pEnemy[i] = new EnemyBear;
			m_pEnemy[i]->Start(6000.0f, 900.0f, 200.0f);
			m_pEnemy[i]->Init(m_pBg, m_pPlayer);
			break;
		default:
			break;
		}
	}
}

/// <summary>
/// �񕜃A�C�e���h���b�v
/// </summary>
/// <param name="enemyIndex">�G</param>
void SceneMain::CreateItem(int enemyIndex)
{
	int getRandDrop = GetRand(100);
	if (getRandDrop <= 20)
	{
		DropHpSmallRecovery(enemyIndex); // HP��(��)
	}
	else if (getRandDrop <= 35)
	{
		DropHpGreatRecovery(enemyIndex);	// HP��(��)
	}
	else if (getRandDrop <= 60)
	{
		DropShotSmallRecovery(enemyIndex); // �e�G�l���M�[(��)
	}
	else if (getRandDrop <= 80)
	{
		DropShotGreatRecovery(enemyIndex); // �e�G�l���M�[(��)
	}
	else if (getRandDrop <= 90)
	{
		DropLifeRecovery(enemyIndex);	// �c�@
	}
}

/// <summary>
/// �e���A�G���\��
/// </summary>
void SceneMain::DrawInfo()
{
	// ��ʉ��Ɏl�p��\��
	DrawBox(0, 0, kFrameSize, Game::kScreenHeight, 0x483d8b, true); // ����
	DrawBox(Game::kScreenWidth - kFrameSize, 0, Game::kScreenWidth, Game::kScreenHeight, 0x483d8b, true); // �E��

	// �g�\��
	DrawGraph(0, kFramePosY, m_frameHandle, true); // ����
	DrawGraph(Game::kScreenWidth - kFrameSize, kFramePosY, m_frameHandle, true); // �E��
	
	/*�c�@�A�c��G���A�^�C���������ɕ\��*/

	// �c�@���\��
	DrawStringToHandle(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY, "�c�@", 0xffffff, m_pFont->GetFont2());
	DrawFormatStringToHandle(kInfoTextPosX + 80, kInfoTextPosY + kShotNumIntervalY + 40, 0xffaa00, m_pFont->GetFont3(), " %d", m_pPlayer->GetLife());

	// �G���\��
	DrawStringToHandle(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY * 2 + 10, "�G��", 0xffffff, m_pFont->GetFont2());
	DrawFormatStringToHandle(kInfoTextPosX + 50, kInfoTextPosY + kShotNumIntervalY * 2 + 50, 0xffaa00, m_pFont->GetFont3(), " %d / %d", m_enemyTotalNum, kEnemyMax);

	// �^�C��
	int milliSec = static_cast<int>(m_time) * 1000 / 60;
	int sec = (milliSec / 1000) % 60;
	int min = (milliSec / 1000) / 60;
	milliSec %= 1000;

	DrawStringToHandle(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY * 3 + 30, "�^�C��", 0xffffff, m_pFont->GetFont2());
	DrawFormatStringToHandle(kInfoTextPosX + 20, kInfoTextPosY + kShotNumIntervalY * 3 + 70, 0xffaa00, m_pFont->GetFont3(), " %3d:%02d.%03d", min, sec, milliSec);

	
/// <summary>
/// HP�A����̒e�����E���ɕ\��
/// </summary>
	// HP
	if (m_pPlayer->IsBuster())
	{
		// ����I�𒆂̕\��
		DrawGraph(Game::kScreenWidth - kFrameSize + 3, kShotNumDisPosY - 10, m_shotSelectHandle, true);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY - 40, "HP :" ,0xffffff, m_pFont->GetFont2());
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
		DrawGraph(Game::kScreenWidth - kFrameSize + 3, kShotNumDisPosY - 10 + kShotNumIntervalY, m_shotSelectHandle, true);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY - 40, "M :", 0xffffff, m_pFont->GetFont2());
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
		DrawGraph(Game::kScreenWidth - kFrameSize + 3, kShotNumDisPosY - 10 + kShotNumIntervalY * 2, m_shotSelectHandle, true);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY * 2 - 40,  "F :", 0xffffff, m_pFont->GetFont2());
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
		DrawGraph(Game::kScreenWidth - kFrameSize + 3, kShotNumDisPosY - 10 + kShotNumIntervalY * 3, m_shotSelectHandle, true);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY * 3 - 40, "L :", 0xffffff, m_pFont->GetFont2());
	for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++)
	{
		DrawBox(kShotNumDisPosX + kShotNumIntervalX * i,
			kShotNumDisPosY + kShotNumIntervalY * 3,
			(kShotNumDisPosX + kShotNumIntervalX * i) + kShotDisWidth,
			kShotNumDisPosY + kShotNumIntervalY * 3 + kPauseShotNumHeight,
			0xb22222, true);
	}
}

/// <summary>
/// ����؂�ւ���ʕ\��
/// </summary>
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

/// <summary>
/// �|�[�Y��ʕ\��
/// </summary>
void SceneMain::DrawPause()
{
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY, 0xffffff, m_pFont->GetFont(), "�Q�[���ɖ߂�");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 2, 0xffffff, m_pFont->GetFont(), "���g���C");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 3, 0xffffff, m_pFont->GetFont(), "�^�C�g���ɖ߂�");
}

/// <summary>
/// �X�^�[�g���o�̕`��
/// </summary>
void SceneMain::DrawStartStaging()
{
	// �t�F�[�h�C�����A�E�g
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_stagingFade);
	DrawGraph(m_startDis.x, Game::kScreenHeight * 0.5f - 220, m_startHandle, true);

	DrawStringToHandle(static_cast<int>(m_startDis.x + Game::kScreenWidth * 0.5 - 170), Game::kScreenHeight * 0.5 - 100,
		"�G�����ׂĂ������I\n", 0xffffff, m_pFont->GetFontStaging());

	DrawFormatStringToHandle(static_cast<int>(m_startDis.x + Game::kScreenWidth * 0.5 - 60), Game::kScreenHeight * 0.5 + 30,
		0xffffff, m_pFont->GetFontStaging(), "%d / %d\n", m_enemyTotalNum, m_enemyTotalNum);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/// <summary>
/// �N���A���o�̕`��
/// </summary>
void SceneMain::DrawClearStaging()
{
	// �^�C��
	int milliSec = m_time * 1000 / 60;
	int sec = (milliSec / 1000) % 60;
	int min = (milliSec / 1000) / 60;
	milliSec %= 1000;

	// �N���A�̕�����\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_stagingFade);
	DrawGraph(0, Game::kScreenHeight * 0.5f - 200, m_startHandle, true);

	DrawStringToHandle(Game::kScreenWidth * 0.5 - 70, Game::kScreenHeight * 0.5 - 100,
		"CLEAR!\n", 0xffe44d, m_pFont->GetFontStaging());

	DrawFormatStringToHandle(Game::kScreenWidth * 0.5 - 260, Game::kScreenHeight * 0.5 + 30,
		0xffffff, m_pFont->GetFontStaging(), "�N���A�^�C�� : % 3d:%02d.%03d", min, sec, milliSec);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
