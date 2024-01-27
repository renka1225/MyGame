#include "FontManager.h"
#include "DxLib.h"

FontManager::FontManager()
{
	/*フォント*/
// ファイルのロード
	LPCSTR font_path = "data/851Gkktt_005.ttf";	// 読み込むフォントファイルのパス

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
	{
	}
	else
	{
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

	m_fontHandle = CreateFontToHandle("851ゴチカクット", 30, -1);
}

FontManager::~FontManager()
{
	DeleteFontToHandle(m_fontHandle);
}
