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
	int GetTextFont() const { return m_textFontHandle; }
	int GetTextFont2() const { return m_textFont2Handle; }
	int GetStartCountFont() const { return m_startCountFontHandle; }
	int GetTimeFont() const { return m_timeFontHandle; }
	int GetResultTimeFont() const { return m_resultTimeFontHandle; }
	int GetCreditFont() const { return m_creditFontHandle; }

private:
	int m_textFontHandle;		// テキストのフォント
	int m_textFont2Handle;		// テキストのフォント
	int m_startCountFontHandle;	// スタートカウントのフォント
	int m_timeFontHandle;		// 時間経過のフォント
	int m_resultTimeFontHandle;	// 結果タイムのフォント
	int m_creditFontHandle;		// クレジット表記のフォント
};

