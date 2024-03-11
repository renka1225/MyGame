#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"
#include <memory>

/// <summary>
/// 定数
/// </summary>
namespace
{
	// ゲーム時間
	constexpr int kClearTime = 60 * 120;
}

ScenePlaying::ScenePlaying():
	m_time(0)
{
	m_pPlayer = std::make_shared<Player>();
	m_pEnemy = std::make_shared<Enemy>();
	m_pCamera = std::make_shared<Camera>();
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
	// タイム更新
	m_time++;

	// クリア
	if (m_time >= kClearTime)
	{
		return std::make_shared<SceneClear>();
	}

	// プレイヤーの更新
	m_pPlayer->Update(input);
	// 敵の更新
	m_pEnemy->Update();
	// カメラの更新
	m_pCamera->Update(m_pPlayer);

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
	// 経過時間の描画
	int milliSec = m_time * 1000 / 60;
	int sec = (milliSec / 1000) % 120;
	milliSec %= 1000;
	DrawFormatString(0, 50, 0xffffff, "time:%03d:%03d", sec, milliSec);

	// プレイヤーの描画
	m_pPlayer->Draw();
	// 敵の描画
	m_pEnemy->Draw();

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
