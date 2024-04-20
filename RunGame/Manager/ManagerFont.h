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
	int GetStartCountFont() const { return m_startCountFontHandle; }
	int GetTimeFont() const { return m_timeFontHandle; }
	int GetTextFont() const { return m_textFontHandle; }
	int GetCreditFont() const { return m_creditFontHandle; }

private:
	int m_fontHandle;
	int m_startCountFontHandle;	// スタートカウントのフォント
	int m_textFontHandle;		// テキストのフォント
	int m_timeFontHandle;		// 時間経過のフォント
	int m_creditFontHandle;		// クレジットのフォント
};

