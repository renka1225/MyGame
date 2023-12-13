#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "Game.h"

/// <summary>
/// 背景クラス
/// </summary>
class Bg
{
public:
	Bg();
	~Bg();

	void Init();
	void Update();
	void Draw();

	// グラフィックの設定
	void SetHandle(int bgHandle) { m_bgHandle = bgHandle; }
	void SetMapHandle(int mapHandle) { m_mapHandle = mapHandle; }

	// 当たり判定の取得
	 Rect GetColRect() const { return m_colRect[kChipNumY - 1][kChipNumX - 1]; }

	// マップチップ番号の取得
	int GetChipData();

private:
	// マップチップの情報
	static constexpr int kChipWidth = 32;
	static constexpr int kChipHeight = 32;

	// チップを置く数
	static constexpr int kChipNumX = Game::kScreenWidth / kChipWidth;
	static constexpr int kChipNumY = Game::kScreenHeight / kChipHeight;

private:
	// 背景のグラフィック
	int m_bgHandle;
	// マップチップのグラフィック
	int m_mapHandle;

	// 背景の表示位置
	Vec2 m_pos;

	// グラフィックに含まれるマップチップの数
	int m_graphChipNumX;
	int m_graphChipNumY;
	// マップチップの配置情報
	int m_chipData[kChipNumY][kChipNumX];

	// 各マップチップごとの当たり判定用の矩形
	Rect m_colRect[kChipNumY][kChipNumX];
};