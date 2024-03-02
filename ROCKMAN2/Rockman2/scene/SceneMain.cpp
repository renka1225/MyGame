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
	/*スタート演出*/
	// スタート演出時間
	constexpr float kStartTime = 120.0f;
	// readyカウント演出
	constexpr int kReadyCount = 60;
	// 四角表示位置
	constexpr int kStartBackPos = 320;
	// クリア条件表示位置調整
	constexpr int kStartDisPosX = 790;
	constexpr int kStartDisPosY = 440;
	// 敵数表示位置
	constexpr int kEnemyNumDisPosX = 900;
	constexpr int kEnemyNumDisPosY = 570;

	/*クリア演出*/
	// クリア演出時間
	constexpr float kClearTime = 240.0f;
	// クリアSEを流し始める時間
	constexpr float kClearSETime = 180.0f;
	// クリア時のフェード時間
	constexpr int kClearFadeFrame = 150;
	// 四角表示位置
	constexpr int kClearBackPos = 340;
	// クリアの文字表示位置調整
	constexpr int kClearDisPosX = 890;
	constexpr int kClearDisPosY = 440;
	// クリア時間表示位置
	constexpr int kClearTimePosX = 700;
	constexpr int kClearTimePosY = 570;

	/*花火の演出*/
	// 花火を打ち上げ始める時間
	constexpr float kFireworks1Time = 220.0f;
	constexpr float kFireworks2Time = 210.0f;
	constexpr float kFireworks3Time = 180.0f;
	constexpr float kFireworks4Time = 150.0f;
	constexpr float kFireworks5Time = 120.0f;
	constexpr float kFireworks6Time = 100.0f;
	constexpr float kFireworks7Time = 80.0f;
	// 描画時間調整
	constexpr float kDrawFireworks = 10.0f;
	// 描画終了時間
	constexpr float kDrawEndFireworks1 = 70.0f;	// 1つ目
	constexpr float kDrawEndFireworks2 = 50.0f;	// 2つ目
	constexpr float kDrawEndFireworks3 = 30.0f;	// 3つ目
	constexpr float kDrawEndFireworks4 = 10.0f;	// 4つ目
	constexpr float kDrawEndFireworks5 = 5.0f;	// 5つ目
	constexpr float kDrawEndFireworks6 = 0.0f;	// 6つ目
	// 花火の表示フレーム
	constexpr int kFireworksFrame = 10;
	// 花火の打ち上げ速度
	constexpr float kFireworksSpeed = 20.0f;
	// 花火の画像切り出しサイズ
	constexpr int kFireworksWidth = 92;
	constexpr int kFireworksHeight = 94;
	// 花火の拡大率
	constexpr float kFireworksScale1 = 5.0f;
	constexpr float kFireworksScale2 = 6.0f;

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

	/*アイテムドロップの確率*/
	constexpr int kItemDropMax = 100;		// 最大確率
	constexpr int kHpSmallRec = 20;			// HP回復(小)
	constexpr int kHpGreatRec = 35;			// HP回復(大)
	constexpr int kShotSmallRec = 60;		// 弾回復(小)
	constexpr int kShotGreatRec = 80;		// 弾回復(大)
	constexpr int kLifeRec = 85;			// 残機回復
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

	// 画像読み込み
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
/// アイテムドロップ
/// </summary>
/// <param name="enemyIndex">アイテムドロップする敵</param>
void SceneMain::CreateItem(int enemyIndex)
{
	int getRandDrop = GetRand(kItemDropMax);
	if (getRandDrop <= kHpSmallRec)
	{
		DropHpSmallRecovery(enemyIndex); // HP回復(小)
	}
	else if (getRandDrop <= kHpGreatRec)
	{
		DropHpGreatRecovery(enemyIndex);	// HP回復(大)
	}
	else if (getRandDrop <= kShotSmallRec)
	{
		DropShotSmallRecovery(enemyIndex); // 弾エネルギー(小)
	}
	else if (getRandDrop <= kShotGreatRec)
	{
		DropShotGreatRecovery(enemyIndex); // 弾エネルギー(大)
	}
	else if (getRandDrop <= kLifeRec)
	{
		DropLifeRecovery(enemyIndex);	// 残機
	}
	else
	{
		// 何もドロップしない
	}
}


/// <summary>
/// クリア演出処理
/// </summary>
void SceneMain::UpdateClearStaging()
{
	m_clearStagingTime--;
	m_stagingFade += kClearFadeFrame;

	// クリアSE1回だけを鳴らす
	StopSoundMem(m_bgm);
	if (CheckSoundMem(m_clearSE) == 0 && m_clearStagingTime >= kClearSETime)
	{
		m_stagingFade = 0;
		PlaySoundMem(m_clearSE, DX_PLAYTYPE_BACK, true);
		return;
	}
	// 花火の更新
	else if (m_clearStagingTime <= kFireworks1Time && m_clearStagingTime > 0.0f)
	{
		// 花火を上にあげる
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
	
		// 音を流す
		if (CheckSoundMem(m_fireworksSE) == 0)
		{
			PlaySoundMem(m_fireworksSE, DX_PLAYTYPE_BACK, true);
			return;
		}
	}
}


