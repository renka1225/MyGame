#include "DxLib.h"
#include "Vec2.h"
#include "Game.h"
#include "Font.h"
#include "UI.h"
#include <algorithm>

// 定数
namespace
{
	/*背景関連*/
	constexpr int kBackColor = 0xdddddd;				// 背景の色
	constexpr int kBackBoxColor = 0x494949;				// 四角の色
	constexpr int kBackBoxLTPos = 140;					// 四角の左上位置
	constexpr int kBackBoxWidth = 490;					// 四角の幅
	const Vec2 kBackHandlePos = { 750.0f, 200.0f };		// 背景画像の表示位置

	const Vec2 kPauseBackLTPos = { 600.0f, 200.0f };	// ポーズ画面の背景画像左上位置
	const Vec2 kPauseBackRBPos = { 1320.0f, 880.0f };	// ポーズ画面の背景画像右下位置

	/*カーソル関連*/
	constexpr float kCursorWidth = 489.0f;				// カーソルの横幅
	constexpr float kOptionCursorWidth = 1000.0f;		// オプション画面のカーソルの横幅
	constexpr float kCursorHeight = 90.0f;				// カーソルの縦幅
	constexpr float kCursorSpeed = 60.0f;				// カーソルの横幅の伸びる量

	/*ボタンの画像とテキストの位置*/
	const Vec2 kButtonPos = { 1500, 1000 };				// ボタン表示位置
	const Vec2 kClearButtonPos = { 1450, 1000 };		// クリア時ボタン表示位置
	constexpr float kButtonWidth = 180.0f;				// 表示するボタンの幅
	constexpr int kButtonSize = 32;						// ボタン画像のサイズ
	constexpr float kButtonScale = 1.5f;				// ボタンの拡大率
	const Vec2 kButtonTextPos = { 1530, 970 };			// テキストの位置
	const Vec2 kClearButtonTextPos = { 1480, 975 };		// クリア時のテキスト位置
	constexpr float kButtonTextWidth = 170.0f;			// テキストの幅
	constexpr int kTextColor = 0xffffff;				// テキストの色

	/*操作説明画面*/
	const Vec2 kOperationFramePos = { 1720.0f, 280.0f };	// 枠表示位置
	constexpr float kOperationWidth = 300.0f;				// 枠の横幅
	constexpr float kOperationHeight = 350.0f;				// 枠の縦幅
	constexpr int kOperationBackColor = 0x000000;			// 枠の背景色
	const Vec2 kOperationTextPos = { 1730.0f, 300.0f };		// テキストの表示位置
	const Vec2 kOperationButtonPos = { 1880.0f, 320.0f };	// ボタン位置
	constexpr float kOperationButtonScale = 1.0f;			// ボタンサイズ
	constexpr float kOperationInterval = 40.0f;				// 表示間隔
}


/// <summary>
/// コンストラクタ
/// </summary>
UI::UI():
	m_cursorWidth(0.0f),
	m_isOption(false)
{
	m_cursorHandle = LoadGraph("data/UI/cursor.png");
	m_buttonHandle = LoadGraph("data/UI/button.png");
	m_backHandle = LoadGraph("data/UI/back.png");
}


/// <summary>
/// デストラクタ
/// </summary>
UI::~UI()
{
	DeleteGraph(m_cursorHandle);
	DeleteGraph(m_buttonHandle);
	DeleteGraph(m_backHandle);
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
/// ポーズ画面の背景表示
/// </summary>
void UI::DrawPauseBack()
{
	// 背景画像表示
	DrawExtendGraphF(kPauseBackLTPos.x, kPauseBackLTPos.y, kPauseBackRBPos.x, kPauseBackRBPos.y, m_backHandle, true);
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
	// 背景画像表示
	DrawGraphF(kBackHandlePos.x, kBackHandlePos.y, m_backHandle, true);
}


/// <summary>
/// ボタンの画像とテキストを表示する
/// </summary>
void UI::DrawButtonText()
{
	// テキスト表示
	DrawStringFToHandle(kButtonTextPos.x, kButtonTextPos.y,
		"決定", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kButtonText)]);
	DrawStringFToHandle(kButtonTextPos.x + kButtonTextWidth, kButtonTextPos.y,
		"もどる", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kButtonText)]);

	// ボタン画像表示
	DrawRectRotaGraphF(kButtonPos.x, kButtonPos.y, kButtonSize * ButtonKind::kAButton, 0, kButtonSize, kButtonSize, kButtonScale, 0.0f, m_buttonHandle, true);
	DrawRectRotaGraphF(kButtonPos.x + kButtonWidth, kButtonPos.y, kButtonSize * ButtonKind::kBButton, 0, kButtonSize, kButtonSize, kButtonScale, 0.0f, m_buttonHandle, true);
}


/// <summary>
/// クリア画面でボタンの画像とテキスト表示する
/// </summary>
void UI::DrawClearButtonText()
{
	// テキスト表示
	DrawStringFToHandle(kClearButtonTextPos.x, kClearButtonTextPos.y,
		"ステージ選択にもどる", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearButtonText)]);

	// ボタン画像表示
	DrawRectRotaGraphF(kClearButtonPos.x, kClearButtonPos.y, kButtonSize * ButtonKind::kAButton, 0, kButtonSize, kButtonSize, kButtonScale, 0.0f, m_buttonHandle, true);
}


/// <summary>
/// 操作説明を表示する
/// </summary>
void UI::DrawOperation()
{
	// 背景を薄く表示する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxAA(kOperationFramePos.x, kOperationFramePos.y, kOperationFramePos.x + kOperationWidth, kOperationFramePos.y + kOperationHeight, kOperationBackColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// テキスト表示
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kMove,
		"移動", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kCameraMove,
		"カメラ移動", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kPunch,
		"パンチ", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kKick,
		"キック", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kAvoid,
		"回避", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kGuard,
		"ガード", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kRockon,
		"ロックオン", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kPause,
		"ポーズ", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);

	// ボタン画像表示
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kMove,
		kButtonSize * ButtonKind::kRStick, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);		// Rスティック
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kCameraMove,
		kButtonSize * ButtonKind::kLStick, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);		// Lスティック
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kPunch,
		kButtonSize * ButtonKind::kXButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// X
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kKick,
		kButtonSize * ButtonKind::kYButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// Y
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kAvoid,
		kButtonSize * ButtonKind::kAButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// A
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kGuard,
		kButtonSize * ButtonKind::kLBButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// LB
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kRockon,
		kButtonSize * ButtonKind::kRBButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// RB
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kPause,
		kButtonSize * ButtonKind::kMenuButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// Menu
}
