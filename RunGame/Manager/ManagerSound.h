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
	int GetStartCountSE() const { return m_startCountSE; }

private:
	int m_selectSE;		// 選択時のSE
	int m_determineSE;	// 決定時のSE
	int m_startCountSE;	// スタートカウントのSE

	int m_gameBgm;		// プレイ中のBGM
};

