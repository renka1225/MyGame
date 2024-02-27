﻿#include "SceneTutorial.h"
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
	// 画面内に1度に出せる弾数
	constexpr int kShotMax = 3;
	// 画面内に1度に出せる回復アイテム数
	constexpr int kRecoveryMax = 5;

	// 登場する敵数
	constexpr int kEnemyMax = 3;

	// プレイヤーの初期位置
	constexpr float kPlayerInitPosX = 350.0f;
	constexpr float kPlayerInitPosY = 430.0f;

	// プレイヤーの画像サイズ
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 64;

	// マップチップのサイズ
	constexpr int kMapChipWidth = 32;
	constexpr int kMapChipHeight = 32;

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

SceneTutorial::SceneTutorial()
{
	// ゲーム画面描画先の生成
	m_gameScreenHandle = MakeScreen(static_cast<int>(Tutorial::kMapWidth), static_cast<int>(Tutorial::kMapHeight), true);

	// プレイヤーのメモリ確保
	m_pPlayer = new Player;

	// 背景のメモリ確保
	m_pBg = new BgTutorial;
	m_pBg->SetPlayer(m_pPlayer);

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
	m_fireworksSE = LoadSoundMem("data/sound/SE/fireworks.wav");

	// 画像
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

SceneTutorial::~SceneTutorial()
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
	DeleteSoundMem(m_fireworksSE);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_shotSelectHandle);
	DeleteGraph(m_startHandle);
	DeleteGraph(m_fireworks1);
	DeleteGraph(m_fireworks2);
	DeleteGraph(m_fireworks3);
}

/// <summary>
/// 初期化
/// </summary>
void SceneTutorial::Init()
{
	// リトライ時はスタート演出を行わない
	if (!(m_isSceneEnd || m_isRetry || m_isSceneTitle))
	{
		// 演出時間の初期化
		m_startStagingTime = kStartTime;
		m_startDis = { 30, 0 };
		m_fadeAlpha = 240;
		m_stagingFade = 0;
		// スタートSE
		PlaySoundMem(m_startSE, DX_PLAYTYPE_BACK, true);
	}
	// HPが0以下になった場合は行わない
	if (!m_isRetry)
	{
		// 敵の初期化
		CreateEnemy();
		m_enemyTotalNum = kEnemyMax;
		m_time = 0.0f;

		m_isGetFullHpRecovery = false;
	}
	// 演出時間の初期化
	m_clearStagingTime = kClearTime;
	m_gameoverStagingTime = kGameoverTime;
	m_fireworks1Frame = 0;
	m_fireworks2Frame = 0;
	m_fireworks3Frame = 0;
	m_shakeFrame = 0;
	m_readyCount = kReadyCount;
	m_ampFrame = 0;

	// ポーズ画面の初期化
	m_pPause->Init();

	// プレイヤーの初期化
	assert(m_pPlayer);
	m_pPlayer->Init(m_pBg, this, { kPlayerInitPosX, kPlayerInitPosY });

	// 背景の初期化
	m_pBg->Init();

	// 回復アイテムの初期化
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

	// 画面遷移の初期化
	m_isSceneGameOver = false;
	m_isSceneClear = false;
	m_isSceneTitle = false;
	m_isSceneEnd = false;
	m_isRetry = false;

	// 花火の初期位置
	m_fireworks1Pos = { 900.0f, static_cast<float>(Game::kScreenHeight) + 50.0f };
	m_fireworks2Pos = { 300.0f, static_cast<float>(Game::kScreenHeight) + 200.0f };
	m_fireworks3Pos = { 1400.0f, static_cast<float>(Game::kScreenHeight) + 250.0f };
	m_fireworks4Pos = { 500.0f, static_cast<float>(Game::kScreenHeight) + 300.0f };
	m_fireworks5Pos = { 700.0f, static_cast<float>(Game::kScreenHeight) + 350.0f };
	m_fireworks6Pos = { 1100.0f, static_cast<float>(Game::kScreenHeight) + 400.0f };
}

