#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneOption.h"
#include "SceneStageSelect.h"
#include "SceneTutorial.h"
#include "SceneStage1.h"
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
	m_pTutorial = new SceneTutorial;
	m_pStage1 = new SceneStage1;
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

	delete m_pTutorial;
	m_pTutorial = nullptr;

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
		// 操作説明
	case kSceneOption:
		m_pOption->Init();
		break;
		// ステージ選択シーン
	case kSceneStageSelect:
		m_pStageSelect->Init();
		break;
		// チュートリアル
	case kSceneTutorial:
		m_pTutorial->Init();
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

void SceneManager::Update()
{
	Pad::Update();

	// 実行するシーンの切り替えを行う
	switch (m_runScene)
	{
		// タイトルシーン
	case kSceneTitle:
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

		// 操作説明
	case kSceneOption:
		if (m_pOption->IsSceneTitle())
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

		// ステージ選択シーン
	case kSceneStageSelect:
		if (m_pStageSelect->IsSceneTutorial())		// チュートリアル
		{
			m_runScene = kSceneTutorial;
			m_pTutorial->Init();
		}
		else if (m_pStageSelect->IsSceneStage1())	// ステージ1
		{
			m_runScene = kSceneStage1;
			m_pStage1->Init();
		}
		else if (m_pStageSelect->IsSceneTitle())	// タイトル
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

		// チュートリアル
	case kSceneTutorial:
		if (m_pTutorial->IsSceneGameOver())		// ゲームオーバー
		{
			m_runScene = kSceneGameOver;
			m_pGameOver->Init();
		}
		else if (m_pTutorial->IsSceneClear())	// ゲームクリア
		{
			m_runScene = kSceneClear;
			m_pClear->Init();
		}
		else if (m_pTutorial->IsSceneTitle())	// タイトル
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
			m_pTutorial->Init();
		}
		else if (m_pTutorial->IsSceneEnd())		// リトライ
		{
			m_runScene = kSceneTutorial;
			m_pTutorial->Init();
		}
		break;


		// ステージ1
	case kSceneStage1:
		if (m_pStage1->IsSceneGameOver())		// ゲームオーバー
		{
			m_runScene = kSceneGameOver;
			m_pGameOver->Init();
		}
		else if (m_pStage1->IsSceneClear())		// クリア
		{
			m_runScene = kSceneClear;
			m_pClear->Init();
		}
		else if (m_pStage1->IsSceneTitle())		// タイトル
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
			m_pStage1->Init();
		}
		else if (m_pStage1->IsSceneEnd())		// リトライ
		{
			m_runScene = kSceneStage1;
			m_pStage1->Init();
		}
		break;

		// ゲームクリア
	case kSceneClear:
		if (m_pClear->IsSceneStageSelect())		// リトライ
		{
			m_runScene = kSceneStageSelect;
			m_pStageSelect->Init();
		}
		else if (m_pClear->IsSceneTitle())		// タイトル
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

		// ゲームオーバー
	case kSceneGameOver:
		if (m_pGameOver->IsSeneRetry())			 // リトライ
		{
			if (m_pTutorial->IsSceneGameOver())
			{
				m_runScene = kSceneTutorial;
				m_pTutorial->Init();
			}
			if (m_pStage1->IsSceneGameOver())
			{
				m_runScene = kSceneStage1;
				m_pStage1->Init();
			}
		}
		else if (m_pGameOver->IsSceneSelect())
		{
			m_runScene = kSceneStageSelect;
			m_pStageSelect->Init();
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
		// 操作説明
	case kSceneOption:
		m_pOption->Update();
		break;
		// ステージ選択シーン
	case kSceneStageSelect:
		m_pStageSelect->Update();
		break;
		// チュートリアル
	case kSceneTutorial:
		m_pTutorial->Update();
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
		// 操作説明
	case kSceneOption:
		m_pOption->Draw();
		break;
		// ステージ選択シーン
	case kSceneStageSelect:
		m_pStageSelect->Draw();
		break;
		// チュートリアル
	case kSceneTutorial:
		m_pTutorial->Draw();
		break;
		// ゲームシーン
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
