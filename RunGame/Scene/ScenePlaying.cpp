#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "ManagerModel.h"
#include "Background.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Input.h"
#include "Game.h"
#include <memory>


/// <summary>
/// コンストラクタ
/// </summary>
ScenePlaying::ScenePlaying():
	m_time(0),
	m_enemyPos(VGet(0.0f, 0.0f, 0.0f))
{
	m_pModel = std::make_shared<ManagerModel>();
	m_pBackground = std::make_shared<Background>(m_pModel);
	m_pPlayer = std::make_shared<Player>(m_pModel);
	m_pCamera = std::make_shared<Camera>();

	m_pEnemy.resize(kEnemyNum);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = std::make_shared<Enemy>(m_pModel);
	}
}


/// <summary>
/// 初期化
/// </summary>
void ScenePlaying::Init()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i]->Init(VGet(i * 100, 0.0f, 0.0f));
	}
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

	// 背景の更新
	m_pBackground->Update();
	// プレイヤーの更新
	m_pPlayer->Update(input);
	// カメラの更新
	m_pCamera->Update(m_pPlayer);
	// 敵の更新
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// 敵の更新
		m_pEnemy[i]->Update();
	}

#if _DEBUG
	// MEMO:デバック用ボタン
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
	// 背景の描画
	m_pBackground->Draw();

	// プレイヤーの描画
	m_pPlayer->Draw();

	// 敵の描画
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i]->Draw();
	}

	// 経過時間の描画
	int milliSec = m_time * 1000 / 60;
	int sec = (milliSec / 1000) % 120;
	milliSec %= 1000;
	DrawFormatString(0, 50, 0xffffff, "time:%03d:%03d", sec, milliSec);

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
