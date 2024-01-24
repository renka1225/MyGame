#include "SceneStage3.h"
#include "DxLib.h"
#include "Pad.h"
#include "BgStage3.h"
#include "Player.h"

SceneStage3::SceneStage3()
{
	// プレイヤーのメモリ確保
	m_pPlayer = new Player{ this };

	// 背景のメモリ確保
	m_pBg = new BgStage3;
	m_pBg->SetPlayer(m_pPlayer);
	m_pPlayer->SetBg(m_pBg);
}

SceneStage3::~SceneStage3()
{
	// 背景のメモリ解放
	delete m_pBg;
	m_pBg = nullptr;

	// プレイヤーのメモリ解放
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void SceneStage3::Init()
{
	// 画面遷移の初期化
	m_isSceneGameOver = false;
	m_isSceneClear = false;

	// プレイヤーの初期化
	m_pPlayer->Init();

	// 背景の初期化
	m_pBg->Init();
}

void SceneStage3::End()
{
}

void SceneStage3::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// 背景の更新
	m_pBg->Update();

	// プレイヤーの更新
	m_pPlayer->Update();

#ifdef _DEBUG
	// Cキーでクリア画面に移動するようにする
	if (Pad::IsTrigger(pad & PAD_INPUT_3))
	{
		m_isSceneClear = true; // クリア画面に遷移
	}
#endif
}

void SceneStage3::Draw()
{
	// 背景の描画
	m_pBg->Draw();

	// プレイヤーの描画
	m_pPlayer->Draw();

#ifndef _DEGUG
	DrawString(8, 8, "ステージ3", 0xffffff);
#endif

}
