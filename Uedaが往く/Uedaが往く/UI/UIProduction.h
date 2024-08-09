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
	// 操作説明を表示
	void DrawOperation();

private:
	int m_fightTextHandle;	// "Fight"のテキスト画像
	int m_numTextHandle;	// 数字の画像

	// ボタンの種類
	enum Button
	{
		kLSButton = 0,	// 左側のアナログスティック
		kRSButton = 1,	// 右側のアナログスティック
		kAButton = 4,	// Aボタン
		kBButton = 10,	// Bボタン
		kXButton = 2,	// Xボタン
		kYButton = 3,	// Yボタン
		kLBButton = 5,	// LBボタン
		kRBButton = 6,	// RBボタン
		kLineButton = 7,// 三本線ボタン
		kViewButton = 8,// ビューボタン 
		kButtonNum = 9	// ボタンの数
	};

};