/// <summary>
/// 更新
/// </summary>
void SceneTutorial::Update()
{
	/*スタート演出*/
	if (m_startStagingTime > 0.0f)
	{
		m_startStagingTime--;	// スタート演出の時間

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
			// 0.5秒間待機
			WaitTimer(500);
		}
		else
		{
			m_startDis.x -= 40.0f;
			m_stagingFade -= 40;
		}
		return;
	}

	/*フェードインアウト*/
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

	/*カウントダウン演出*/
	m_readyCount--;
	if (m_readyCount >= 0) return;
	else m_readyCount = 0;

	/*スタートSEを鳴らした後にBGMを鳴らす*/
	if (CheckSoundMem(m_startSE) == 0 && CheckSoundMem(m_bgm) == 0)
	{
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
	}

	/*敵をすべて倒したらクリア演出を行う*/
	if (m_enemyTotalNum <= 0)
	{
		UpdateClearStaging();
	}
	if (m_clearStagingTime <= 0.0f)
	{
		// 0.5秒後にクリア画面に遷移
		m_isSceneClear = true;
		WaitTimer(500);
		return;
	}

	/*ポーズ画面の更新*/
	m_pPause->Update();

	/*ポーズ画面が表示されている場合画面を止める*/
	if (m_pPause->IsPause())
	{
		// BGM一時停止
		m_isExistMenu = true;

		// リトライが選択されたら初期化する
		if (m_pPause->IsSelectRetry())
		{
			m_pPlayer->Init(m_pBg, this, { kPlayerInitPosX, kPlayerInitPosY });
			m_isSceneEnd = true;
		}
		// タイトルに戻るを選択
		else if (m_pPause->IsSelectTitle())
		{
			// タイトル画面に遷移
			m_isSceneTitle = true;
			StopSoundMem(m_bgm);

			// 1秒後に遷移
			WaitTimer(1000);
		}
		return;
	}

	/*武器切り替え画面が表示されている場合画面を止める*/
	if (m_pPause->IsSelectShotExist())
	{
		m_isExistMenu = true;
		return;
	}

	/*タイムカウント*/
	if (m_enemyTotalNum > 0)
	{
		m_time++;
	}

	/*背景の更新*/
	m_pBg->Update();

	/*プレイヤーのHPが0になった場合*/
	if (m_pPlayer->GetHp() <= 0)
	{
		// プレイヤーの残機が0以下の場合
		if (m_pPlayer->GetLife() <= 0)
		{
			// 1秒後にゲームオーバー画面に遷移
			WaitTimer(1000);
			m_isSceneGameOver = true;
			StopSoundMem(m_bgm);
			return;
		}
		else
		{
			// 死亡アニメーション後リトライ
			if (m_pPlayer->GetDeadFrame() <= 0)
			{
				m_isRetry = true;
				Init();
			}
		}
	}

	/*プレイヤーの更新*/
	if (m_enemyTotalNum > 0)
	{
		m_pPlayer->Update();
	}
	/*プレイヤーの現在地を取得*/
	m_playerPos = m_pPlayer->GetPos();
	/*プレイヤーの当たり判定を取得*/
	Rect playerRect = m_pPlayer->GetColRect();

	// E缶を表示
	if (!m_isGetFullHpRecovery)
	{
		DropFullHpRecovery();
	}

	/*弾の更新*/
	UpdateShot(playerRect);
	/*敵の更新*/
	UpdateEnemy(playerRect);
	/*回復アイテムの更新*/
	UpdateRecovery(playerRect);

	/*画面を揺らす*/
	m_shakeFrame--;
	m_ampFrame *= 0.95f;
	if (m_shakeFrame < 0)
	{
		m_shakeFrame = 0;
	}

	/*メニューを閉じる際にジャンプしないようにする*/
	if (!m_pPause->IsSelectShotExist() || !m_pPause->IsPause())
	{
		m_isExistMenu = false;
	}

#ifdef _DEBUG
	// MEMO:ESCAPEキーor左スティック押し込みでクリア画面に移動
	// パッドの入力状態を取得
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Pad::IsTrigger(pad & PAD_INPUT_START))
	{
		m_enemyTotalNum = 0;
	}
#endif
}

