#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneTitle.h"
#include "ManagerResult.h"
#include "Input.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager():
	m_pScene(nullptr)
{
	m_pResult = std::make_shared<ManagerResult>();
}


/// <summary>
/// 初期化
/// </summary>
void SceneManager::Init()
{
	m_pScene = std::make_shared<SceneTitle>();
	m_pScene->Init(m_pResult);
}


/// <summary>
/// 更新
/// </summary>
void SceneManager::Update(Input& input)
{
	std::shared_ptr<SceneBase> pNext = m_pScene->Update(input);

	// 遷移先のシーンの開始処理を行う
	if (pNext != m_pScene)
	{
		// Updateが返した新しいシーンの開始処理を行う
		m_pScene = pNext;
		m_pScene->Init(m_pResult);
	}
}


/// <summary>
/// 描画
/// </summary>
void SceneManager::Draw()
{
	m_pScene->Draw();
}