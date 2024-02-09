#include "SceneTutorial.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "FontManager.h"
#include "BgTutorial.h"
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
	constexpr int kEnemyMax = 3;

	// �v���C���[�̉摜�T�C�Y
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 64;

	// �}�b�v�`�b�v�̃T�C�Y
	constexpr int kMapChipWidth = 32;
	constexpr int kMapChipHeight = 32;

	/*���o*/
	// �X�^�[�g���o����
	constexpr float kStartTime = 120.0f;
	constexpr float kClearTime = 240.0f;
	constexpr float kGameoverTime = 300.0f;
	// ready�J�E���g���o
	constexpr int kReadyCount = 60;

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

SceneTutorial::SceneTutorial() :
	m_drawValue(0),
	m_isGetFullHpRecovery(false),
	m_enemyTotalNum(kEnemyMax),
	m_time(0.0f),
	m_isExistLineMove(false),
	m_isSceneGameOver(false),
	m_isSceneClear(false),
	m_isSceneEnd(false),
	m_isRetry(false),
	m_fadeAlpha(240),
	m_stagingFade(0),
	m_startStagingTime(kStartTime),
	m_clearStagingTime(kClearTime),
	m_gameoverStagingTime(kGameoverTime),
	m_readyCount(kReadyCount),
	m_shakeFrame(0),
	m_ampFrame(0)
{
	// �Q�[����ʕ`���̐���
	m_gameScreenHandle = MakeScreen(Tutorial::kMapWidth, Tutorial::kMapHeight, true);

	// �v���C���[�̃������m��
	m_pPlayer = new Player{ this };

	// �w�i�̃������m��
	m_pBg = new BgTutorial;
	m_pBg->SetPlayer(m_pPlayer);

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
	m_fireworksSE = LoadSoundMem("data/sound/SE/fireworks.wav");

	// �摜
	m_frameHandle = LoadGraph("data/image/UI/frame.png");
	m_shotSelectHandle = LoadGraph("data/image/UI/shotSelect.png");
	m_startHandle = LoadGraph("data/image/UI/start.png");
	m_fireworks = LoadGraph("data/image/Effect/clear/1.png");
}

SceneTutorial::~SceneTutorial()
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
	DeleteGraph(m_fireworksSE);
}

void SceneTutorial::Init()
{
	// ���g���C���̓X�^�[�g���o���s��Ȃ�
	if (!(m_isSceneEnd || m_isRetry))
	{
		// ���o���Ԃ̏�����
		m_startStagingTime = kStartTime;
		m_startDis = { 30, 0 };
		m_fadeAlpha = 240;
		m_stagingFade = 0;
		// �X�^�[�gSE
		PlaySoundMem(m_startSE, DX_PLAYTYPE_BACK, true);
	}
	// HP��0�ȉ��ɂȂ����ꍇ�͍s��Ȃ�
	if (!m_isRetry)
	{
		// �G�̏�����
		CreateEnemy();
		m_enemyTotalNum = kEnemyMax;
		m_time = 0.0f;

		m_isGetFullHpRecovery = false;
	}
	// ���o���Ԃ̏�����
	m_clearStagingTime = kClearTime;
	m_gameoverStagingTime = kGameoverTime;
	m_shakeFrame = 0;
	m_readyCount = kReadyCount;
	m_ampFrame = 0;

	// �|�[�Y��ʂ̏�����
	m_pPause->Init();

	// �v���C���[�̏�����
	assert(m_pPlayer);
	m_pPlayer->Init(m_pBg);

	// �w�i�̏�����
	m_pBg->Init();

	// �񕜃A�C�e���̏�����
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (m_pRecovery[i])
		{
			m_pRecovery[i]->Init(m_pBg);
			delete m_pRecovery[i];
			m_pRecovery[i] = nullptr;
		}
	}
	m_isExistLineMove = false;

	// ��ʑJ�ڂ̏�����
	m_isSceneGameOver = false;
	m_isSceneClear = false;
	m_isSceneTitle = false;
	m_isSceneEnd = false;
	m_isRetry = false;
}