/// <summary>
/// 描画
/// </summary>
void SceneTutorial::Draw()
{
	// 書き込み
	SetDrawScreen(m_gameScreenHandle);
	// 描画先スクリーンをクリアする
	ClearDrawScreen();

	// 背景の描画
	m_pBg->Draw();

	// 弾の描画
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pShot[i])continue;
		m_pShot[i]->Draw();
	}

	// 敵の描画
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pEnemy[i])continue;
		m_pEnemy[i]->Draw();
	}

	// 回復アイテムの描画
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pRecovery[i])continue;
		m_pRecovery[i]->Draw();
	}

	// プレイヤーの描画
	m_pPlayer->Draw();

	/*画面横に情報表示*/
	DrawInfo();

	/*ポーズ画面、武器切り替え画面の表示*/
	m_pPause->Draw();

	/*武器切り替え画面表示中*/
	if (m_pPause->IsSelectShotExist())
	{
		DrawShotChange();
	}
	/*ポーズ画面表示中*/
	if (m_pPause->IsPause())
	{
		DrawPause();
	}

	// フェードインアウト
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x0e0918, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// バックバッファに書き込む設定に戻しておく
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲーム画面をバックバッファに描画する
	int screenX = 0;
	int screenY = 0;
	if (m_shakeFrame > 0)
	{
		// 画面揺れ
		screenX = GetRand(4) - 2 * static_cast<int>(m_ampFrame);
		screenY = GetRand(4) - 2 * static_cast<int>(m_ampFrame);
	}
	DrawRectGraph(screenX, screenY, 0, 0, Game::kScreenWidth, Game::kScreenHeight, m_gameScreenHandle, true);

	// スタートとクリア条件の表示
	if (m_startStagingTime > 0.0f)
	{
		DrawStartStaging();
	}
	else if (m_startStagingTime <= 0.0f)
	{
		if (m_readyCount % 10 >= 8) return;

		if (m_readyCount > 0)
		{
			DrawStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5 - 30), static_cast<int>(Game::kScreenHeight * 0.5), "READY", 0xffffff, m_pFont->GetFontStaging());
		}
	}

	// クリアの演出とタイム表示
	if (m_enemyTotalNum <= 0 && m_clearStagingTime >= 0.0f)
	{
		DrawClearStaging();
	}
}

/// <summary>
/// 弾の更新
/// </summary>
void SceneTutorial::UpdateShot(Rect playerRect)
{
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pShot[i]) continue;

		m_pShot[i]->SetBg(m_pBg);
		m_pShot[i]->SetMain(this);
		m_pShot[i]->Update();

		// アイテム2号の場合
		if (m_pShot[i]->GetShotType() == ShotType::kShotLineMove)
		{
			// 画面上に存在するか
			if (m_pShot[i]->IsExist())
			{
				m_isExistLineMove = true;

				// アイテム2号のSEを鳴らす
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

			// 弾の当たり判定
			Rect shotRect = m_pShot[i]->GetColRect();
			// プレイヤーと弾の当たり判定
			if (playerRect.IsCollision(shotRect))
			{
				m_pPlayer->RideLineMove(shotRect);
			}
		}

		// 画面外に出たらメモリを解放する
		if (!m_pShot[i]->IsExist())
		{
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}
}

/// <summary>
/// 敵の更新
/// </summary>
/// <param name="playerRect">プレイヤーの当たり判定</param>
void SceneTutorial::UpdateEnemy(Rect playerRect)
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i]) continue;
		m_pEnemy[i]->Update();

		// 使用済みの敵キャラクターを削除
		if (!m_pEnemy[i]->IsExist())
		{
			// 消滅時SEを鳴らす
			PlaySoundMem(m_enemyDeadSE, DX_PLAYTYPE_BACK, true);

			// 敵の合計数を減らす
			m_enemyTotalNum--;

			// 確率でアイテムをドロップ
			CreateItem(i);

			// メモリを解放する
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;	// nullptrを入れる
		}
		else
		{
			// 敵とプレイヤーの当たり判定
			Rect enemyRect = m_pEnemy[i]->GetColRect();
			if (playerRect.IsCollision(enemyRect))
			{
				m_pPlayer->OnDamage();
				m_shakeFrame = 2;
				m_ampFrame = 5;
			}

			for (int j = 0; j < m_pShot.size(); j++)
			{
				// nullptrなら処理は行わない
				if (!m_pShot[j]) continue;

				// 敵と弾の当たり判定
				// アイテム２号の場合は敵との当たり判定を無視する
				if (m_pShot[j]->GetShotType() != ShotType::kShotLineMove)
				{
					Rect shotRect = m_pShot[j]->GetColRect(); // 弾の当たり判定
					if (shotRect.IsCollision(enemyRect))
					{
						m_pEnemy[i]->OnDamage();
					}
					if (enemyRect.IsCollision(shotRect))
					{
						// 弾を削除
						delete m_pShot[j];
						m_pShot[j] = nullptr;
					}
				}
			}
		}
	}
}

