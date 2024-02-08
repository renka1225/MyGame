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
	// 音読み込み
	m_bgm = LoadSoundMem("data/sound/BGM/stage1.mp3");
	m_enemyDeadSE = LoadSoundMem("data/sound/SE/enemyDamage.mp3");
	m_recoverySE = LoadSoundMem("data/sound/SE/recovery.mp3");
	m_lineMoveSE = LoadSoundMem("data/sound/SE/shotLine.mp3");
	m_startSE = LoadSoundMem("data/sound/BGM/start.wav");
	m_clearSE = LoadSoundMem("data/sound/SE/clear.wav");
	m_fireworksSE = LoadSoundMem("data/sound/SE/fireworks.wav");

	// 画像読み込み
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
/// 弾の生成
/// </summary>
/// <param name="pShot">弾の種類</param>
/// <returns></returns>
bool SceneMain::AddShot(ShotBase* pShot)
{
	// nullptrを渡されたら止まる
	assert(pShot);

	for (int i = 0; i < m_pShot.size(); i++)
	{
		// 使用中なら次のチェックを行う
		if (m_pShot[i])continue;

		// m_pShot[i] == nullptrなので新しく登録する
		m_pShot[i] = pShot;

		// 登録したら終了
		return true;
	}

	// m_pShotにポインタを登録できなかった
	delete pShot;
	return false;
}

/// <summary>
/// 敵の生成
/// </summary>
void SceneMain::CreateEnemy()
{
}

/// <summary>
/// アイテム生成
/// </summary>
/// <param name="enemyIndex">敵</param>
// HP小回復
void SceneMain::DropHpSmallRecovery(int enemyIndex)
{
}
// HP大回復
void SceneMain::DropHpGreatRecovery(int enemyIndex)
{
}
// 弾小回復
void SceneMain::DropShotSmallRecovery(int enemyIndex)
{
}
// 弾大回復
void SceneMain::DropShotGreatRecovery(int enemyIndex)
{
}
// 残機回復
void SceneMain::DropLifeRecovery(int enemyIndex)
{
}
// HP全回復
void SceneMain::DropFullHpRecovery()
{
}

/// <summary>
/// 回復アイテムドロップ
/// </summary>
/// <param name="enemyIndex">敵</param>
void SceneMain::CreateItem(int enemyIndex)
{
}

/// <summary>
/// 弾数、敵数表示
/// </summary>
void SceneMain::DrawInfo()
{
}

/// <summary>
/// 武器切り替え画面表示
/// </summary>
void SceneMain::DrawShotChange()
{
}

/// <summary>
/// ポーズ画面表示
/// </summary>
void SceneMain::DrawPause()
{
;
}

/// <summary>
/// スタート演出の描画
/// </summary>
void SceneMain::DrawStartStaging()
{
}

/// <summary>
/// クリア演出の描画
/// </summary>
void SceneMain::DrawClearStaging()
{
}
