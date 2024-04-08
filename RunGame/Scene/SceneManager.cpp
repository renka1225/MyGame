#include "SceneManager.h"
#include "SceneTitle.h"
#include "Input.h"

SceneManager::SceneManager():
	m_pScene(nullptr)
{
}


SceneManager::~SceneManager()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneManager::Init()
{
	m_pScene = std::make_shared<SceneTitle>();
	m_pScene->Init();
}


/// <summary>
/// 更新
/// </summary>
void SceneManager::Update(Input& input)
{
	std::shared_ptr<SceneBase> pNext = m_pScene->Update(input);

	// 遷移先のシーンの開始処理を行う
	m_pScene = pNext;
	m_pScene->Init();
}


/// <summary>
/// 描画
/// </summary>
void SceneManager::Draw()
{
	m_pScene->Draw();
}