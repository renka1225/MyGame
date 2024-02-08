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

SceneMain::SceneMain() :
	m_pFont(nullptr),
	m_pPause(nullptr),
	m_pPlayer(nullptr),
	m_drawValue(0),
	m_isGetFullHpRecovery(false),
	m_enemyTotalNum(0),
	m_time(0.0f),
	m_isExistLineMove(false),
	m_isSceneGameOver(false),
	m_isSceneClear(false),
	m_isSceneTitle(false),
	m_isSceneEnd(false),
	m_fadeAlpha(255),
	m_stagingFade(0),
	m_startStagingTime(0.0f),
	m_clearStagingTime(0.0f),
	m_gameoverStagingTime(0.0f)
{
	// ���ǂݍ���
	m_bgm = LoadSoundMem("data/sound/BGM/stage1.mp3");
	m_enemyDeadSE = LoadSoundMem("data/sound/SE/enemyDamage.mp3");
	m_recoverySE = LoadSoundMem("data/sound/SE/recovery.mp3");
	m_lineMoveSE = LoadSoundMem("data/sound/SE/shotLine.mp3");
	m_startSE = LoadSoundMem("data/sound/BGM/start.wav");
	m_clearSE = LoadSoundMem("data/sound/SE/clear.wav");
	m_fireworksSE = LoadSoundMem("data/sound/SE/fireworks.wav");

	// �摜�ǂݍ���
	m_frameHandle = LoadGraph("data/image/UI/frame.png");
	m_shotSelectHandle = LoadGraph("data/image/UI/shotSelect.png");
	m_startHandle = LoadGraph("data/image/UI/start.png");
	m_fireworks = LoadGraph("data/image/Effect/fireworks.png");
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
}

void SceneMain::Update()
{
}

void SceneMain::Draw()
{
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
/// �G�̐���
/// </summary>
void SceneMain::CreateEnemy()
{
}

/// <summary>
/// �A�C�e������
/// </summary>
/// <param name="enemyIndex">�G</param>
// HP����
void SceneMain::DropHpSmallRecovery(int enemyIndex)
{
}
// HP���
void SceneMain::DropHpGreatRecovery(int enemyIndex)
{
}
// �e����
void SceneMain::DropShotSmallRecovery(int enemyIndex)
{
}
// �e���
void SceneMain::DropShotGreatRecovery(int enemyIndex)
{
}
// �c�@��
void SceneMain::DropLifeRecovery(int enemyIndex)
{
}
// HP�S��
void SceneMain::DropFullHpRecovery()
{
}

/// <summary>
/// �񕜃A�C�e���h���b�v
/// </summary>
/// <param name="enemyIndex">�G</param>
void SceneMain::CreateItem(int enemyIndex)
{
}

/// <summary>
/// �e���A�G���\��
/// </summary>
void SceneMain::DrawInfo()
{
}

/// <summary>
/// ����؂�ւ���ʕ\��
/// </summary>
void SceneMain::DrawShotChange()
{
}

/// <summary>
/// �|�[�Y��ʕ\��
/// </summary>
void SceneMain::DrawPause()
{
;
}

/// <summary>
/// �X�^�[�g���o�̕`��
/// </summary>
void SceneMain::DrawStartStaging()
{
}

/// <summary>
/// �N���A���o�̕`��
/// </summary>
void SceneMain::DrawClearStaging()
{
}
