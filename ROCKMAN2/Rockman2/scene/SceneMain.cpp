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

	/*ポーズ画面*/
	// ポーズ画面の文字表示位置
	constexpr int kTextPosX = 840;
	constexpr int kTextPosY = 400;
	// 弾数表示位置
	constexpr int kBarPosX = 840;
	constexpr int kBarPosY = 430;
	// 弾数表示間隔
	constexpr int kBarInterval = 10;
	// 弾数表示サイズ
	constexpr int kPauseShotNumWidth = 18;
	constexpr int kPauseShotNumHeight = 20;
	// 弾数表示間隔
	constexpr int kIntervalY = 70;

	/*ゲーム内*/
	// 黒枠のサイズ
	constexpr int kFrameSize = 270;
	// 残機、敵数表示位置
	constexpr int kInfoTextPosX = 30;	// 横
	constexpr int kInfoTextPosY = 300;	// 縦
	// 弾数表示位置
	constexpr int kShotNumDisPosX = Game::kScreenWidth - kFrameSize + 10;	// 横
	constexpr int kShotNumDisPosY = 300;									// 縦
	// 弾数表示間隔
	constexpr int kShotNumIntervalX = 25;	// 横
	constexpr int kShotNumIntervalY = 100;	// 縦
	// 弾数表示サイズ
	constexpr int kShotDisWidth = 18;	// 横
	constexpr int kShotDisHeight = 20;	// 縦
}

SceneMain::SceneMain():
	m_drawValue(0),
	m_isGetFullHpRecovery(false),
	m_enemyTotalNum(kEnemyMax),
	m_isExistLineMove(false),
	m_isSceneGameOver(false),
	m_isSceneClear(false),
	m_isSceneEnd(false),
	m_fadeAlpha(255),
	m_startDisplayX(0.0f)
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

	// 操作説明の画像
	m_exHandle = LoadGraph("data/image/UI/ex.png");
}

SceneMain::~SceneMain()
{
	// 背景のメモリ解放
	delete m_pBg;
	m_pBg = nullptr;

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
	DeleteGraph(m_exHandle);
}

void SceneMain::Init()
{
	// 画面遷移の初期化
	m_isSceneGameOver = false;
	m_isSceneClear = false;
	m_isSceneTitle = false;
	m_isSceneEnd = false;
	m_isExistLineMove = false;

	m_enemyTotalNum = kEnemyMax;

	// TODO:スタート時の演出
	StartStaging();

	// ポーズ画面の初期化
	m_pPause->Init();

	// プレイヤーの初期化
	assert(m_pPlayer);	// m_pPlayer == nullptrの場合止まる
	m_pPlayer->Init();

	// 背景の初期化
	m_pBg->Init();

	// 敵の初期化
	CreateEnemy();

	// 回復アイテムの初期化
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (m_pRecovery[i])
		{
			m_pRecovery[i]->Init(m_pBg);
		}
	}
	m_isGetFullHpRecovery = false;

	// BGMを鳴らす
	// TODO: BGM変更予定
	//PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	// プレイヤーの残機が0未満の場合
	if (m_pPlayer->GetLife() < 0)
	{
		// 1秒間待機
		WaitTimer(1000);

		m_isSceneGameOver = true; // ゲームオーバー画面に遷移
		StopSoundMem(m_bgm);
	}

	// 敵をすべて倒したらクリア画面に遷移
	if (m_enemyTotalNum <= 0)
	{
		m_isSceneClear = true;
		StopSoundMem(m_bgm);

		// 1秒後に遷移
		WaitTimer(1000);
	}

	// パッドの入力状態を取得
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ポーズ画面の更新
	m_pPause->Update();

	// 武器切り替え画面が表示されている場合画面を止める
	if (m_pPause->IsSelectShotExist())
	{
		return;
	}

	// ポーズ画面が表示されている場合画面を止める
	if (m_pPause->IsPause())
	{
		// リトライが選択されたら初期化する
		if (m_pPause->IsSelectRetry())
		{
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

	// 背景の更新
	m_pBg->Update();

	// プレイヤーの更新
	m_pPlayer->Update();

	// プレイヤーの現在地を取得
	m_playerPos = m_pPlayer->GetPos();
	// プレイヤーの当たり判定
	Rect playerRect = m_pPlayer->GetColRect();

	// E缶を表示
	if (!m_isGetFullHpRecovery)
	{
		DropFullHpRecovery();
	}

	// 弾の更新
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pShot[i]) continue;

		m_pShot[i]->SetBg(m_pBg);
		m_pShot[i]->Update();

		// アイテム2号の場合
		if (m_pShot[i]->GetShotType() == ShotType::kShotLineMove)
		{
			// 画面上に存在するか
			if (m_pShot[i]->IsExist())
			{
				m_isExistLineMove = true;
			}
			else
			{
				m_isExistLineMove = false;
			}

			// 弾の当たり判定
			Rect shotRect = m_pShot[i]->GetColRect();
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

	// 敵の更新
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

	// 回復アイテムの更新
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pRecovery[i]) continue;

		//m_pRecovery[i]->SetBg(m_pBg);
		m_pRecovery[i]->Update();

		Rect recoveryRect = m_pRecovery[i]->GetColRect();	// 回復アイテムの当たり判定
		// プレイヤーと回復アイテムの当たり判定
		if (playerRect.IsCollision(recoveryRect))
		{
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
	}

#ifdef _DEBUG
	// Cキーでクリア画面に移動するようにする
	if (Pad::IsTrigger(pad & PAD_INPUT_3))
	{
		m_isSceneClear = true; // クリア画面に遷移
		StopSoundMem(m_bgm);
	}
#endif

}

