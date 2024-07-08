#include "DxLib.h"
#include "Player.h"
#include "Camera.h"
#include "Input.h"
#include "Stage.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStage1.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneStage1::SceneStage1(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage):
	m_pPlayer(pPlayer),
	m_pCamera(pCamera),
	m_pStage(pStage)
{
}

/// <summary>
/// デストラクタ
/// </summary>
SceneStage1::~SceneStage1()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneStage1::Init()
{
	m_pPlayer->Init();
	m_pCamera->Init();
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <returns></returns>
std::shared_ptr<SceneBase> SceneStage1::Update(Input& input)
{
	// シーン遷移
	if (input.IsTriggered("debug_clear"))
	{
		return std::make_shared<SceneClear>();
	}
	else if (input.IsTriggered("debug_gameover"))
	{
		return std::make_shared<SceneGameover>();
	}

	m_pPlayer->Update(input, *m_pCamera, *m_pStage);
	m_pCamera->Update(input, *m_pPlayer);

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneStage1::Draw()
{
	// ステージ描画
	m_pStage->Draw();
	// プレイヤー描画
	m_pPlayer->Draw();

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "ステージ1", 0xffffff);
#endif
}
