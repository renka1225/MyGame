#include "ManagerFont.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
ManagerFont::ManagerFont()
{
	// ファイルのロード
	LPCSTR font_path = "data/font/Pomeranian-Regular.ttf";

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
	{
	}
	else
	{
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

	m_textFontHandle = CreateFontToHandle("Pomeranian", 30, -1);
	m_textFont2Handle = CreateFontToHandle("Pomeranian", 25, -1);
	m_startCountFontHandle = CreateFontToHandle("Pomerania", 100, -1);
	m_timeFontHandle = CreateFontToHandle("Pomerania", 35, -1);
	m_resultTimeFontHandle = CreateFontToHandle("Pomerania", 25, -1);
	m_creditFontHandle = CreateFontToHandle("Pomerania", 15, -1);
}


/// <summary>
/// デストラクタ
/// </summary>
ManagerFont::~ManagerFont()
{
	DeleteFontToHandle(m_textFontHandle);
	DeleteFontToHandle(m_textFont2Handle);
	DeleteFontToHandle(m_startCountFontHandle);
	DeleteFontToHandle(m_timeFontHandle);
	DeleteFontToHandle(m_resultTimeFontHandle);
	DeleteFontToHandle(m_creditFontHandle);
}
