#pragma once
#include "Vec2.h"

/// <summary>
/// UIの表示に関するクラス
/// </summary>
class UI
{
public:
	UI();
	~UI();
	void Init();
	void Update();
	void DrawCursor(Vec2 pos, int select, float interval, bool isOption = false); // カーソル表示
	void DrawMenuBg();	// メニューの背景表示

private:
	float m_cursorWidth;	// カーソルの横幅
	bool m_isOption;		// オプション画面かどうか
	int m_cursorHandle;		// カーソルの画像
};