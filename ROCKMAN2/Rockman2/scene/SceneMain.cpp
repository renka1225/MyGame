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


/// <summary>
/// �萔
/// </summary>
namespace
{
	/*���o*/
// �X�^�[�g���o����
	constexpr float kStartTime = 120.0f;
	constexpr float kClearTime = 240.0f;
	constexpr float kGameoverTime = 300.0f;
	// ready�J�E���g���o
	constexpr int kReadyCount = 60;
	// �ԉ΂̑ł��グ���x
	constexpr float kFireworksSpeed = 20.0f;
	// �ԉ΂̉摜�؂�o���T�C�Y
	constexpr int kFireworksWidth = 92;
	constexpr int kFireworksHeight = 94;
	// �ԉ΂̕\���t���[��
	constexpr int kFireworksFrame = 10;

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
	constexpr int kShotNumDisPosX = static_cast<int>(Game::kScreenWidth - kFrameSize + 10);	// ��
	constexpr int kShotNumDisPosY = static_cast<int>(Game::kScreenHeight * 0.5 - 140);		// �c
	// �e���\���Ԋu
	constexpr int kShotNumIntervalX = 25;	// ��
	constexpr int kShotNumIntervalY = 100;	// �c
	// �e���\���T�C�Y
	constexpr int kShotDisWidth = 18;	// ��
	constexpr int kShotDisHeight = 20;	// �c
	// �t���[���̕\���ʒu
	constexpr int kFramePosY = static_cast<int>(Game::kScreenHeight * 0.5 - 199);

	/*�A�C�e���h���b�v�̊m��*/
	constexpr int kItemDropMax = 100;		// �ő�m��
	constexpr int kHpSmallRec = 20;			// HP��(��)
	constexpr int kHpGreatRec = 35;			// HP��(��)
	constexpr int kShotSmallRec = 60;		// �e��(��)
	constexpr int kShotGreatRec = 80;			// �e��(��)
	constexpr int kLifeRec = 85;			// �c�@��
}


SceneMain::SceneMain() :
	m_pFont(nullptr),
	m_pPause(nullptr),
	m_pPlayer(nullptr),
	m_drawValue(0),
	m_isGetFullHpRecovery(false),
	m_enemyTotalNum(0),
	m_time(0.0f),
	m_isExistLineMove(false),
	m_isExistMenu(false),
	m_isSceneGameOver(false),
	m_isSceneClear(false),
	m_isSceneTitle(false),
	m_isSceneEnd(false),
	m_isRetry(false),
	m_fadeAlpha(255),
	m_stagingFade(0),
	m_startStagingTime(0.0f),
	m_clearStagingTime(0.0f),
	m_gameoverStagingTime(0.0f),
	m_fireworks1Frame(0),
	m_fireworks2Frame(0),
	m_fireworks3Frame(0),
	m_fireworks4Frame(0),
	m_fireworks5Frame(0),
	m_fireworks6Frame(0),
	m_readyCount(0),
	m_shakeFrame(0),
	m_ampFrame(0),
	m_gameScreenHandle(-1)
{
	m_bgm = LoadSoundMem("data/sound/BGM/stage2.wav");
	m_enemyDeadSE = LoadSoundMem("data/sound/SE/enemyDamage.mp3");
	m_recoverySE = LoadSoundMem("data/sound/SE/recovery.mp3");
	m_lineMoveSE = LoadSoundMem("data/sound/SE/shotLine.mp3");
	m_startSE = LoadSoundMem("data/sound/BGM/start.wav");
	m_clearSE = LoadSoundMem("data/sound/SE/clear.wav");
	m_fireworksSE = LoadSoundMem("data/sound/SE/fireworks.wav");

	// �摜�ǂݍ���
	m_frameHandle = LoadGraph("data/image/UI/frame.png");
	m_metalHandle = LoadGraph("data/image/Shot/shotMetal.png");
	m_fireHandle = LoadGraph("data/image/Shot/shotFire3.png");
	m_lineMoveHandle = LoadGraph("data/image/shot/shotLineMove.png");
	m_fullHpRecHandle = LoadGraph("data/image/Recovery/fullHp.png");
	m_shotSelectHandle = LoadGraph("data/image/UI/shotSelect.png");
	m_startHandle = LoadGraph("data/image/UI/start.png");
	m_fireworks1 = LoadGraph("data/image/Effect/clear/1.png");
	m_fireworks2 = LoadGraph("data/image/Effect/clear/2.png");
	m_fireworks3 = LoadGraph("data/image/Effect/clear/3.png");
}


SceneMain::~SceneMain()
{
}


/// <summary>
/// �A�C�e���h���b�v
/// </summary>
/// <param name="enemyIndex">�A�C�e���h���b�v����G</param>
void SceneMain::CreateItem(int enemyIndex)
{
	int getRandDrop = GetRand(kItemDropMax);
	if (getRandDrop <= kHpSmallRec)
	{
		DropHpSmallRecovery(enemyIndex); // HP��(��)
	}
	else if (getRandDrop <= kHpGreatRec)
	{
		DropHpGreatRecovery(enemyIndex);	// HP��(��)
	}
	else if (getRandDrop <= kShotSmallRec)
	{
		DropShotSmallRecovery(enemyIndex); // �e�G�l���M�[(��)
	}
	else if (getRandDrop <= kShotGreatRec)
	{
		DropShotGreatRecovery(enemyIndex); // �e�G�l���M�[(��)
	}
	else if (getRandDrop <= kLifeRec)
	{
		DropLifeRecovery(enemyIndex);	// �c�@
	}
	else
	{
		// �����h���b�v���Ȃ�
	}
}


