#include "DxLib.h"
#include "Vec2.h"
#include "Game.h"
#include "Font.h"
#include "UI.h"
#include <algorithm>

// 定数
namespace
{
	// 背景関連
	constexpr int kBackColor = 0xdddddd;			// 背景の色
	constexpr int kBackBoxColor = 0x494949;			// 四角の色
	constexpr int kBackBoxLTPos = 140;				// 四角の左上位置
	constexpr int kBackBoxWidth = 490;				// 四角の幅
	// カーソル関連
	constexpr float kCursorWidth = 489.0f;			// カーソルの横幅
	constexpr float kOptionCursorWidth = 1000.0f;	// オプション画面のカーソルの横幅
	constexpr float kCursorHeight = 90.0f;			// カーソルの縦幅
	constexpr float kCursorSpeed = 60.0f;			// カーソルの横幅の伸びる量
	// ボタンの画像とテキストの位置
	const Vec2 kButtonTextPos = { 1500, 970 };		// テキストの位置
	constexpr float kButtonTextWidth = 150.0f;		// テキストの幅
	constexpr int kTextColor = 0xffffff;			// テキストの色
}


/// <summary>
/// コンストラクタ
/// </summary>
UI::UI():
	m_cursorWidth(0.0f),
	m_isOption(false)
{
	m_cursorHandle = LoadGraph("data/UI/cursor.png");
}


/// <summary>
/// デストラクタ
/// </summary>
UI::~UI()
{
	DeleteGraph(m_cursorHandle);
}


/// <summary>
/// 初期化
/// </summary>
void UI::Init()
{
	m_cursorWidth = 0.0f;
}


/// <summary>
/// 更新
/// </summary>
void UI::Update()
{
	// カーソルの横幅を更新
	// オプション画面の場合のみカーソルの長さを変える
	m_cursorWidth += kCursorSpeed;
	if (m_isOption)
	{
		m_cursorWidth = std::min(m_cursorWidth, kOptionCursorWidth);
	}
	else
	{
		m_cursorWidth = std::min(m_cursorWidth, kCursorWidth);
	}
}


/// <summary>
///  カーソル表示
/// </summary>
/// <param name="pos">表示位置</param>
/// <param name="select">選択状態</param>
/// <param name="interval">表示間隔</param>
void UI::DrawCursor(Vec2 pos, int select, float interval, bool isOption)
{
	m_isOption = isOption;
	DrawExtendGraphF(pos.x, pos.y + interval * select,
		pos.x + m_cursorWidth, pos.y + interval * select + kCursorHeight,
		m_cursorHandle, true);
}


/// <summary>
/// メニューの背景表示
/// </summary>
void UI::DrawMenuBg()
{
	// 背景描画
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBackColor, true);
	// 背景の四角部分表示
	DrawBox(kBackBoxLTPos, 0, kBackBoxLTPos + kBackBoxWidth, Game::kScreenHeight, kBackBoxColor, true);
}


/// <summary>
/// ボタンの画像とテキストを表示する
/// </summary>
void UI::DrawButtonText()
{
	//TODO:シーンによってテキストを変更する

	// テキスト表示
	DrawStringFToHandle(kButtonTextPos.x, kButtonTextPos.y,
		"決定", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kButtonText)]);
	DrawStringFToHandle(kButtonTextPos.x + kButtonTextWidth, kButtonTextPos.y,
		"もどる", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kButtonText)]);
}
