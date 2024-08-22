#pragma once
#include "Vec2.h"

/// <summary>
/// UIの表示に関するクラス
/// </summary>
class UI
{
public:
	UI();
	virtual ~UI();
	void Init();
	void Update();
	void DrawCursor(Vec2 pos, int select, float interval, bool isOption = false); // カーソル表示
	void DrawPauseBack();		// ポーズ画面の背景表示
	void DrawMenuBg();			// メニューの背景表示
	void DrawButtonText();		// ボタンテキスト表示
	void DrawClearButtonText();	// クリア画面でのボタンテキスト表示


protected:
	int m_buttonHandle;		// ボタンの画像

	// ボタンの種類
	enum ButtonKind
	{
		kAButton,		// A
		kBButton,		// B
		kXButton,		// X
		kYButton,		// Y
		kMenuButton,	// メヌー
		kViewButton,	// ビュー
		kLStick,		// 左スティック
		kRStick,		// 右スティック
		kLBButton,		// LB
		kRBButton,		// RB
	};

private:
	float m_cursorWidth;	// カーソルの横幅
	bool m_isOption;		// オプション画面かどうか
	int m_cursorHandle;		// カーソルの画像
	int m_backHandle;		// 背景の画像
};