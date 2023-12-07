#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneGameOver.h"
#include "Pad.h"

SceneManager::SceneManager() :
	m_runScene(kSceneKindTitle)
{
	// クラスのメモリを確保する
	m_pTitle = new SceneTitle;
	m_pMain = new SceneMain;
	m_pGameOver = new SceneGameOver;
}

SceneManager::~SceneManager()
{
	// クラスのメモリを解放する
	delete m_pTitle;
	m_pTitle = nullptr;

	delete m_pMain;
	m_pMain = nullptr;

	delete m_pGameOver;
	m_pGameOver = nullptr;
}

void SceneManager::Init()
{
	// 実行するシーンの初期化を行う
	switch (m_runScene)
	{
	case kSceneKindTitle: // タイトルシーンの場合
		m_pTitle->Init();
		break;
	case kSceneKindMain: // ゲームシーンの場合
		m_pMain->Init();
		break;
	case kSceneKindGameOver: // ゲームオーバーの場合
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
	case kSceneKindTitle: // タイトルシーンの場合
		m_pTitle->End();
		break;
	case kSceneKindMain: // ゲームシーンの場合
		m_pMain->End();
		break;
	case kSceneKindGameOver: // ゲームオーバーの場合
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
	case kSceneKindTitle: // タイトルシーンの場合
		// タイトル画面が終了されたか
		if (m_pTitle->IsSceneEnd())
		{
			m_pTitle->End();			 // タイトルの終了処理を行う
			m_runScene = kSceneKindMain; // ゲーム画面に切り替える
			m_pMain->Init();			 // ゲーム画面の初期化
		}
		break;
	case kSceneKindMain: // ゲームシーンの場合
		// ゲーム画面が終了されたか
		if (m_pMain->IsSceneEnd())
		{
			m_pMain->End();					 // ゲームシーンの終了処理を行う
			m_runScene = kSceneKindGameOver; // ゲームオーバー画面に切り替える
			m_pGameOver->Init();			 // ゲームオーバー画面の初期化
		}
		break;
	case kSceneKindGameOver: // ゲームオーバーシーンの場合
		// ゲームオーバー画面が終了されたか
		if (m_pGameOver->IsSceneEnd())
		{
			m_pGameOver->End();				// ゲームオーバーの終了処理を行う
			m_runScene = kSceneKindTitle;	// タイトル画面に切り替える
			m_pTitle->Init();				// タイトル画面の初期化
		}
		break;
	}

	// 実行するシーンの更新を行う
	switch (m_runScene)
	{
	case kSceneKindTitle: // タイトルシーンの場合
		m_pTitle->Update();
		break;
	case kSceneKindMain: // ゲームシーンの場合
		m_pMain->Update();
		break;
	case kSceneKindGameOver: // ゲームオーバーの場合
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
	case kSceneKindTitle: // タイトルシーンの場合
		m_pTitle->Draw();
		break;
	case kSceneKindMain: // ゲームシーンの場合
		m_pMain->Draw();
		break;
	case kSceneKindGameOver: // ゲームオーバーの場合
		m_pGameOver->Draw();
		break;
	default:
		break;
	}
}
