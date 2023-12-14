#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "Bg.h"

#include "RecoveryBase.h"
#include "RecoverySmallHp.h"
#include "RecoveryGreatHp.h"
#include "RecoveryFullHp.h"
#include "RecoverySmallShot.h"
#include "RecoveryGreatShot.h"
#include "RecoveryLife.h"

#include "Player.h"

#include "ShotBase.h"

#include "Matasaburo.h"
#include <cassert>

namespace
{
	// 画面内に1度に出せる弾数
	constexpr int kShotMax = 3;
	// 1度に登場できる敵数
	constexpr int kEnemyMax = 5;
	// 画面内に1度に出せる回復アイテム数
	constexpr int kRecoveryMax = 20;
}

SceneMain::SceneMain():
	m_isSceneEnd(false)
{
	// プレイヤーのグラフィックロード
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);
	m_bgHandle = LoadGraph("data/image/backGround.png");
	assert(m_bgHandle != -1);
	m_mapHandle = LoadGraph("data/image/map.png");
	assert(m_mapHandle != -1);
	m_enemyHandle = LoadGraph("data/image/Enemy/matasaburo.png");
	assert(m_bgHandle != -1);

	// 背景のメモリ確保
	m_pBg = new Bg;
	m_pBg->SetHandle(m_bgHandle);
	m_pBg->SetMapHandle(m_mapHandle);

	// プレイヤーのメモリ確保
	m_pPlayer = new Player{ this, m_pBg };
	m_pPlayer->SetHandle(m_playerHandle);	// Playerにグラフィックのハンドルを渡す

	// ショットの初期化
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr; // 未使用状態にする
	}

	// 敵の初期化
	m_pEnemy.resize(kEnemyMax);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = nullptr; // 未使用状態にする
	}

	// 回復アイテムの初期化
	m_pRecovery.resize(kRecoveryMax);
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		m_pRecovery[i] = nullptr; // 未使用状態にする
	}
}

SceneMain::~SceneMain()
{
	// メモリからグラフィックを削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_enemyHandle);

	// 背景のメモリ解放
	delete m_pBg;
	m_pBg = nullptr;

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
}

void SceneMain::Init()
{
	// 画面遷移の初期化
	m_isSceneEnd = false;

	// 背景の初期化
	m_pBg->Init();

	// プレイヤーの初期化
	assert(m_pPlayer);	// m_pPlayer == nullptrの場合止まる
	m_pPlayer->Init();
	

	// 敵の初期化
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			m_pEnemy[i]->Init();
		}
	}

	// 回復アイテムの初期化
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (m_pRecovery[i])
		{
			m_pRecovery[i]->Init();
		}
	}
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	// プレイヤーの残機が0未満の場合
	if (m_pPlayer->GetLife() < 0)
	{
		m_isSceneEnd = true; // ゲームオーバー画面に遷移
	}

	// 背景の更新
	m_pBg->Update();

	// プレイヤーの更新
	m_pPlayer->Update();

	Rect playerRect = m_pPlayer->GetColRect();	// プレイヤーの当たり判定
	Vec2 playerPos = m_pPlayer->GetPos();		// プレイヤーの現在地を取得

	// プレイヤーが画面中央に移動したら敵を登場させる
	if (playerPos.x == Game::kScreenWidth / 2)
	{
		CreateMatasaburo();
	}

	// 弾の更新
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pShot[i]) continue;

		m_pShot[i]->Update();

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
		// nullptrなら処理は行わない
		if (!m_pEnemy[i]) continue;
		m_pEnemy[i]->Update();

		// 使用済みの敵キャラクターを削除
		if (!m_pEnemy[i]->IsExist())
		{
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

	// 回復アイテムの更新
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pRecovery[i]) continue;

		m_pRecovery[i]->Update();

		// 画面外に出たらメモリを解放する
		if (!m_pRecovery[i]->IsExist())
		{
			delete m_pRecovery[i];
			m_pRecovery[i] = nullptr;
		}
	}
}

void SceneMain::Draw()
{
	// 描画先スクリーンをクリアする
	ClearDrawScreen();

	// 背景の描画
	m_pBg->Draw();

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

	// 現在のHPを表示
	DrawFormatString(8, 8, 0xffffff, "HP:%.2f", m_pPlayer->GetHp());
	// 現在の残機数を表示
	DrawFormatString(8, 28, 0xffffff, "残機数:%d", m_pPlayer->GetLife());
	// 現在の弾エネルギー数を表示
	DrawFormatString(8, 48, 0xffffff, "メタル: %.2f", m_pPlayer->GetMetalEnergy());
	DrawFormatString(8, 68, 0xffffff, "ファイヤー: %.2f", m_pPlayer->GetFireEnergy());
	DrawFormatString(8, 88, 0xffffff, "アイテム2号: %.2f", m_pPlayer->GetLineEnergy());

}

// 弾の生成
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

bool SceneMain::AddItem(RecoveryBase* pRecovery)
{
	// nullptrを渡されたら止まる
	assert(pRecovery);

	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// 使用中なら次のチェックを行う
		if (m_pRecovery[i]) continue;

		// m_pRecovery[i] == nullptrなので新しく登録する
		m_pRecovery[i] = pRecovery;
		// 登録したら終了
		return true;
	}
}

// 敵の生成
void SceneMain::CreateMatasaburo()
{
	//使われていない場所にアドレスを保存する
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	// nullptrであることをチェックする
		{
			m_pEnemy[i] = new Matasaburo;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	// 1体分メモリを確保できたらその時点で終了
		}
	}
}
