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
	/*�X�^�[�g���o*/
	// �X�^�[�g���o����
	constexpr float kStartTime = 120.0f;
	// ready�J�E���g���o
	constexpr int kReadyCount = 60;
	// �l�p�\���ʒu
	constexpr int kStartBackPos = 320;
	// �N���A�����\���ʒu����
	constexpr int kStartDisPosX = 790;
	constexpr int kStartDisPosY = 440;
	// �G���\���ʒu
	constexpr int kEnemyNumDisPosX = 900;
	constexpr int kEnemyNumDisPosY = 570;

	/*�N���A���o*/
	// �N���A���o����
	constexpr float kClearTime = 240.0f;
	// �N���ASE�𗬂��n�߂鎞��
	constexpr float kClearSETime = 180.0f;
	// �N���A���̃t�F�[�h����
	constexpr int kClearFadeFrame = 150;
	// �l�p�\���ʒu
	constexpr int kClearBackPos = 340;
	// �N���A�̕����\���ʒu����
	constexpr int kClearDisPosX = 890;
	constexpr int kClearDisPosY = 440;
	// �N���A���ԕ\���ʒu
	constexpr int kClearTimePosX = 700;
	constexpr int kClearTimePosY = 570;

	/*�ԉ΂̉��o*/
	// �ԉ΂�ł��グ�n�߂鎞��
	constexpr float kFireworks1Time = 220.0f;
	constexpr float kFireworks2Time = 210.0f;
	constexpr float kFireworks3Time = 180.0f;
	constexpr float kFireworks4Time = 150.0f;
	constexpr float kFireworks5Time = 120.0f;
	constexpr float kFireworks6Time = 100.0f;
	constexpr float kFireworks7Time = 80.0f;
	// �`�掞�Ԓ���
	constexpr float kDrawFireworks = 10.0f;
	// �`��I������
	constexpr float kDrawEndFireworks1 = 70.0f;	// 1��
	constexpr float kDrawEndFireworks2 = 50.0f;	// 2��
	constexpr float kDrawEndFireworks3 = 30.0f;	// 3��
	constexpr float kDrawEndFireworks4 = 10.0f;	// 4��
	constexpr float kDrawEndFireworks5 = 5.0f;	// 5��
	constexpr float kDrawEndFireworks6 = 0.0f;	// 6��
	// �ԉ΂̕\���t���[��
	constexpr int kFireworksFrame = 10;
	// �ԉ΂̑ł��グ���x
	constexpr float kFireworksSpeed = 20.0f;
	// �ԉ΂̉摜�؂�o���T�C�Y
	constexpr int kFireworksWidth = 92;
	constexpr int kFireworksHeight = 94;
	// �ԉ΂̊g�嗦
	constexpr float kFireworksScale1 = 5.0f;
	constexpr float kFireworksScale2 = 6.0f;

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
	constexpr int kShotGreatRec = 80;		// �e��(��)
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
/// �N���A���o����
/// </summary>
void SceneMain::UpdateClearStaging()
{
	m_clearStagingTime--;
	m_stagingFade += kClearFadeFrame;

	// �N���ASE1�񂾂���炷
	StopSoundMem(m_bgm);
	if (CheckSoundMem(m_clearSE) == 0 && m_clearStagingTime >= kClearSETime)
	{
		m_stagingFade = 0;
		PlaySoundMem(m_clearSE, DX_PLAYTYPE_BACK, true);
		return;
	}
	// �ԉ΂̍X�V
	else if (m_clearStagingTime <= kFireworks1Time && m_clearStagingTime > 0.0f)
	{
		// �ԉ΂���ɂ�����
		if (m_clearStagingTime <= kFireworks1Time)
		{
			m_fireworks1Pos.y -= kFireworksSpeed;
		}
		if (m_clearStagingTime <= kFireworks2Time)
		{
			m_fireworks1Frame += kFireworksWidth;
			m_fireworks2Pos.y -= kFireworksSpeed;
		}
		if (m_clearStagingTime <= kFireworks3Time)
		{
			m_fireworks2Frame += kFireworksWidth;
			m_fireworks3Pos.y -= kFireworksSpeed;
		}
		if (m_clearStagingTime <= kFireworks4Time)
		{
			m_fireworks3Frame += kFireworksWidth;
			m_fireworks4Pos.y -= kFireworksSpeed;
		}
		if (m_clearStagingTime <= kFireworks5Time)
		{
			m_fireworks4Frame += kFireworksWidth;
			m_fireworks5Pos.y -= kFireworksSpeed;
		}
		if (m_clearStagingTime <= kFireworks6Time)
		{
			m_fireworks5Frame += kFireworksWidth;
			m_fireworks6Pos.y -= kFireworksSpeed;
		}
		if(m_clearStagingTime <= kFireworks7Time)
		{
			m_fireworks6Frame += kFireworksWidth;
		}
	
		// ���𗬂�
		if (CheckSoundMem(m_fireworksSE) == 0)
		{
			PlaySoundMem(m_fireworksSE, DX_PLAYTYPE_BACK, true);
			return;
		}
	}
}