void SceneMain::Draw()
{
	// 描画先スクリーンをクリアする
	ClearDrawScreen();

	// TODO:スタート時の描画
	//// 四角を描画
	//DrawBox(m_startDisplayX, Game::kScreenHeight * 0.5 - 10, 
	//	m_startDisplayX + 400, Game::kScreenHeight * 0.5 + 10,
	//	0xffffff, true);

	//// 文字描画
	//DrawFormatString(
	//	m_startDisplayX, Game::kScreenHeight * 0.5 - 10,
	//	0x000000, "敵を%d体倒せ！", m_enemyTotalNum);

	// 背景の描画
	m_pBg->Draw();

	// TODO:操作説明の表示
	DrawEx();

	// プレイヤーの描画
	m_pPlayer->Draw();

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

	/*画面横に情報表示*/
	DrawInfo();

	// ポーズ画面、武器切り替え画面の表示
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

}

/*弾の生成*/
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

/*アイテムドロップ*/
void SceneMain::DropHpSmallRecovery(int enemyIndex) // HP小回復
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoverySmallHp;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init(m_pBg);
			return;
		}
	}
}

void SceneMain::DropHpGreatRecovery(int enemyIndex) // HP大回復
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryGreatHp;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init(m_pBg);
			return;
		}
	}
}

void SceneMain::DropShotSmallRecovery(int enemyIndex) // 弾小回復
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoverySmallShot;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init(m_pBg);
			return;
		}
	}
}

void SceneMain::DropShotGreatRecovery(int enemyIndex) // 弾大回復
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryLife;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init(m_pBg);
			return;
		}
	}
}

void SceneMain::DropLifeRecovery(int enemyIndex) // 残機回復
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryGreatShot;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init(m_pBg);
			return;
		}
	}
}

void SceneMain::DropFullHpRecovery() // HP全回復
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryFullHp;
			m_pRecovery[i]->Start({ 900, 500 }); // アイテムの位置を設定
			m_pRecovery[i]->Init(m_pBg);
			return;
		}
	}
}

/*スタート演出*/
void SceneMain::StartStaging()
{
	// TODO:スタートとクリア条件の表示
	//m_startDisplayX = Game::kScreenWidth;
	//m_startDisplayX -= 10.0f;

	WaitTimer(1000); // 1秒間待機
}

