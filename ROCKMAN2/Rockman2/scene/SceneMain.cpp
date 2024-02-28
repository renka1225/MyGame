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
/// 定数
/// </summary>
namespace
{
	/*演出*/
// スタート演出時間
	constexpr float kStartTime = 120.0f;
	constexpr float kClearTime = 240.0f;
	constexpr float kGameoverTime = 300.0f;
	// readyカウント演出
	constexpr int kReadyCount = 60;
	// 花火の打ち上げ速度
	constexpr float kFireworksSpeed = 20.0f;
	// 花火の画像切り出しサイズ
	constexpr int kFireworksWidth = 92;
	constexpr int kFireworksHeight = 94;
	// 花火の表示フレーム
	constexpr int kFireworksFrame = 10;

	/*ポーズ画面*/
	// ポーズ画面の文字表示位置
	constexpr int kTextPosX = 850;
	constexpr int kTextPosY = 420;
	// 弾数表示位置
	constexpr int kBarPosX = 850;
	constexpr int kBarPosY = 455;
	// 弾数表示間隔
	constexpr int kBarInterval = 23;
	// 弾数表示サイズ
	constexpr int kPauseShotNumWidth = 18;
	constexpr int kPauseShotNumHeight = 20;
	// 弾数Y座標表示間隔
	constexpr int kIntervalY = 70;

	/*ゲーム内*/
	// 黒枠のサイズ
	constexpr int kFrameSize = 270;
	// 残機、敵数、タイム表示位置
	constexpr int kInfoTextPosX = 30;	// 横
	constexpr int kInfoTextPosY = 290;	// 縦
	// 弾数表示位置
	constexpr int kShotNumDisPosX = static_cast<int>(Game::kScreenWidth - kFrameSize + 10);	// 横
	constexpr int kShotNumDisPosY = static_cast<int>(Game::kScreenHeight * 0.5 - 140);		// 縦
	// 弾数表示間隔
	constexpr int kShotNumIntervalX = 25;	// 横
	constexpr int kShotNumIntervalY = 100;	// 縦
	// 弾数表示サイズ
	constexpr int kShotDisWidth = 18;	// 横
	constexpr int kShotDisHeight = 20;	// 縦
	// フレームの表示位置
	constexpr int kFramePosY = static_cast<int>(Game::kScreenHeight * 0.5 - 199);

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
}


SceneMain::~SceneMain()
{
}


void SceneMain::CreateItem(int enemyIndex)
{
	int getRandDrop = GetRand(100);
	if (getRandDrop <= 20)
	{
		DropHpSmallRecovery(enemyIndex); // HP回復(小)
	}
	else if (getRandDrop <= 35)
	{
		DropHpGreatRecovery(enemyIndex);	// HP回復(大)
	}
	else if (getRandDrop <= 65)
	{
		DropShotSmallRecovery(enemyIndex); // 弾エネルギー(小)
	}
	else if (getRandDrop <= 90)
	{
		DropShotGreatRecovery(enemyIndex); // 弾エネルギー(大)
	}
	else if (getRandDrop <= 100)
	{
		DropLifeRecovery(enemyIndex);	// 残機
	}
}

/// <summary>
/// 武器切り替え画面表示
/// </summary>
void SceneMain::DrawShotChange()
{
	// 現在のHPを表示
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffffff, m_pFont->GetFont(), "P :"); // 文字
	for (int i = 0; i < m_pPlayer->GetHp(); i++) // 現在のHP分だけ四角を描画する
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kPauseShotNumHeight,
			0xeee8aa, true);
	}

	// 現在の弾エネルギー数を表示
	// メタル
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY, 0xffffff, m_pFont->GetFont(), "M :"); // 文字
	DrawExtendGraph(kTextPosX + 50, kTextPosY + kIntervalY, kTextPosX + 75, kTextPosY + kIntervalY + 25, m_metalHandle, true); // メタルの画像
	for (int i = 0; i < m_pPlayer->GetMetalEnergy(); i++) // 現在のエネルギー分だけ四角を描画する
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY + kPauseShotNumHeight,
			0xc0c0c0, true);
	}

	// ファイアー
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 2, 0xffffff, m_pFont->GetFont(), "F :"); // 文字
	DrawExtendGraph(kTextPosX + 50, kTextPosY + kIntervalY * 2, kTextPosX + 75, kTextPosY + kIntervalY * 2 + 25, m_fireHandle, true); // ファイアの画像
	for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++) // 現在のエネルギー分だけ四角を描画する
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY * 2,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY * 2 + kPauseShotNumHeight,
			0xff4500, true);
	}

	// アイテム2号
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 3, 0xffffff, m_pFont->GetFont(), "L :"); // 文字
	DrawGraph(kTextPosX + 45, kTextPosY + kIntervalY * 3 + 3, m_lineMoveHandle, true); // 2号の画像
	for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++) // 現在のエネルギー分だけ四角を描画する
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY * 3,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY * 3 + kPauseShotNumHeight,
			0xb22222, true);
	}

	// 現在のE缶数を表示
	DrawStringToHandle(kTextPosX, kTextPosY + kIntervalY * 4, "E : ", 0xffffff, m_pFont->GetFont()); // 文字
	if (m_pPlayer->GetFullHpRecovery() == 1)
	{
		DrawGraph(kTextPosX, kBarPosY + kIntervalY * 4 - 5, m_fullHpRecHandle, true);
	}
}


/// <summary>
/// ポーズ画面表示
/// </summary>
void SceneMain::DrawPause()
{
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY, 0xffffff, m_pFont->GetFont(), "ゲームに戻る");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 2, 0xffffff, m_pFont->GetFont(), "リトライ");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 3, 0xffffff, m_pFont->GetFont(), "タイトルに戻る");
}


/// <summary>
/// スタート演出の描画
/// </summary>	
void SceneMain::DrawStartStaging()
{
	// フェードイン→アウト
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_stagingFade);
	DrawGraph(static_cast<int>(m_startDis.x), static_cast<int>(Game::kScreenHeight * 0.5 - 220), m_startHandle, true);

	DrawStringToHandle(static_cast<int>(m_startDis.x + Game::kScreenWidth * 0.5 - 170), static_cast<int>(Game::kScreenHeight * 0.5 - 100),
		"敵をすべてたおせ！\n", 0xffffff, m_pFont->GetFontStaging());

	DrawFormatStringToHandle(static_cast<int>(m_startDis.x + Game::kScreenWidth * 0.5 - 60), static_cast<int>(Game::kScreenHeight * 0.5 + 30),
		0xffffff, m_pFont->GetFontStaging(), "%d / %d\n", m_enemyTotalNum, m_enemyTotalNum);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


/// <summary>
/// クリア演出の描画
/// </summary>
void SceneMain::DrawClearStaging()
{
	// タイム
	int milliSec = static_cast<int>(m_time * 1000 / 60);
	int sec = (milliSec / 1000) % 60;
	int min = (milliSec / 1000) / 60;
	milliSec %= 1000;

	// クリアの文字を表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_stagingFade);
	DrawGraph(0, static_cast<int>(Game::kScreenHeight * 0.5 - 200), m_startHandle, true);

	DrawStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5 - 70), static_cast<int>(Game::kScreenHeight * 0.5 - 100),
		"CLEAR!\n", 0xffe44d, m_pFont->GetFontStaging());

	DrawFormatStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5 - 260), static_cast<int>(Game::kScreenHeight * 0.5 + 30),
		0xffffff, m_pFont->GetFontStaging(), "クリアタイム : % 3d:%02d.%03d", min, sec, milliSec);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 文字表示後花火をあげる
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