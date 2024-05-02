#pragma once

/// <summary>
/// サウンド管理クラス
/// </summary>
class ManagerSound
{
public:
	ManagerSound();
	~ManagerSound();

	int GetSelectSE() const { return m_selectSE; }
	int GetDetermineSE() const { return m_determineSE; }
	int GetCountSE() const { return m_countSE; }
	int GetJumpSE() const { return m_jumpSE; }
	int GetMissSE() const { return m_missSE; }
	int GetTitleBgm() const { return m_titleBgm; }
	int GetPlayBgm() const { return m_playBgm; }
	int GetGameoverBgm() const { return m_gameoverBgm; }
	int GetClearBgm() const { return m_clearBgm; }

private:
	int m_selectSE;		// 選択時のSE
	int m_determineSE;	// 決定時のSE
	int m_countSE;		// スタートカウントのSE
	int m_jumpSE;		// ジャンプのSE
	int m_missSE;		// ボタン押しミス時のSE

	int m_titleBgm;		// タイトルBGM
	int m_playBgm;		// プレイ中BGM
	int m_gameoverBgm;	// ゲームオーバーBGM
	int m_clearBgm;		// クリアBGM
};

