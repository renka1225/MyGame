#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneOption.h"
#include "SceneStageSelect.h"
#include "SceneMain.h"
#include "SceneStage2.h"
#include "SceneStage3.h"
#include "SceneClear.h"
#include "SceneGameOver.h"
#include "Pad.h"

SceneManager::SceneManager() :
	m_runScene(kSceneTitle)
{
	// クラスのメモリを確保する
	m_pTitle = new SceneTitle;
	m_pOption = new SceneOption;
	m_pStageSelect = new SceneStageSelect;
	m_pMain = new SceneMain;
	m_pStage2 = new SceneStage2;
	m_pStage3 = new SceneStage3;
	m_pClear = new SceneClear;
	m_pGameOver = new SceneGameOver;
}

SceneManager::~SceneManager()
{
	// クラスのメモリを解放する
	delete m_pTitle;
	m_pTitle = nullptr;

	delete m_pOption;
	m_pOption = nullptr;

	delete m_pStageSelect;
	m_pStageSelect = nullptr;

	delete m_pMain;
	m_pMain = nullptr;

	delete m_pStage2;
	m_pStage2 = nullptr;

	delete m_pStage3;
	m_pStage3 = nullptr;

	delete m_pClear;
	m_pClear = nullptr;

	delete m_pGameOver;
	m_pGameOver = nullptr;
}

void SceneManager::Init()
{
	// 実行するシーンの初期化を行う
	switch (m_runScene)
	{
		// タイトルシーン
	case kSceneTitle:
		m_pTitle->Init();
		break;
		// オプションシーン
	case kSceneOption:
		m_pOption->Init();
		break;
		// ステージ選択シーン
	case kSceneStageSelect:
		m_pStageSelect->Init();
		break;
		// ゲームシーン
	case kSceneMain:
		m_pMain->Init();
		break;
		// ステージ2
	case kSceneStage2:
		m_pStage2->Init();
		break;
		// ステージ3
	case kSceneStage3:
		m_pStage3->Init();
		break;
		// ゲームクリア
	case kSceneClear:
		m_pClear->Init();
		break;
		// ゲームオーバー
	case kSceneGameOver:
		m_pGameOver->Init();
		break;

	default:
		break;
	}
}

void SceneManager::End()
{
	// 実行するシーンを終了する
	switch (m_runScene)
	{
		// タイトルシーン
	case kSceneTitle:
		m_pTitle->End();
		break;
		// オプションシーン
	case kSceneOption:
		m_pOption->End();
		break;
		// ステージ選択シーン
	case kSceneStageSelect: 
		m_pStageSelect->End();
		break;
		// ゲームシーン
	case kSceneMain:
		m_pMain->End();
		break;
		// ステージ2
	case kSceneStage2:
		m_pStage2->End();
		break;
		// ステージ3
	case kSceneStage3:
		m_pStage3->End();
		break;
		// ゲームクリア
	case kSceneClear:
		m_pClear->End();
		break;
		// ゲームオーバー
	case kSceneGameOver:
		m_pGameOver->End();
		break;
	default:
		break;
	}
}

void SceneManager::Update()
{
	Pad::Update();

	// 実行するシーンの切り替えを行う
	switch (m_runScene)
	{
		// タイトルシーン
	case kSceneTitle:
		m_pTitle->End();
		if (m_pTitle->IsSceneStart())
		{
			m_runScene = kSceneStageSelect;
			m_pStageSelect->Init();
		}
		else if (m_pTitle->IsSceneOption())
		{
			m_runScene = kSceneOption;
			m_pOption->Init();
		}
		break;

		// オプションシーン
	case kSceneOption:
		m_pOption->End();
		if (m_pOption->IsSceneTitle())
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

		// ステージ選択シーン
	case kSceneStageSelect:
		m_pStageSelect->End();
		if (m_pStageSelect->IsSceneStage1())
		{
			m_runScene = kSceneMain;
			m_pMain->Init();
		}
		else if (m_pStageSelect->IsSceneStage2())
		{
			m_runScene = kSceneStage2;
			m_pStage2->Init();
		}
		else if (m_pStageSelect->IsSceneTitle())
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

		// ステージ2
	case kSceneStage2:
		m_pStage2->End();
		break;

		// ゲームシーン
	case kSceneMain:
		m_pMain->End();
		if (m_pMain->IsSceneGameOver())
		{
			m_runScene = kSceneGameOver;
			m_pGameOver->Init();
		}
		else if (m_pMain->IsSceneClear())
		{
			m_runScene = kSceneClear;
			m_pClear->Init();
		}
		break;

		// ステージ3
	case kSceneStage3:
		m_pStage3->End();
		break;

		// ゲームクリア
	case kSceneClear:
		m_pClear->End();
		if (m_pClear->IsSceneStageSelect())
		{
			m_runScene = kSceneStageSelect;
			m_pStageSelect->Init();
		}
		else if (m_pClear->IsSceneTitle())
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

		// ゲームオーバー
	case kSceneGameOver:
		if (m_pGameOver->IsSceneSelect())
		{
			m_pGameOver->End();
			m_runScene = kSceneStageSelect;
			m_pTitle->Init();
		}
		break;

	default:
		break;
	}

	// 実行するシーンの更新を行う
	switch (m_runScene)
	{
		// タイトルシーン
	case kSceneTitle:
		m_pTitle->Update();
		break;
		// オプションシーン
	case kSceneOption:
		m_pOption->Update();
		break;
		// ステージ選択シーン
	case kSceneStageSelect:
		m_pStageSelect->Update();
		break;
		// ゲームシーン
	case kSceneMain:
		m_pMain->Update();
		break;
		// ステージ2
	case kSceneStage2:
		m_pStage2->Update();
		break;
		// ステージ3
	case kSceneStage3:
		m_pStage3->Update();
		break;
		// ゲームクリア
	case kSceneClear:
		m_pClear->Update();
		break;
		// ゲームオーバー
	case kSceneGameOver:
		m_pGameOver->Update();
		break;
	default:
		break;
	}
}

void SceneManager::Draw()
{
	// 実行するシーンの描画を行う
	switch (m_runScene)
	{
		// タイトルシーン
	case kSceneTitle:
		m_pTitle->Draw();
		break;
		// オプションシーン
	case kSceneOption:
		m_pOption->Draw();
		break;
		// ステージ選択シーン
	case kSceneStageSelect:
		m_pStageSelect->Draw();
		break;
		// ゲームシーン
	case kSceneMain:
		m_pMain->Draw();
		break;
		// ステージ2
	case kSceneStage2:
		m_pStage2->Draw();
		break;
		// ステージ3
	case kSceneStage3:
		m_pStage3->Draw();
		break;
		// ゲームクリア
	case kSceneClear:
		m_pClear->Draw();
		break;
		// ゲームオーバー
	case kSceneGameOver:
		m_pGameOver->Draw();
		break;
	default:
		break;
	}
}