/// <summary>
/// 回復アイテムの更新
/// </summary>
/// <param name="playerRect">プレイヤーの当たり判定</param>
void SceneTutorial::UpdateRecovery(Rect playerRect)
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
/// 弾の生成
/// </summary>
/// <param name="pShot">弾の種類</param>
/// <returns></returns>
bool SceneTutorial::AddShot(ShotBase* pShot)
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
/// クリア演出の更新
/// </summary>
void SceneTutorial::UpdateClearStaging()
{
	m_clearStagingTime--;
	m_stagingFade += 150;

	// クリアSE1回だけを鳴らす
	StopSoundMem(m_bgm);
	if (CheckSoundMem(m_clearSE) == 0 && m_clearStagingTime >= kClearTime - 60.0f)
	{
		m_stagingFade = 0;
		PlaySoundMem(m_clearSE, DX_PLAYTYPE_BACK, true);
		return;
	}
	// 花火の更新
	else if (m_clearStagingTime <= kClearTime - 30.0f && m_clearStagingTime > 0.0f)
	{
		// 花火を上にあげる
		if (m_clearStagingTime <= 220.0f)
		{
			m_fireworks1Pos.y -= kFireworksSpeed;
		}
		if (m_clearStagingTime <= 210.0f)
		{
			m_fireworks1Frame += kFireworksWidth;
			m_fireworks2Pos.y -= kFireworksSpeed;
		}
		if (m_clearStagingTime <= 180.0f)
		{
			m_fireworks2Frame += kFireworksWidth;
			m_fireworks3Pos.y -= kFireworksSpeed;
		}
		if (m_clearStagingTime <= 150.0f)
		{
			m_fireworks3Frame += kFireworksWidth;
			m_fireworks4Pos.y -= kFireworksSpeed;
		}
		if (m_clearStagingTime <= 120.0f)
		{
			m_fireworks4Frame += kFireworksWidth;
			m_fireworks5Pos.y -= kFireworksSpeed;
		}
		if (m_clearStagingTime <= 100.0f)
		{
			m_fireworks5Frame += kFireworksWidth;
			m_fireworks6Pos.y -= kFireworksSpeed;
		}
		if (m_clearStagingTime <= 80.0f)
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
/// アイテム生成
/// </summary>
/// <param name="enemyIndex">敵</param>
// HP小回復
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
// HP大回復
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
// 弾小回復
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
// 弾大回復
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
// 残機回復
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
// HP全回復
void SceneTutorial::DropFullHpRecovery()
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryFullHp;
			m_pRecovery[i]->Init(m_pBg);
			m_pRecovery[i]->Start({ 4200, 750 }); // アイテムの位置を設定
			return;
		}
	}
}

/// <summary>
/// 敵の生成
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
			m_pEnemy[i]->Start(3300.0f, 400.0f, 80.0f);
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
/// 回復アイテムドロップ
/// </summary>
/// <param name="enemyIndex">敵</param>
void SceneTutorial::CreateItem(int enemyIndex)
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
/// 弾数、敵数表示
/// </summary>
void SceneTutorial::DrawInfo()
{
	// 画面横の表示
	DrawBox(0, 0, kFrameSize, Game::kScreenHeight, 0x483d8b, true); // 左側
	DrawLine(kFrameSize + 1, 0, kFrameSize + 1, Game::kScreenHeight, 0xffffff , 2);
	DrawBox(Game::kScreenWidth - kFrameSize, 0, Game::kScreenWidth, Game::kScreenHeight, 0x483d8b, true); // 右側
	DrawLine(Game::kScreenWidth - kFrameSize - 1, 0, Game::kScreenWidth - kFrameSize - 1, Game::kScreenHeight, 0xffffff, 2);

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
	// Energyの表示
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY - 120, "Energy", 0xffffff, m_pFont->GetFont3());

	// HP
	if (m_pPlayer->IsBuster())
	{
		// 武器選択中の表示
		DrawGraph(Game::kScreenWidth - kFrameSize + 3, kShotNumDisPosY - 10, m_shotSelectHandle, true);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY - 40, "HP :", 0xffffff, m_pFont->GetFont2()); // 文字
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
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY - 40, "M :", 0xffffff, m_pFont->GetFont2()); // 文字
	DrawGraph(kShotNumDisPosX + 40, kShotNumDisPosY + kShotNumIntervalY - 45, m_metalHandle, true); // メタルの画像
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
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY * 2 - 40, "F :", 0xffffff, m_pFont->GetFont2()); // 文字
	DrawGraph(kShotNumDisPosX + 40, kShotNumDisPosY + kShotNumIntervalY * 2 - 40, m_fireHandle, true); // ファイアの画像
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
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY * 3 - 40, "L :", 0xffffff, m_pFont->GetFont2()); // 文字
	DrawGraph(kShotNumDisPosX + 40, kShotNumDisPosY + kShotNumIntervalY * 3 - 40, m_lineMoveHandle, true); // 2号の画像
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
void SceneTutorial::DrawShotChange()
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
void SceneTutorial::DrawPause()
{
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY, 0xffffff, m_pFont->GetFont(), "ゲームに戻る");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 2, 0xffffff, m_pFont->GetFont(), "リトライ");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 3, 0xffffff, m_pFont->GetFont(), "タイトルに戻る");
}

