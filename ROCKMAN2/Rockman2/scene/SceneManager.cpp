#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneStage1.h"
#include "SceneClear.h"
#include "SceneGameOver.h"
#include "Pad.h"

SceneManager::SceneManager() :
	m_runScene(kSceneTitle)
{
	// クラスのメモリを確保する
	m_pTitle = new SceneTitle;
	//m_pOption = new SceneOption;
	m_pStage1 = new SceneStage1;
	m_pClear = new SceneClear;
	m_pGameOver = new SceneGameOver;
}

SceneManager::~SceneManager()
{
	// クラスのメモリを解放する
	delete m_pTitle;
	m_pTitle = nullptr;

	delete m_pStage1;
	m_pStage1 = nullptr;

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
		// ステージ1
	case kSceneStage1:
		m_pStage1->Init();
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
		// ステージ1
	case kSceneStage1:
		m_pStage1->End();
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
			m_runScene = kSceneStage1;
			m_pStage1->Init();
		}
		break;
		// ステージ1
	case kSceneStage1:
		m_pStage1->End();
		if (m_pStage1->IsSceneGameOver())
		{
			m_runScene = kSceneGameOver;
			m_pGameOver->Init();
		}
		else if (m_pStage1->IsSceneClear())
		{
			m_runScene = kSceneClear;
			m_pClear->Init();
		}
		else if (m_pStage1->IsSceneTitle())
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
			m_pStage1->Init();
		}
		else if (m_pStage1->IsSceneEnd()) // リトライ
		{
			m_runScene = kSceneStage1;
			m_pStage1->Init();
		}
		break;

		// ゲームクリア
	case kSceneClear:
		m_pClear->End();
		if (m_pClear->IsSceneStageSelect())
		{
			m_runScene = kSceneStage1;
			m_pStage1->Init();
		}
		else if (m_pClear->IsSceneTitle())
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

		// ゲームオーバー
	case kSceneGameOver:
		m_pGameOver->End();
		if (m_pGameOver->IsSeneRetry()) // リトライ
		{
			m_runScene = kSceneStage1;
			m_pStage1->Init();
		}
		else if (m_pGameOver->IsSceneTitle())	// タイトル
		{
			m_runScene = kSceneTitle;
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
		// ステージ1
	case kSceneStage1:
		m_pStage1->Update();
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
		// ステージ1
	case kSceneStage1:
		m_pStage1->Draw();
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
