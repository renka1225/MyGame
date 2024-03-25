#include "ManagerFont.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
ManagerFont::ManagerFont()
{
	// ファイルのロード
	LPCSTR font_path = "data/font/KyouryunoGuratan.otf";

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
	{
	}
	else
	{
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

	m_fontHandle = CreateFontToHandle("KyouryunoGuratan", 28, -1);
}


/// <summary>
/// デストラクタ
/// </summary>
ManagerFont::~ManagerFont()
{
	DeleteFontToHandle(m_fontHandle);
}