void SceneTutorial::Update()
{
	// �X�^�[�g���o
	if (m_startStagingTime > 0.0f)
	{
		m_startStagingTime--;	// �X�^�[�g���o�̎���

		if (m_startStagingTime > kStartTime - 3.0f)
		{
			m_startDis.x -= 5.0f;
			m_stagingFade += 45;
		}
		else if (m_startStagingTime <= kStartTime - 2.0f && m_startStagingTime >= 40.0f)
		{
			m_startDis.x -= 1.0f;
			m_stagingFade += 30;
			if (m_stagingFade > 255)
			{
				m_stagingFade = 255;
			}
		}
		else if (m_startStagingTime <= 0)
		{
			// 0.5�b�ԑҋ@
			WaitTimer(500);
		}
		else
		{
			m_startDis.x -= 40.0f;
			m_stagingFade -= 40;
		}
		return;
	}

	//�@�t�F�[�h�C���A�E�g
	if (m_isSceneGameOver || m_isSceneClear || m_isSceneTitle || m_isSceneEnd)
	{
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else
	{
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}

	// �J�E���g�_�E�����o
	m_readyCount--;
	if (m_readyCount >= 0) return;
	else m_readyCount = 0;

	// �X�^�[�gSE��炵�����BGM��炷
	if (CheckSoundMem(m_startSE) == 0 && CheckSoundMem(m_bgm) == 0)
	{
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
	}

	// �G�����ׂē|������N���A���o���s��
	if (m_enemyTotalNum <= 0)
	{
		UpdateClearStaging();
	}
	if (m_clearStagingTime <= 0.0f)
	{
		// 0.5�b��ɃN���A��ʂɑJ��
		m_isSceneClear = true;
		WaitTimer(500);
		return;
	}

	// �p�b�h�̓��͏�Ԃ��擾
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �|�[�Y��ʂ̍X�V
	m_pPause->Update();

	// �|�[�Y��ʂ��\������Ă���ꍇ��ʂ��~�߂�
	if (m_pPause->IsPause())
	{
		// BGM�ꎞ��~
		StopSoundMem(m_bgm);

		// ���g���C���I�����ꂽ�珉��������
		if (m_pPause->IsSelectRetry())
		{
			m_pPlayer->Init(m_pBg);
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

	// ����؂�ւ���ʂ��\������Ă���ꍇ��ʂ��~�߂�
	if (m_pPause->IsSelectShotExist()) return;

	// �^�C���J�E���g
	if (m_enemyTotalNum > 0)
	{
		m_time++;
	}

	// �w�i�̍X�V
	m_pBg->Update();

	// �v���C���[�̍X�V
	if (m_enemyTotalNum > 0)
	{
		m_pPlayer->Update();
	}

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

				// �A�C�e��2����SE��炷
				if (CheckSoundMem(m_lineMoveSE) == 0)
				{
					PlaySoundMem(m_lineMoveSE, DX_PLAYTYPE_BACK, true);
				}
			}
			else
			{
				m_isExistLineMove = false;
				StopSoundMem(m_lineMoveSE);
			}

			// �e�̓����蔻��
			Rect shotRect = m_pShot[i]->GetColRect();
			// �v���C���[�ƒe�̓����蔻��
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
				m_shakeFrame = 2;
				m_ampFrame = 5;
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

	// ��ʂ�h�炷
	m_shakeFrame--;
	m_ampFrame *= 0.95f;
	if (m_shakeFrame < 0)
	{
		m_shakeFrame = 0;
	}

	// �v���C���[��HP��0�ɂȂ����ꍇ
	if (m_pPlayer->GetHp() <= 0)
	{
		// �v���C���[�̎c�@��0�ȉ��̏ꍇ
		if (m_pPlayer->GetLife() <= 0)
		{
			// 1�b��ɃQ�[���I�[�o�[��ʂɑJ��
			WaitTimer(1000);
			m_isSceneGameOver = true;
			StopSoundMem(m_bgm);
			return;
		}
		else
		{
			// ���S�A�j���[�V�����ナ�g���C
			if (m_pPlayer->GetDeadFrame() <= 0)
			{
				m_isRetry = true;
				Init();
			}
		}
	}

#ifdef _DEBUG
	// MEMO:ESCAPE�L�[or���X�e�B�b�N�������݂ŃN���A��ʂɈړ�
	if (Pad::IsTrigger(pad & PAD_INPUT_START))
	{
		m_enemyTotalNum = 0;
	}
#endif
}

void SceneTutorial::Draw()
{
	// ��������
	SetDrawScreen(m_gameScreenHandle);
	// �`���X�N���[�����N���A����
	ClearDrawScreen();

	// �w�i�̕`��
	m_pBg->Draw();

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

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	/*��ʉ��ɏ��\��*/
	DrawInfo();

	/*�|�[�Y��ʁA����؂�ւ���ʂ̕\��*/
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

	// �t�F�[�h�C���A�E�g
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x0e0918, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �o�b�N�o�b�t�@�ɏ������ސݒ�ɖ߂��Ă���
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[����ʂ��o�b�N�o�b�t�@�ɕ`�悷��
	int screenX = 0;
	int screenY = 0;
	if (m_shakeFrame > 0)
	{
		// ��ʗh��
		screenX = GetRand(4) - 2 * m_ampFrame;
		screenY = GetRand(4) - 2 * m_ampFrame;
	}
	DrawRectGraph(screenX, screenY, 0, 0, Game::kScreenWidth, Game::kScreenHeight, m_gameScreenHandle, true);

	// �X�^�[�g�ƃN���A�����̕\��
	if (m_startStagingTime > 0.0f)
	{
		DrawStartStaging();
	}
	else if (m_startStagingTime <= 0.0f)
	{
		if (m_readyCount % 10 >= 8) return;

		if (m_readyCount > 0)
		{
			DrawStringToHandle(Game::kScreenWidth * 0.5f - 30, Game::kScreenHeight * 0.5f, "READY", 0xffffff, m_pFont->GetFontStaging());
		}
	}

	// �N���A�̉��o�ƃ^�C���\��
	if (m_enemyTotalNum <= 0 && m_clearStagingTime >= 0.0f)
	{
		DrawClearStaging();
	}
}

/// <summary>
/// �e�̐���
/// </summary>
/// <param name="pShot">�e�̎��</param>
/// <returns></returns>
bool SceneTutorial::AddShot(ShotBase* pShot)
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
/// �N���A���o�̍X�V
/// </summary>
void SceneTutorial::UpdateClearStaging()
{
	m_clearStagingTime--;
	m_stagingFade += 150;

	// �N���ASE1�񂾂���炷
	StopSoundMem(m_bgm);
	if (CheckSoundMem(m_clearSE) == 0 && m_clearStagingTime >= kClearTime - 60.0f)
	{
		m_stagingFade = 0;
		PlaySoundMem(m_clearSE, DX_PLAYTYPE_BACK, true);
		return;
	}
	// �ԉ΂̉��𗬂�
	else if (m_clearStagingTime <= kClearTime - 120.0f || m_clearStagingTime > 0.0f)
	{
		if (CheckSoundMem(m_fireworksSE) == 0)
		{
			PlaySoundMem(m_fireworksSE, DX_PLAYTYPE_BACK, true);
			return;
		}
	}
}

/// <summary>
/// �A�C�e������
/// </summary>
/// <param name="enemyIndex">�G</param>
// HP����
void SceneTutorial::DropHpSmallRecovery(int enemyIndex)
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
void SceneTutorial::DropHpGreatRecovery(int enemyIndex)
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
void SceneTutorial::DropShotSmallRecovery(int enemyIndex)
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
void SceneTutorial::DropShotGreatRecovery(int enemyIndex)
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
void SceneTutorial::DropLifeRecovery(int enemyIndex)
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
void SceneTutorial::DropFullHpRecovery()
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryFullHp;
			m_pRecovery[i]->Init(m_pBg);
			m_pRecovery[i]->Start({ 4200, 750 }); // �A�C�e���̈ʒu��ݒ�
			return;
		}
	}
}

/// <summary>
/// �G�̐���
/// </summary>
void SceneTutorial::CreateEnemy()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		switch (i)
		{
		case 0:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(2200.0f, 400.0f, 400.0f);
			m_pEnemy[i]->Init(m_pBg, m_pPlayer);
			break;
		case 1:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(3300.0f, 240.0f, 80.0f);
			m_pEnemy[i]->Init(m_pBg, m_pPlayer);
			break;
		case 2:
			m_pEnemy[i] = new EnemyBear;
			m_pEnemy[i]->Start(6900.0f, 400.0f, 200.0f);
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
void SceneTutorial::CreateItem(int enemyIndex)
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
void SceneTutorial::DrawInfo()
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
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY - 40, "HP :", 0xffffff, m_pFont->GetFont2());
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
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY * 2 - 40, "F :", 0xffffff, m_pFont->GetFont2());
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
void SceneTutorial::DrawShotChange()
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
void SceneTutorial::DrawPause()
{
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY, 0xffffff, m_pFont->GetFont(), "�Q�[���ɖ߂�");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 2, 0xffffff, m_pFont->GetFont(), "���g���C");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 3, 0xffffff, m_pFont->GetFont(), "�^�C�g���ɖ߂�");
}

/// <summary>
/// �X�^�[�g���o�̕`��
/// </summary>
void SceneTutorial::DrawStartStaging()
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
void SceneTutorial::DrawClearStaging()
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

	// TODO:�����\����ԉ΂�������
	if (m_clearStagingTime < 180.0f)
	{
		int disX = GetRand(1400) - 1400;
		int srcX = 0;
		int srcY = 0;
		DrawRectRotaGraph(disX, Game::kScreenHeight * 0.5f - 400, srcX, srcY, 64, 64, 1.0f, 0.0f, m_fireworks, true);
	}
}