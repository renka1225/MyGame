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
	int GetCount3SE() const { return m_count3SE; }
	int GetCount2SE() const { return m_count2SE; }
	int GetCount1SE() const { return m_count1SE; }
	int GetNoticeSE() const { return m_noticeSE; }
	int GetJumpSE() const { return m_jumpSE; }
	int GetTitleBgm() const { return m_titleBgm; }
	int GetPlayBgm() const { return m_playBgm; }
	int GetGameoverBgm() const { return m_gameoverBgm; }
	int GetClearBgm() const { return m_clearBgm; }

private:
	int m_selectSE;		// 選択時のSE
	int m_determineSE;	// 決定時のSE

	// スタートカウントのSE
	int m_count3SE;
	int m_count2SE;
	int m_count1SE;


	int m_noticeSE;		// 通知表示時のSE
	int m_jumpSE;		// ジャンプのSE

	int m_titleBgm;		// タイトルBGM
	int m_playBgm;		// プレイ中BGM
	int m_gameoverBgm;	// ゲームオーバーBGM
	int m_clearBgm;		// クリアBGM
};