/*敵の生成*/
void SceneMain::CreateEnemy()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		switch (i)
		{
		case 0:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(300.0f, 600.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 1:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(500.0f, 650.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 2:
			m_pEnemy[i] = new EnemyCat;
			m_pEnemy[i]->Start(1000.0f, 700.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 3:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(400.0f, 600.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 4:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(2000.0f, 600.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 5:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(800.0f, 200.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 6:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(1500.0f, 400.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 7:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(2400.0f, 100.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 8:
			m_pEnemy[i] = new EnemyBird;
			m_pEnemy[i]->Start(2000.0f, 50.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		case 9:
			m_pEnemy[i] = new EnemyBear;
			m_pEnemy[i]->Start(2600.0f, 650.0f);
			m_pEnemy[i]->Init(m_pBg);
			break;
		default:
			break;
		}
	}
}

/*回復アイテムの生成*/
void SceneMain::CreateItem(int enemyIndex)
{
	int getRandDrop = GetRand(100);
	if (getRandDrop <= 5)
	{
		DropHpSmallRecovery(enemyIndex); // HP回復(小)
	}
	else if (getRandDrop <= 8)
	{
		DropHpGreatRecovery(enemyIndex);	// HP回復(大)
	}
	else if (getRandDrop <= 13)
	{
		DropShotSmallRecovery(enemyIndex); // 弾エネルギー(小)
	}
	else if (getRandDrop <= 16)
	{
		DropShotGreatRecovery(enemyIndex); // 弾エネルギー(大)
	}
	else if (getRandDrop <= 19)
	{
		DropLifeRecovery(enemyIndex);	// 残機
	}
}

/*操作説明の表示*/
void SceneMain::DrawEx()
{
	// 表示位置
	int x = 400;
	int y = 500;

	// スクロール量を反映する
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	DrawGraph(x, y, m_exHandle, true);
}

/*弾数、敵数表示*/
void SceneMain::DrawInfo()
{
	// 画面横に四角を表示
	DrawBox(0, 0, kFrameSize, Game::kScreenHeight, 0x483d8b, true); // 左側
	DrawBox(Game::kScreenWidth - kFrameSize, 0, Game::kScreenWidth, Game::kScreenHeight, 0x483d8b, true); // 右側
	
	/*残機、E缶数、残り敵数を左側に表示*/
	// E缶数表示
	DrawFormatStringToHandle(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY, 0xffffff, m_pFont->GetFont(), "E : %d", m_pPlayer->GetFullHpRecovery());
	// 残機数表示
	DrawFormatStringToHandle(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY * 2, 0xffffff, m_pFont->GetFont(), "残機数:%d", m_pPlayer->GetLife());
	// 敵数表示
	DrawFormatStringToHandle(kInfoTextPosX, kInfoTextPosY + kShotNumIntervalY * 3, 0xffffff, m_pFont->GetFont(), "残敵数:%d / %d", m_enemyTotalNum, kEnemyMax);

	/*HP、武器の弾数を右側に表示*/
	// TODO:選択中の武器が分かるようにする
	// HP
	if (m_pPlayer->IsBuster())
	{
		// 武器選択中の表示
		DrawBox(Game::kScreenWidth - kFrameSize,
			kShotNumDisPosY - 10,
			Game::kScreenWidth,
			kShotNumDisPosY + 30,
			0xffd700, false);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY - 40, "HP :" ,0xffffff, m_pFont->GetFont());
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
		DrawBox(Game::kScreenWidth - kFrameSize,
			kShotNumDisPosY - 10 + kShotNumIntervalY,
			Game::kScreenWidth,
			kShotNumDisPosY + 30 + kShotNumIntervalY,
			0xffd700, false);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY - 40, "M :", 0xffffff, m_pFont->GetFont());
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
		DrawBox(Game::kScreenWidth - kFrameSize,
			kShotNumDisPosY - 10 + kShotNumIntervalY * 2,
			Game::kScreenWidth,
			kShotNumDisPosY + 30 + kShotNumIntervalY * 2,
			0xffd700, false);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY * 2 - 40,  "F :", 0xffffff, m_pFont->GetFont());
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
		DrawBox(Game::kScreenWidth - kFrameSize,
			kShotNumDisPosY - 10 + kShotNumIntervalY * 3,
			Game::kScreenWidth,
			kShotNumDisPosY + 30 +  kShotNumIntervalY * 3,
			0xffd700, false);
	}
	DrawStringToHandle(kShotNumDisPosX, kShotNumDisPosY + kShotNumIntervalY * 3 - 40, "L :", 0xffffff, m_pFont->GetFont());
	for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++)
	{
		DrawBox(kShotNumDisPosX + kShotNumIntervalX * i,
			kShotNumDisPosY + kShotNumIntervalY * 3,
			(kShotNumDisPosX + kShotNumIntervalX * i) + kShotDisWidth,
			kShotNumDisPosY + kShotNumIntervalY * 3 + kPauseShotNumHeight,
			0xb22222, true);
	}
}

/*武器切り替え画面表示*/
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

/*ポーズ画面表示*/
void SceneMain::DrawPause()
{
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY, 0xffffff, m_pFont->GetFont(), "ゲームに戻る");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 2, 0xffffff, m_pFont->GetFont(), "リトライ");
	DrawFormatStringToHandle(kTextPosX, kTextPosY + kIntervalY * 3, 0xffffff, m_pFont->GetFont(), "タイトルに戻る");
}
