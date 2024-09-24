#include "DxLib.h"
#include "Font.h"

namespace
{
	// 読み込むフォントファイル名
	const LPCSTR kFontDataPath[] =
	{
		"data/font/TsunagiGothic.ttf",
	};

	// フォントのデータ
	struct FontData
	{
		const char* name;	// フォント名
		int size;			// フォントサイズ
		int thick;			// フォントの太さ(-1:デフォルト)
		int type;			// フォントのタイプ(-1:デフォルト)
	};
}

namespace Font
{
	std::vector<int> m_fontHandle;

	FontData data[] =
	{
		// Size96_4
		{"Tsunagi Gothic Black", 96, 4, -1},
		// Size64_4
		{"Tsunagi Gothic Black", 64, 4, -1},
		// Size48_4
		{"Tsunagi Gothic Black", 48, 4, -1},
		// Size42_4
		{"Tsunagi Gothic Black", 42, 4, -1},
		// Size40_4
		{"Tsunagi Gothic Black", 40, 4, DX_FONTTYPE_ANTIALIASING_EDGE_8X8},
		// Size28_4
		{"Tsunagi Gothic Black", 28, 4, -1},
		// Size24_4
		{"Tsunagi Gothic Black", 24, 4, -1},
		// Size16_4
		{"Tsunagi Gothic Black", 16, 4, -1},
		// Normal
		{"ＭＳ　ゴシック", 16, -1, -1},
	};


	/// <summary>
	/// フォントのロード
	/// </summary>
	void Font::Load()
	{
		Font::m_fontHandle.resize(static_cast<int>(Font::FontId::kNum));

		for (auto& fontPath : kFontDataPath)
		{
			if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {
			}
			else
			{
				// フォント読込エラー処理
				MessageBox(NULL, "フォント読込失敗", "", MB_OK);
			}
		}

		// フォントデータ生成
		for (int i = 0; i < Font::m_fontHandle.size(); i++)
		{
			Font::m_fontHandle[i] = CreateFontToHandle(data[i].name, data[i].size, data[i].thick, data[i].type);
		}
	}


	/// <summary>
	/// フォントのアンロード
	/// </summary>
	void Font::UnLoad()
	{
		for (auto& fontPath : kFontDataPath)
		{
			if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL))
			{
			}
			else
			{
				MessageBox(NULL, "フォント削除失敗", "", MB_OK);
			}
		}

		// フォントデータ削除
		for (const auto& handle : m_fontHandle)
		{
			DeleteFontToHandle(handle);
		}
	}
}
