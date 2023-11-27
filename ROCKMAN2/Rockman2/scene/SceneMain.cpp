#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Player.h"
#include "ShotBuster.h"
#include <cassert>

namespace
{
	// 画面内に1度に出せる弾数
	constexpr int kShotMax = 3;
}

SceneMain::SceneMain()
{
	// プレイヤーのグラフィックロード
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);


	// プレイヤーのメモリ確保
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	// Playerにグラフィックのハンドルを渡す

	// ショットの準備
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr; // 未使用状態にする

	}
}

SceneMain::~SceneMain()
{
	// メモリからグラフィックを削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_shotBusterHandle);

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
}

void SceneMain::Init()
{
	// プレイヤーの初期化
	assert(m_pPlayer);	// m_pPlayer == nullptrの場合止まる
	m_pPlayer->Init();
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	// プレイヤーの更新
	m_pPlayer->Update();

	Rect playerRect = m_pPlayer->GetColRect();

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
}

void SceneMain::Draw()
{
	// プレイヤーの描画
	m_pPlayer->Draw();

	// 弾の描画
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pShot[i])continue;
		m_pShot[i]->Draw();
	}
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
