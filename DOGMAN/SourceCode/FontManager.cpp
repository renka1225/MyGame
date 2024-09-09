#include "FontManager.h"
#include "DxLib.h"

FontManager::FontManager()
{
	/*フォント*/
	// ファイルのロード
	LPCSTR font_path = "data/Kaisotai-Next-UP-B.otf";

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
	{
	}
	else
	{
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

	m_fontHandle = CreateFontToHandle("廻想体 ネクスト UP B", 28, -1);
	m_fontHandle2 = CreateFontToHandle("廻想体 ネクスト UP B", 36, -1);
	m_fontHandle3 = CreateFontToHandle("廻想体 ネクスト UP B", 45, -1);
	m_fontStaging = CreateFontToHandle("廻想体 ネクスト UP B", 85, -1);
}

FontManager::~FontManager()
{
	DeleteFontToHandle(m_fontHandle);
	DeleteFontToHandle(m_fontHandle2);
	DeleteFontToHandle(m_fontHandle3);
	DeleteFontToHandle(m_fontStaging);
}
