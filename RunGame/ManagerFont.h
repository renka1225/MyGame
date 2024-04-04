#pragma once

/// <summary>
/// フォント管理クラス
/// </summary>
class ManagerFont
{
public:
	ManagerFont();
	~ManagerFont();

	// フォントを取得
	int GetFont() const { return m_fontHandle; }
	int GetTimeFont() const { return m_timeFontHandle; }
	int GetTextFont() const { return m_textFontHandle; }

private:
	int m_fontHandle;
	int m_textFontHandle;	// テキストのフォント
	int m_timeFontHandle;	// 時間経過のフォント
};