/// <summary>
/// ����؂�ւ���ʕ\��
/// </summary>
void SceneMain::DrawShotChange()
{
	// ���݂�HP��\��
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffffff, m_pFont->GetFont(), "P :"); // ����
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
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY, 0xffffff, m_pFont->GetFont(), "M :"); // ����
	DrawExtendGraph(kTextPosX + 50, kTextPosY + kIntervalY, kTextPosX + 75, kTextPosY + kIntervalY + 25, m_metalHandle, true); // ���^���̉摜
	for (int i = 0; i < m_pPlayer->GetMetalEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY + kPauseShotNumHeight,
			0xc0c0c0, true);
	}

	// �t�@�C�A�[
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * kShotFire, 0xffffff, m_pFont->GetFont(), "F :"); // ����
	DrawExtendGraph(kTextPosX + 50, kTextPosY + kIntervalY * 2, kTextPosX + 75, kTextPosY + kIntervalY * kShotFire + 25, m_fireHandle, true); // �t�@�C�A�̉摜
	for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY * 2,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY * 2 + kPauseShotNumHeight,
			0xff4500, true);
	}

	// �A�C�e��2��
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * kShotLineMove, 0xffffff, m_pFont->GetFont(), "L :"); // ����
	DrawGraph(kTextPosX + 45, kTextPosY + kIntervalY * kShotLineMove + 3, m_lineMoveHandle, true); // 2���̉摜
	for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY * 3,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY * 3 + kPauseShotNumHeight,
			0xb22222, true);
	}

	// ���݂�E�ʐ���\��
	DrawStringToHandle(kTextPosX, kTextPosY + kIntervalY * kRecovery, "E : ", 0xffffff, m_pFont->GetFont()); // ����
	if (m_pPlayer->GetFullHpRecovery() == 1)
	{
		DrawGraph(kTextPosX, kBarPosY + kIntervalY * kRecovery - 5, m_fullHpRecHandle, true);
	}
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
	DrawGraph(static_cast<int>(m_startDis.x), static_cast<int>(Game::kScreenHeight * 0.5 - 220), m_startHandle, true);

	DrawStringToHandle(static_cast<int>(m_startDis.x + Game::kScreenWidth * 0.5 - 170), static_cast<int>(Game::kScreenHeight * 0.5 - 100),
		"�G�����ׂĂ������I\n", 0xffffff, m_pFont->GetFontStaging());

	DrawFormatStringToHandle(static_cast<int>(m_startDis.x + Game::kScreenWidth * 0.5 - 60), static_cast<int>(Game::kScreenHeight * 0.5 + 30),
		0xffffff, m_pFont->GetFontStaging(), "%d / %d\n", m_enemyTotalNum, m_enemyTotalNum);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


/// <summary>
/// �N���A���o�̕`��
/// </summary>
void SceneMain::DrawClearStaging()
{
	// �^�C��
	int milliSec = static_cast<int>(m_time * 1000 / 60);
	int sec = (milliSec / 1000) % 60;
	int min = (milliSec / 1000) / 60;
	milliSec %= 1000;

	// �N���A�̕�����\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_stagingFade);
	DrawGraph(0, static_cast<int>(Game::kScreenHeight * 0.5 - 200), m_startHandle, true);

	DrawStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5 - 70), static_cast<int>(Game::kScreenHeight * 0.5 - 100),
		"CLEAR!\n", 0xffe44d, m_pFont->GetFontStaging());

	DrawFormatStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5 - 260), static_cast<int>(Game::kScreenHeight * 0.5 + 30),
		0xffffff, m_pFont->GetFontStaging(), "�N���A�^�C�� : % 3d:%02d.%03d", min, sec, milliSec);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �����\����ԉ΂�������
	if (m_clearStagingTime <= 220.0f && m_clearStagingTime > 70.0f)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks1Pos.x), static_cast<int>(m_fireworks1Pos.y), 
			m_fireworks1Frame, 0,
			kFireworksWidth, kFireworksHeight, 
			6.0f, 0.0f,
			m_fireworks1, true);
	}
	if (m_clearStagingTime <= 190.0f && m_clearStagingTime > 50.0f)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks2Pos.x), static_cast<int>(m_fireworks2Pos.y),
			m_fireworks2Frame, 0, 
			kFireworksWidth, kFireworksHeight, 
			5.0f, 0.0f, 
			m_fireworks2, true);
	}
	if (m_clearStagingTime <= 160.0f && m_clearStagingTime > 30.0f)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks3Pos.x), static_cast<int>(m_fireworks3Pos.y),
			m_fireworks3Frame, 0,
			kFireworksWidth, kFireworksHeight, 
			5.0f, 0.0f, 
			m_fireworks3, true);
	}
	if (m_clearStagingTime <= 140.0f && m_clearStagingTime > 10.0f)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks4Pos.x), static_cast<int>(m_fireworks4Pos.y),
			m_fireworks4Frame, 0,
			kFireworksWidth, kFireworksHeight, 
			4.8f, 0.0f,
			m_fireworks2, true);
	}
	if (m_clearStagingTime <= 120.0f && m_clearStagingTime > 5.0f)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks5Pos.x), static_cast<int>(m_fireworks5Pos.y), 
			m_fireworks5Frame, 0,
			kFireworksWidth, kFireworksHeight,
			5.2f, 0.0f,
			m_fireworks3, true);
	}
	if (m_clearStagingTime <= 90.0f && m_clearStagingTime > 0.0f)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks6Pos.x), static_cast<int>(m_fireworks6Pos.y),
			m_fireworks6Frame, 0,
			kFireworksWidth, kFireworksHeight,
			6.0f, 0.0f, 
			m_fireworks1, true);
	}
}