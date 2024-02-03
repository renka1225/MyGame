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
	int GetFont2() const { return m_fontHandle2; }
	int GetFont3() const { return m_fontHandle3; }
	int GetFontStaging() const { return m_fontStaging; }

private:
	int m_fontHandle;
	int m_fontHandle2;
	int m_fontHandle3;
	int m_fontStaging; // 演出用のフォント
};

