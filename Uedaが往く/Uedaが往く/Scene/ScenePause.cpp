#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "Game.h"
#include "UI.h"
#include "ScenePause.h"
#include "SceneOption.h"
#include "SceneSelectStage.h"

// 定数
namespace
{
	constexpr int kAlpha = 200;
	constexpr int kBackColor = 0xdcdcdc;				// 背景の色
	constexpr int kBackBoxColor = 0x494949;				// 四角の色
	const Vec2 kBackBoxLTPos = { 500.0f, 120.0f };		// 四角の左上位置
	const Vec2 kBackBoxRBPos = { 1420.0f, 880.0f };		// 四角の右下位置
	constexpr int kBackBoxWidth = 490;					// 四角の幅
	const Vec2 kSelectTextPos = { 750, 300 };			// 選択テキスト表示位置
	constexpr float kSelectTextInterval = 200.0f;		// 選択テキスト表示間隔
	const Vec2 kCursorPos = { 700, 290 };				// カーソル表示位置
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
	// 選択状態を更新
	UpdateSelect(input, Select::kSelectNum);
	m_pUI->Update();

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
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBackColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 背景に黒枠を表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAlpha);
	DrawBoxAA(kBackBoxLTPos.x, kBackBoxLTPos.y, kBackBoxRBPos.x, kBackBoxRBPos.y, kBackBoxColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// カーソル表示
	m_pUI->DrawCursor(kCursorPos, m_select, kSelectTextInterval);

	// テキスト表示
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kBack, "ゲームにもどる", 0x000000);
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kOption ,"オプション", 0x000000);
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kStageSelect,"ステージ選択に戻る", 0x000000);

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "ポーズ画面", 0xffffff);
#endif
}
