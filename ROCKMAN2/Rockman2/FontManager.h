#pragma once

/// <summary>
/// フォント管理クラス
/// </summary>
class FontManager
{
public:
	FontManager();
	~FontManager();

	// フォントを取得
	int GetFont() const { return m_fontHandle; }

private:
	int m_fontHandle;
};

