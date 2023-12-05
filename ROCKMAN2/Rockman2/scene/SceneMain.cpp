#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Bg.h"
#include "Player.h"

#include "ShotBase.h"

#include "Matasaburo.h"
#include <cassert>

namespace
{
	// 画面内に1度に出せる弾数
	constexpr int kShotMax = 3;
	// 1度に登場できる敵数
	constexpr int kEnemyMax = 32;
}

SceneMain::SceneMain()
{
	// プレイヤーのグラフィックロード
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);
	m_bgHandle = LoadGraph("data/image/backGround.png");
	assert(m_bgHandle != -1);
	m_enemyHandle = LoadGraph("data/image/Enemy/matasaburo.png");
	assert(m_bgHandle != -1);

	// 背景のメモリ確保
	m_pBg = new Bg;
	m_pBg->SetHandle(m_bgHandle);

	// プレイヤーのメモリ確保
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	// Playerにグラフィックのハンドルを渡す

	// ショットのメモリ確保
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr; // 未使用状態にする
	}

	// 敵のメモリ確保
	m_pEnemy.resize(kEnemyMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pEnemy[i] = nullptr; // 未使用状態にする
	}
}

SceneMain::~SceneMain()
{
	// メモリからグラフィックを削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_enemyHandle);

	// プレイヤーのメモリ解放
	delete m_pPlayer;
	m_pPlayer = nullptr;

	// 背景のメモリ解放
	delete m_pBg;
	m_pBg = nullptr;

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
}

void SceneMain::Init()
{
	// プレイヤーの初期化
	assert(m_pPlayer);	// m_pPlayer == nullptrの場合止まる
	m_pPlayer->Init();

	// 背景の初期化
	m_pBg->Init();
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	// 背景の更新
	m_pBg->Update();

	// プレイヤーの更新
	m_pPlayer->Update();
	Rect playerRect = m_pPlayer->GetColRect(); // プレイヤーの当たり判定

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	// nullptrでない場合
		{
			m_pEnemy[i]->Update();

			Rect enemyRect = m_pEnemy[i]->GetColRect(); // 敵の当たり判定を取得

			// 弾との当たり判定
			for (int j = 0; j < m_pShot.size(); j++)
			{
				if (m_pShot[j])
				{
					Rect shotRect = m_pShot[j]->GetColRect();	// 弾の当たり判定を取得
					if (shotRect.IsCollision(enemyRect))
					{
						m_pEnemy[i]->OnDamage(1);	// 敵のHPを減らす
					}
				}
			}
			// プレイヤーとの当たり判定
			if (playerRect.IsCollision(enemyRect))
			{
				m_pPlayer->OnDamage();
			}

			// 使用済みの敵キャラクターを削除
			if (!m_pEnemy[i]->IsExist())
			{
				// メモリを解放する
				delete m_pEnemy[i];
				m_pEnemy[i] = nullptr;	// nullptrを入れる
			}
		}
	}

	// 弾の更新
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pShot[i]) continue;

		m_pShot[i]->Update();

		Rect enemyRect = m_pEnemy[i]->GetColRect(); // 敵の当たり判定
		Rect shotRect = m_pShot[i]->GetColRect();	// 弾の当たり判定

		// 弾が敵に当たった、または弾が画面外に出たらメモリを解放する
		if (enemyRect.IsCollision(shotRect) || !m_pShot[i]->IsExist())
		{
			// 弾を削除
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}

	// 敵の更新
	CreateMatasaburo();
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

	// nullptrではないかチェック
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			m_pEnemy[i]->Draw();
		}
	}

	// 現在のHPを表示
	DrawFormatString(8, 8, 0xffffff, "HP:%.2f", m_pPlayer->GetHp());
	// 現在の弾エネルギー数を表示
	DrawFormatString(8, 28, 0xffffff, "メタル: %.2f", m_pPlayer->GetMetalEnergy());
	DrawFormatString(8, 48, 0xffffff, "ファイヤー: %.2f", m_pPlayer->GetFireEnergy());
	DrawFormatString(8, 68, 0xffffff, "アイテム2号: %.2f", m_pPlayer->GetLineEnergy());
	// 長押し時間を表示
	DrawFormatString(8, 88, 0xffffff, "長押し時間:%d", m_pPlayer->GetPressTime());
}

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

void SceneMain::CreateMatasaburo()
{
	//使われていない場所にアドレスを保存する
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	// nullptrであることをチェックする
		{
			m_pEnemy[i] = new Matasaburo;
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	// 1体分メモリを確保できたらその時点で終了
		}
	}
}