/// <summary>
/// 回復アイテムの処理
/// </summary>
/// <param name="playerRect"></param>
void SceneMain::UpdateRecovery(Rect playerRect)
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pRecovery[i]) continue;

		m_pRecovery[i]->Update();

		Rect recoveryRect = m_pRecovery[i]->GetColRect();	// 回復アイテムの当たり判定
		// プレイヤーと回復アイテムの当たり判定
		if (playerRect.IsCollision(recoveryRect))
		{
			// SEを鳴らす
			PlaySoundMem(m_recoverySE, DX_PLAYTYPE_BACK, true);

			if (dynamic_cast<RecoverySmallHp*>(m_pRecovery[i])) // HP小回復
			{
				m_pPlayer->HpSmallRecovery();
			}
			else if (dynamic_cast<RecoveryGreatHp*>(m_pRecovery[i])) // HP大回復
			{
				m_pPlayer->HpGreatRecovery();
			}
			else if (dynamic_cast<RecoverySmallShot*>(m_pRecovery[i])) // 弾小回復
			{
				m_pPlayer->ShotSmallRecovery();
			}
			else if (dynamic_cast<RecoveryGreatShot*>(m_pRecovery[i])) // 弾大回復
			{
				m_pPlayer->ShotGreatRecovery();
			}
			else if (dynamic_cast<RecoveryLife*>(m_pRecovery[i])) // 残機回復
			{
				m_pPlayer->LifeRecovery();
			}
			else if (dynamic_cast<RecoveryFullHp*>(m_pRecovery[i])) // HP全回復
			{
				if (!m_isGetFullHpRecovery)  // E缶を取得してない場合
				{
					m_pPlayer->GetHpFullRecovery();
					m_isGetFullHpRecovery = true;
				}
			}

			// 取得したらアイテムを消す
			delete m_pRecovery[i];
			m_pRecovery[i] = nullptr;
		}
		else if (!m_pRecovery[i]->IsExist())
		{
			// アイテムを消す
			delete m_pRecovery[i];
			m_pRecovery[i] = nullptr;
		}
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
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * kShotFire, 0xffffff, m_pFont->GetFont(), "F :"); // 文字
	DrawExtendGraph(kTextPosX + 50, kTextPosY + kIntervalY * 2, kTextPosX + 75, kTextPosY + kIntervalY * kShotFire + 25, m_fireHandle, true); // ファイアの画像
	for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++) // 現在のエネルギー分だけ四角を描画する
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY * 2,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY * 2 + kPauseShotNumHeight,
			0xff4500, true);
	}

	// アイテム2号
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * kShotLineMove, 0xffffff, m_pFont->GetFont(), "L :"); // 文字
	DrawGraph(kTextPosX + 45, kTextPosY + kIntervalY * kShotLineMove + 3, m_lineMoveHandle, true); // 2号の画像
	for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++) // 現在のエネルギー分だけ四角を描画する
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY * 3,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY * 3 + kPauseShotNumHeight,
			0xb22222, true);
	}

	// 現在のE缶数を表示
	DrawStringToHandle(kTextPosX, kTextPosY + kIntervalY * kRecovery, "E : ", 0xffffff, m_pFont->GetFont()); // 文字
	if (m_pPlayer->GetFullHpRecovery() == 1)
	{
		DrawGraph(kTextPosX, kBarPosY + kIntervalY * kRecovery - 5, m_fullHpRecHandle, true);
	}
}


/// <summary>
/// ポーズ画面表示
/// </summary>
void SceneMain::DrawPause()
{
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY, 0xffffff, m_pFont->GetFont(), "ゲームに戻る");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * (kPauseRetry + 1), 0xffffff, m_pFont->GetFont(), "リトライ");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * (kPauseTitle + 1), 0xffffff, m_pFont->GetFont(), "タイトルに戻る");
}


/// <summary>
/// スタート演出の描画
/// </summary>	
void SceneMain::DrawStartStaging()
{
	// フェードイン→アウト
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_stagingFade);
	DrawGraph(static_cast<int>(m_startDis.x), kStartBackPos, m_startHandle, true);

	DrawStringToHandle(static_cast<int>(m_startDis.x + kStartDisPosX), kStartDisPosY,
		"敵をすべてたおせ！\n", 0xffffff, m_pFont->GetFontStaging());

	DrawFormatStringToHandle(static_cast<int>(m_startDis.x + kEnemyNumDisPosX), kEnemyNumDisPosY,
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
	DrawGraph(0, kClearBackPos, m_startHandle, true);

	DrawStringToHandle(kClearDisPosX, kClearDisPosY,
		"CLEAR!\n", 0xffe44d, m_pFont->GetFontStaging());

	DrawFormatStringToHandle(kClearTimePosX, kClearTimePosY,
		0xffffff, m_pFont->GetFontStaging(), "クリアタイム : % 3d:%02d.%03d", min, sec, milliSec);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 文字表示後花火をあげる
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