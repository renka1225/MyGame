#pragma once

/// <summary>
/// サウンド管理クラス
/// </summary>
class ManagerSound
{
public:
	ManagerSound();
	~ManagerSound();

	int GetStartCountSE() const { return m_startCountSE; }

private:
	int m_gameBgm;		// プレイ中のBGM
	int m_selectSE;		// 選択時のSE

	int m_startCountSE;	// スタートカウントのSE
};

