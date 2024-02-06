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
	// 画面内に1度に出せる弾数
	constexpr int kShotMax = 3;
	// 画面内に1度に出せる回復アイテム数
	constexpr int kRecoveryMax = 5;

	// 登場する敵数
	constexpr int kEnemyMax = 10;

	// プレイヤーの画像サイズ
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 64;

	// マップチップのサイズ
	constexpr int kMapChipWidth = 32;
	constexpr int kMapChipHeight = 32;

	/*演出*/
	// スタート演出時間
	constexpr float kStartTime = 120.0f;
	constexpr float kClearTime = 60.0f;
	constexpr float kGameoverTime = 300.0f;

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
	constexpr int kShotNumDisPosX = Game::kScreenWidth - kFrameSize + 10;	// 横
	constexpr int kShotNumDisPosY = Game::kScreenHeight * 0.5 - 140;		// 縦
	// 弾数表示間隔
	constexpr int kShotNumIntervalX = 25;	// 横
	constexpr int kShotNumIntervalY = 100;	// 縦
	// 弾数表示サイズ
	constexpr int kShotDisWidth = 18;	// 横
	constexpr int kShotDisHeight = 20;	// 縦
	// フレームの表示位置
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
	// プレイヤーのメモリ確保
	m_pPlayer = new Player{ this };

	// 背景のメモリ確保
	m_pBg = new Bg;
	m_pBg->SetPlayer(m_pPlayer);
	m_pPlayer->SetBg(m_pBg);

	// フォント
	m_pFont = new FontManager;

	// ポーズ画面のメモリ確保
	m_pPause = new ScenePause{ m_pPlayer };

	// ショットの初期化
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr; // 未使用状態にする
	}

	// 敵の初期化
	m_pEnemy.resize(kEnemyMax);
	CreateEnemy();

	// 回復アイテムの初期化
	m_pRecovery.resize(kRecoveryMax);
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		m_pRecovery[i] = nullptr; // 未使用状態にする
	}

	// 音読み込み
	m_bgm = LoadSoundMem("data/sound/BGM/stage1.mp3");
	m_enemyDeadSE = LoadSoundMem("data/sound/SE/enemyDamage.mp3");
	m_recoverySE = LoadSoundMem("data/sound/SE/recovery.mp3");
	m_lineMoveSE = LoadSoundMem("data/sound/SE/shotLine.mp3");
	m_startSE = LoadSoundMem("data/sound/BGM/start.wav");
	m_clearSE = LoadSoundMem("data/sound/SE/clear.wav");

	// 画像
	m_frameHandle = LoadGraph("data/image/UI/frame.png");
	m_shotSelectHandle = LoadGraph("data/image/UI/shotSelect.png");
	m_startHandle = LoadGraph("data/image/UI/start.png");
}

SceneMain::~SceneMain()
{
	// 背景のメモリ解放
	delete m_pBg;
	m_pBg = nullptr;

	// フォント
	delete m_pFont;
	m_pFont = nullptr;

	// ポーズ画面のメモリ確保
	delete m_pPause;
	m_pPause = nullptr;

	// プレイヤーのメモリ解放
	delete m_pPlayer;
	m_pPlayer = nullptr;

	// ショットのメモリ解放
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])
		{
			// nullptrでない場合、nullptrを入れる
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}

	// 敵のメモリ解放
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			// nullptrでない場合、nullptrを入れる
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;
		}
	}

	// 回復アイテムのメモリ解放
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (m_pRecovery[i])
		{
			// nullptrでない場合、nullptrを入れる
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
	printfDx("ステージベース");
#endif // _DEBUG
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
/// アイテム生成
/// </summary>
/// <param name="enemyIndex">敵</param>
// HP小回復
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
// HP大回復
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
// 弾小回復
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
// 弾大回復
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
// 残機回復
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
// HP全回復
void SceneMain::DropFullHpRecovery()
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryFullHp;
			m_pRecovery[i]->Init(m_pBg);
			m_pRecovery[i]->Start({ 1680, 700 }); // アイテムの位置を設定
			return;
		}
	}
}

/// <summary>
/// 敵の生成
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
/// 回復アイテムドロップ
/// </summary>
/// <param name="enemyIndex">敵</param>
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
	else if (getRandDrop <= 60)
	{
		DropShotSmallRecovery(enemyIndex); // 弾エネルギー(小)
	}
	else if (getRandDrop <= 80)
	{
		DropShotGreatRecovery(enemyIndex); // 弾エネルギー(大)
	}
	else if (getRandDrop <= 90)
	{
		DropLifeRecovery(enemyIndex);	// 残機
	}
}