/// <summary>
/// スタート演出の描画
/// </summary>
void SceneTutorial::DrawStartStaging()
{
	// フェードイン→アウト
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_stagingFade);
	DrawGraph(static_cast<int>(m_startDis.x), static_cast<int>(Game::kScreenHeight * 0.5 - 220), m_startHandle, true);

	DrawStringToHandle(static_cast<int>(m_startDis.x + Game::kScreenWidth * 0.5 - 190), static_cast<int>(Game::kScreenHeight * 0.5 - 100),
		"敵をすべてたおせ！\n", 0xffffff, m_pFont->GetFontStaging());

	DrawFormatStringToHandle(static_cast<int>(m_startDis.x + Game::kScreenWidth * 0.5 - 60), static_cast<int>(Game::kScreenHeight * 0.5 + 30),
		0xffffff, m_pFont->GetFontStaging(), "%d / %d\n", m_enemyTotalNum, m_enemyTotalNum);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/// <summary>
/// クリア演出の描画
/// </summary>
void SceneTutorial::DrawClearStaging()
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
		DrawRectRotaGraph(static_cast<int>(m_fireworks1Pos.x), static_cast<int>(m_fireworks1Pos.y), m_fireworks1Frame, 0, kFireworksWidth, kFireworksHeight, 6.0f, 0.0f, m_fireworks1, true);
	}
	if (m_clearStagingTime <= 190.0f && m_clearStagingTime > 50.0f)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks2Pos.x), static_cast<int>(m_fireworks2Pos.y), m_fireworks2Frame, 0, kFireworksWidth, kFireworksHeight, 5.0f, 0.0f, m_fireworks2, true);
	}
	if (m_clearStagingTime <= 160.0f && m_clearStagingTime > 30.0f)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks3Pos.x), static_cast<int>(m_fireworks3Pos.y), m_fireworks3Frame, 0, kFireworksWidth, kFireworksHeight, 5.0f, 0.0f, m_fireworks3, true);
	}
	if (m_clearStagingTime <= 140.0f && m_clearStagingTime > 10.0f)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks4Pos.x), static_cast<int>(m_fireworks4Pos.y), m_fireworks4Frame, 0, kFireworksWidth, kFireworksHeight, 4.8f, 0.0f, m_fireworks2, true);
	}
	if (m_clearStagingTime <= 120.0f && m_clearStagingTime > 5.0f)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks5Pos.x), static_cast<int>(m_fireworks5Pos.y), m_fireworks5Frame, 0, kFireworksWidth, kFireworksHeight, 5.2f, 0.0f, m_fireworks3, true);
	}
	if (m_clearStagingTime <= 90.0f && m_clearStagingTime > 0.0f)
	{
		DrawRectRotaGraph(static_cast<int>(m_fireworks6Pos.x), static_cast<int>(m_fireworks6Pos.y), m_fireworks6Frame, 0, kFireworksWidth, kFireworksHeight, 6.0f, 0.0f, m_fireworks1, true);
	}
}