#pragma once

/// <summary>
/// サウンド管理クラス
/// </summary>
class ManagerSound
{
public:
	ManagerSound();
	~ManagerSound();

	int GetCursorSE() const { return m_cursorSE; }
	int GetSelectSE() const { return m_selectSE; }
	int GetCountSE() const { return m_countSE; }
	int GetJumpSE() const { return m_jumpSE; }
	int GetMissSE() const { return m_missSE; }
	int GetClearSE() const { return m_clearSE; }
	int GetTitleBgm() const { return m_titleBgm; }
	int GetPlayBgm() const { return m_playBgm; }
	int GetClearStagingBgm() const { return m_clearStagingBgm; }
	int GetClearBgm() const { return m_clearBgm; }

private:
	int m_cursorSE;		// カーソル移動時のSE
	int m_selectSE;		// 選択時のSE
	int m_countSE;		// スタートカウントのSE
	int m_jumpSE;		// ジャンプのSE
	int m_missSE;		// ボタン押しミス時のSE
	int m_clearSE;		// クリア時のSE

	int m_titleBgm;			// タイトルBGM
	int m_playBgm;			// プレイ中BGM
	int m_clearStagingBgm;	// クリア演出中のBGM
	int m_clearBgm;			// クリアBGM
};