/// <summary>
/// �񕜃A�C�e���̏���
/// </summary>
/// <param name="playerRect"></param>
void SceneMain::UpdateRecovery(Rect playerRect)
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pRecovery[i]) continue;

		m_pRecovery[i]->Update();

		Rect recoveryRect = m_pRecovery[i]->GetColRect();	// �񕜃A�C�e���̓����蔻��
		// �v���C���[�Ɖ񕜃A�C�e���̓����蔻��
		if (playerRect.IsCollision(recoveryRect))
		{
			// SE��炷
			PlaySoundMem(m_recoverySE, DX_PLAYTYPE_BACK, true);

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
		else if (!m_pRecovery[i]->IsExist())
		{
			// �A�C�e��������
			delete m_pRecovery[i];
			m_pRecovery[i] = nullptr;
		}
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
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * (kPauseRetry + 1), 0xffffff, m_pFont->GetFont(), "���g���C");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * (kPauseTitle + 1), 0xffffff, m_pFont->GetFont(), "�^�C�g���ɖ߂�");
}


/// <summary>
/// �X�^�[�g���o�̕`��
/// </summary>	
void SceneMain::DrawStartStaging()
{
	// �t�F�[�h�C�����A�E�g
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_stagingFade);
	DrawGraph(static_cast<int>(m_startDis.x), kStartBackPos, m_startHandle, true);

	DrawStringToHandle(static_cast<int>(m_startDis.x + kStartDisPosX), kStartDisPosY,
		"�G�����ׂĂ������I\n", 0xffffff, m_pFont->GetFontStaging());

	DrawFormatStringToHandle(static_cast<int>(m_startDis.x + kEnemyNumDisPosX), kEnemyNumDisPosY,
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
	DrawGraph(0, kClearBackPos, m_startHandle, true);

	DrawStringToHandle(kClearDisPosX, kClearDisPosY,
		"CLEAR!\n", 0xffe44d, m_pFont->GetFontStaging());

	DrawFormatStringToHandle(kClearTimePosX, kClearTimePosY,
		0xffffff, m_pFont->GetFontStaging(), "�N���A�^�C�� : % 3d:%02d.%03d", min, sec, milliSec);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �����\����ԉ΂�������
	if (m_clearStagingTime <= kFireworks1Time && m_clearStagingTime > kDrawEndFireworks1)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks1Pos.x), static_cast<int>(m_fireworks1Pos.y), 
			m_fireworks1Frame, 0,
			kFireworksWidth, kFireworksHeight, 
			kFireworksScale2, 0.0f,
			m_fireworks1, true);
	}
	if (m_clearStagingTime <= (kFireworks3Time + kDrawFireworks) && m_clearStagingTime > kDrawEndFireworks2)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks2Pos.x), static_cast<int>(m_fireworks2Pos.y),
			m_fireworks2Frame, 0, 
			kFireworksWidth, kFireworksHeight, 
			kFireworksScale1, 0.0f,
			m_fireworks2, true);
	}
	if (m_clearStagingTime <= (kFireworks4Time + kDrawFireworks) && m_clearStagingTime > kDrawEndFireworks3)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks3Pos.x), static_cast<int>(m_fireworks3Pos.y),
			m_fireworks3Frame, 0,
			kFireworksWidth, kFireworksHeight, 
			kFireworksScale1, 0.0f,
			m_fireworks3, true);
	}
	if (m_clearStagingTime <= (kFireworks4Time - kDrawFireworks) && m_clearStagingTime > kDrawEndFireworks4)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks4Pos.x), static_cast<int>(m_fireworks4Pos.y),
			m_fireworks4Frame, 0,
			kFireworksWidth, kFireworksHeight, 
			kFireworksScale1, 0.0f,
			m_fireworks2, true);
	}
	if (m_clearStagingTime <= kFireworks4Time && m_clearStagingTime > kDrawEndFireworks5)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks5Pos.x), static_cast<int>(m_fireworks5Pos.y), 
			m_fireworks5Frame, 0,
			kFireworksWidth, kFireworksHeight,
			kFireworksScale1, 0.0f,
			m_fireworks3, true);
	}
	if (m_clearStagingTime <= (kFireworks6Time - kDrawFireworks) && m_clearStagingTime > kDrawEndFireworks6)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks6Pos.x), static_cast<int>(m_fireworks6Pos.y),
			m_fireworks6Frame, 0,
			kFireworksWidth, kFireworksHeight,
			kFireworksScale2, 0.0f,
			m_fireworks1, true);
	}
}