#include "DxLib.h"
#include "UI.h"
#include <algorithm>

// 定数
namespace
{
	constexpr float kCursorWidth = 489.0f;			// カーソルの横幅
	constexpr float kCursorHeight = 90.0f;			// カーソルの縦幅
	constexpr float kCursorSpeed = 60.0f;			// カーソルの横幅の伸びる量
}


/// <summary>
/// コンストラクタ
/// </summary>
UI::UI():
	m_cursorWidth(0.0f)
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
	m_cursorWidth += kCursorSpeed;
	m_cursorWidth = std::min(m_cursorWidth, kCursorWidth);
}


/// <summary>
///  カーソル表示
/// </summary>
/// <param name="pos">表示位置</param>
/// <param name="select">選択状態</param>
/// <param name="interval">表示間隔</param>
void UI::DrawCursor(Vec2 pos, int select, float interval)
{
	DrawExtendGraphF(pos.x, pos.y + interval * select,
		pos.x + m_cursorWidth, pos.y + interval * select + kCursorHeight,
		m_cursorHandle, true);
}
