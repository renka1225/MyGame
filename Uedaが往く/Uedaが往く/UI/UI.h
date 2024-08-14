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
	void DrawCursor(Vec2 pos, int select, float interval);

private:
	float m_cursorWidth;	// カーソルの横幅
	int m_cursorHandle;		// カーソルの画像
};