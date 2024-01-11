#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneStageSelect.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneGameOver.h"
#include "Pad.h"

SceneManager::SceneManager() :
	m_runScene(kSceneTitle)
{
	// クラスのメモリを確保する
	m_pTitle = new SceneTitle;
	m_pStageSelect = new SceneStageSelect;
	m_pMain = new SceneMain;
	m_pClear = new SceneClear;
	m_pGameOver = new SceneGameOver;
}

SceneManager::~SceneManager()
{
	// クラスのメモリを解放する
	delete m_pTitle;
	m_pTitle = nullptr;

	delete m_pStageSelect;
	m_pStageSelect = nullptr;

	delete m_pMain;
	m_pMain = nullptr;

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
	case kSceneTitle:		// タイトルシーンの場合
		m_pTitle->Init();
		break;
	case kSceneStageSelect: // ステージ選択シーンの場合
		m_pStageSelect->Init();
		break;
	case kSceneMain:		// ゲームシーンの場合
		m_pMain->Init();
		break;
	case kSceneClear:		// ゲームクリアの場合
		m_pClear->Init();
		break;
	case kSceneGameOver:	// ゲームオーバーの場合
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
	case kSceneTitle: // タイトルシーンの場合
		m_pTitle->End();
		break;
	case kSceneStageSelect: // ステージ選択シーンの場合
		m_pStageSelect->End();
		break;
	case kSceneMain: // ゲームシーンの場合
		m_pMain->End();
		break;
	case kSceneClear:		// ゲームクリアの場合
		m_pClear->End();
		break;
	case kSceneGameOver: // ゲームオーバーの場合
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
	case kSceneTitle: // タイトルシーンの場合
		// タイトル画面が終了されたか
		if (m_pTitle->IsSceneEnd())
		{
			m_pTitle->End();					// タイトルの終了処理を行う
			m_runScene = kSceneStageSelect; // ステージ選択画面に切り替える
			m_pMain->Init();					// ゲーム画面の初期化
		}
		break;
	case kSceneStageSelect: // ステージ選択シーンの場合
		if (m_pStageSelect->IsSceneEnd())
			m_runScene = kSceneMain;
		break;
	case kSceneMain: // ゲームシーンの場合
		// ゲーム画面が終了されたか
		if (m_pMain->IsSceneEnd())
		{
			m_pMain->End();					 // ゲームシーンの終了処理を行う
			m_runScene = kSceneGameOver; // ゲームオーバー画面に切り替える
			m_pGameOver->Init();			 // ゲームオーバー画面の初期化
		}
		break;
	case kSceneClear:		// ゲームクリアの場合
		m_pClear->Init();
		break;
	case kSceneGameOver: // ゲームオーバーシーンの場合
		// ゲームオーバー画面が終了されたか
		if (m_pGameOver->IsSceneEnd())
		{
			m_pGameOver->End();				// ゲームオーバーの終了処理を行う
			m_runScene = kSceneTitle;	// タイトル画面に切り替える
			m_pTitle->Init();				// タイトル画面の初期化
		}
		break;
	}

	// 実行するシーンの更新を行う
	switch (m_runScene)
	{
	case kSceneTitle: // タイトルシーンの場合
		m_pTitle->Update();
		break;
	case kSceneStageSelect: // ステージ選択シーンの場合
		m_pStageSelect->Update();
		break;
	case kSceneMain: // ゲームシーンの場合
		m_pMain->Update();
		break;
	case kSceneClear:		// ゲームクリアの場合
		m_pClear->Draw();
		break;
	case kSceneGameOver: // ゲームオーバーの場合
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
	case kSceneTitle: // タイトルシーンの場合
		m_pTitle->Draw();
		break;
	case kSceneStageSelect: // ステージ選択シーンの場合
		m_pStageSelect->Draw();
		break;
	case kSceneMain: // ゲームシーンの場合
		m_pMain->Draw();
		break;
	case kSceneClear:		// ゲームクリアの場合
		m_pClear->Draw();
		break;
	case kSceneGameOver: // ゲームオーバーの場合
		m_pGameOver->Draw();
		break;
	default:
		break;
	}
}
