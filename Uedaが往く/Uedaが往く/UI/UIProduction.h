#pragma once

/// <summary>
/// 演出関連のUI
/// </summary>
class UIProduction
{
public:
	UIProduction();
	~UIProduction();
	void Update();
	// スタート時の演出を表示
	void DrawStartProduction(int time, int matchNum, int maxMatch);

private:
	int m_fightTextHandle;	// "Fight"のテキスト画像
	int m_numTextHandle;	// 数字の画像
};