/// <summary>
/// 弾数、敵数表示
/// </summary>
void SceneMain::DrawInfo()
{
	// 画面横に四角を表示
	DrawBox(0, 0, kFrameSize, Game::kScreenHeight, 0x483d8b, true); // 左側
	DrawBox(Game::kScreenWidth - kFrameSize, 0, Game::kScreenWidth, Game::kScreenHeight, 0x483d8b, true); // 右側

	// 枠表示
	DrawGraph(0, kFramePosY, m_frameHandle, true); // 左側
	DrawGraph(Game::kScreenWidth - kFrameSize, kFramePosY, m_frameHandle, true); // 右側
	
	/*残機、残り敵数、タイムを左側に表示*/

	// 残機数表示
	DrawStringToHandle(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY, "残機", 0xffffff, m_pFont->GetFont2());
	DrawFormatStringToHandle(kInfoTextPosX + 80, kInfoTextPosY + kShotNumIntervalY + 40, 0xffaa00, m_pFont->GetFont3(), " %d", m_pPlayer->GetLife());

	// 敵数表示
	DrawStringToHandle(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY * 2 + 10, "敵数", 0xffffff, m_pFont->GetFont2());
	DrawFormatStringToHandle(kInfoTextPosX + 50, kInfoTextPosY + kShotNumIntervalY * 2 + 50, 0xffaa00, m_pFont->GetFont3(), " %d / %d", m_enemyTotalNum, kEnemyMax);

	// タイム
	int milliSec = static_cast<int>(m_time) * 1000 / 60;
	int sec = (milliSec / 1000) % 60;
	int min = (milliSec / 1000) / 60;
	milliSec %= 1000;

	DrawStringToHandle(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY * 3 + 30, "タイム", 0xffffff, m_pFont->GetFont2());
	DrawFormatStringToHandle(kInfoTextPosX + 20, kInfoTextPosY + kShotNumIntervalY * 3 + 70, 0xffaa00, m_pFont->GetFont3(), " %3d:%02d.%03d", min, sec, milliSec);

	
/// <summary>
/// HP、武器の弾数を右側に表示
/// </summary>
	// HP
	if (m_pPlayer->IsBuster())
	{
		// 武器選択中の表示
		DrawGraph(Game::kScreenWidth - kFrameSize + 3, kShotNumDisPosY - 10, m_shotSelectHandle, true);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY - 40, "HP :" ,0xffffff, m_pFont->GetFont2());
	// 現在のHP分だけ四角を描画する
	for (int i = 0; i < m_pPlayer->GetHp(); i++)
	{
		DrawBox(kShotNumDisPosX + kShotNumIntervalX * i,
			kShotNumDisPosY,
			(kShotNumDisPosX + kShotNumIntervalX * i) + kShotDisWidth,
			kShotNumDisPosY + kPauseShotNumHeight,
			0xeee8aa, true);
	}

	// メタル
	if (m_pPlayer->IsMetal())
	{
		// 武器選択中の表示
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

	// ファイア
	if (m_pPlayer->IsFire())
	{
		// 武器選択中の表示
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

	// 2号
	if (m_pPlayer->IsLineMove())
	{
		// 武器選択中の表示
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
/// 武器切り替え画面表示
/// </summary>
void SceneMain::DrawShotChange()
{
	// 現在のHPを表示
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffffff, m_pFont->GetFont(), "P :");
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
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY, 0xffffff, m_pFont->GetFont(), "M :");
	for (int i = 0; i < m_pPlayer->GetMetalEnergy(); i++) // 現在のエネルギー分だけ四角を描画する
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY + kPauseShotNumHeight,
			0xc0c0c0, true);
	}

	// ファイアー
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 2, 0xffffff, m_pFont->GetFont(), "F :");
	for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++) // 現在のエネルギー分だけ四角を描画する
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY * 2,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY * 2 + kPauseShotNumHeight,
			0xff4500, true);
	}

	// アイテム2号
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 3, 0xffffff, m_pFont->GetFont(), "L :");
	for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++) // 現在のエネルギー分だけ四角を描画する
	{
		DrawBox(kBarPosX + kBarInterval * i,
			kBarPosY + kIntervalY * 3,
			(kBarPosX + kBarInterval * i) + kPauseShotNumWidth,
			kBarPosY + kIntervalY * 3 + kPauseShotNumHeight,
			0xb22222, true);
	}

	// 現在のE缶数を表示
	DrawStringToHandle(kTextPosX, kTextPosY + kIntervalY * 4, "E : ", 0xffffff, m_pFont->GetFont());
	DrawFormatStringToHandle(kTextPosX, kBarPosY + kIntervalY * 4, 0xffffff, m_pFont->GetFont(), "%d", m_pPlayer->GetFullHpRecovery());
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
	DrawGraph(m_startDis.x, Game::kScreenHeight * 0.5f - 220, m_startHandle, true);

	DrawStringToHandle(static_cast<int>(m_startDis.x + Game::kScreenWidth * 0.5 - 170), Game::kScreenHeight * 0.5 - 100,
		"敵をすべてたおせ！\n", 0xffffff, m_pFont->GetFontStaging());

	DrawFormatStringToHandle(static_cast<int>(m_startDis.x + Game::kScreenWidth * 0.5 - 60), Game::kScreenHeight * 0.5 + 30,
		0xffffff, m_pFont->GetFontStaging(), "%d / %d\n", m_enemyTotalNum, m_enemyTotalNum);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/// <summary>
/// クリア演出の描画
/// </summary>
void SceneMain::DrawClearStaging()
{
	// タイム
	int milliSec = m_time * 1000 / 60;
	int sec = (milliSec / 1000) % 60;
	int min = (milliSec / 1000) / 60;
	milliSec %= 1000;

	// クリアの文字を表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_stagingFade);
	DrawGraph(0, Game::kScreenHeight * 0.5f - 200, m_startHandle, true);

	DrawStringToHandle(Game::kScreenWidth * 0.5 - 70, Game::kScreenHeight * 0.5 - 100,
		"CLEAR!\n", 0xffe44d, m_pFont->GetFontStaging());

	DrawFormatStringToHandle(Game::kScreenWidth * 0.5 - 260, Game::kScreenHeight * 0.5 + 30,
		0xffffff, m_pFont->GetFontStaging(), "クリアタイム : % 3d:%02d.%03d", min, sec, milliSec);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
