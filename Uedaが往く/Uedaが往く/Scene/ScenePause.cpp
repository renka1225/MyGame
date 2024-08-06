#include "DxLib.h"
#include "Input.h"
#include "Game.h"
#include "ScenePause.h"
#include "SceneOption.h"
#include "SceneSelectStage.h"

// 定数
namespace
{
	constexpr int kAlpha = 200;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pScene">前に実行していたシーン</param>
ScenePause::ScenePause(std::shared_ptr<SceneBase> pScene)
{
	m_select = Select::kBack;
	m_pPrevScene = pScene;
}


/// <summary>
/// デストラクタ
/// </summary>
ScenePause::~ScenePause()
{
}


/// <summary>
/// 初期化
/// </summary>
void ScenePause::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> ScenePause::Update(Input& input)
{
	UpdateSelect(input, Select::kSelectNum);

	if (input.IsTriggered("OK"))
	{
		if (m_select == Select::kBack)
		{
			return m_pPrevScene;	// ゲーム画面
		}
		else if (m_select == Select::kOption)
		{
			return std::make_shared<SceneOption>(shared_from_this());	// オプション画面
		}
		else if (m_select == Select::kStageSelect)
		{
			return std::make_shared<SceneSelectStage>(); // ステージ選択画面
		}
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void ScenePause::Draw()
{
	// プレイ画面を薄く表示する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAlpha);
	m_pPrevScene->Draw();
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 背景に黒枠を表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAlpha);
	DrawBox(500, 200, 1420, 880, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// カーソル表示
	for (int i = 0; i < Select::kSelectNum; i++)
	{
		DrawBox(700, 300 + 200 * i, 1220, 400 + 200 * i, 0xffffff, true);
	}

	// 文字表示
	DrawString(750, 320, "ゲームにもどる", 0x000000);
	DrawString(750, 520, "オプション", 0x000000);
	DrawString(750, 720, "ステージ選択に戻る", 0x000000);

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "ポーズ画面", 0xffffff);
#endif
}
