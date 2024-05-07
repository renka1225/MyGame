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
	int GetTimeFont() const { return m_timeFontHandle; }
	int GetTimeFontEdge() const { return m_timeFontEdge; }
	int GetResultFont() const { return m_resultFontHandle; }
	int GetResultTimeFont() const { return m_resultTimeFontHandle; }
	int GetCreditFont() const { return m_creditFontHandle; }

private:
	int m_textFontHandle;		// テキストのフォント
	int m_textFont2Handle;		// テキストのフォント
	int m_timeFontHandle;		// 時間経過のフォント
	int m_timeFontEdge;			// 時間経過のフォントエッジ
	int m_resultFontHandle;		// 結果表示のフォント
	int m_resultTimeFontHandle;	// 結果タイムのフォント
	int m_creditFontHandle;		// クレジット表記のフォント
};

