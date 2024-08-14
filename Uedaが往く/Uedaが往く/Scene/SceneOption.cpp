#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "Game.h"
#include "UI.h"
#include "SceneOption.h"

// 定数
namespace
{
	constexpr int kBackColor = 0xdddddd;			// 背景の色
	constexpr int kBackBoxColor = 0x494949;			// 四角の色
	constexpr int kBackBoxLTPos = 140;				// 四角の左上位置
	constexpr int kBackBoxWidth = 490;				// 四角の幅
	const Vec2 kSelectTextPos = { 200, 300 };		// 選択テキスト表示位置
	constexpr float kSelectTextInterval = 100.0f;	// 選択テキスト表示間隔
	const Vec2 kCursorPos = { 140, 290 };			// カーソル表示位置
}


/// <summary>
/// コンストラクタ
/// </summary>
SceneOption::SceneOption(std::shared_ptr<SceneBase> pScene):
	m_pPrevScene(pScene)
{
}


/// <summary>
/// デストラクタ
/// </summary>
SceneOption::~SceneOption()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneOption::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input"></param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneOption::Update(Input& input)
{
	//選択状態更新
	UpdateSelect(input, kSelectNum);
	m_pUI->Update();

	if (input.IsTriggered("back"))
	{
		return m_pPrevScene;	// 前の画面にもどる
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneOption::Draw()
{
	// 背景描画
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBackColor, true);
	// 背景の四角部分表示
	DrawBox(kBackBoxLTPos, 0, kBackBoxLTPos + kBackBoxWidth, Game::kScreenHeight, kBackBoxColor, true);

	// カーソル表示
	m_pUI->DrawCursor(kCursorPos, m_select, kSelectTextInterval);

	// 選択項目表示
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kSound , "サウンド", 0xffffff);
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kBrightness, "明るさ", 0xffffff);
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kKyeConfig, "ボタン配置", 0xffffff);

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "オプション画面", 0xffffff);
#endif
}
