#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "Player.h"
#include "Camera.h"
#include "Input.h"
#include "DxLib.h"

ScenePlaying::ScenePlaying()
{
	m_pPlayer = std::make_shared<Player>();
	//m_pCamera = std::make_shared<Camera>(m_pPlayer);
}


ScenePlaying::~ScenePlaying()
{
}


/// <summary>
/// 初期化
/// </summary>
void ScenePlaying::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	// プレイヤーの更新
	m_pPlayer->Update();
	// カメラの更新
	m_pCamera->Update();

#if _DEBUG
	// MEMO:デバック用
	if (input.IsTriggered("debug"))
	{
		return std::make_shared<SceneClear>();
	}
	else if (input.IsTriggered("OK"))
	{
		return std::make_shared<SceneGameover>();
	}
#endif

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void ScenePlaying::Draw()
{
	// プレイヤーの描画
	m_pPlayer->Draw();

#if _DEBUG
	DrawFormatString(0, 0, 0xffffff, "プレイ画面");
#endif
}


/// <summary>
/// 終了
/// </summary>
void ScenePlaying::End()
{
}
