#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "Game.h"

class SceneMain;

/// <summary>
/// 背景クラス
/// </summary>
class Bg
{
public:
	Bg(SceneMain* pMain);
	~Bg();

	void Init();
	void Update();
	void Draw();

	// プレイヤーの位置からスクロール量を決定する
	Vec2 GetScroll();

	// グラフィックの設定
	void SetHandle(int bgHandle) { m_bgHandle = bgHandle; }
	void SetMapHandle(int mapHandle) { m_mapHandle = mapHandle; }
	// マップチップ番号の取得
	int GetChipData(int x, int y) const { return m_chipData[y][x]; }
	// マップの当たり判定を取得する
 	Rect GetColRect(int x, int y) const { return m_colRect[y][x]; }

private:
	// マップチップの情報
	static constexpr int kChipWidth = 32;
	static constexpr int kChipHeight = 32;

	// チップを置く数
	static constexpr int kChipNumX = 80;
	static constexpr int kChipNumY = 23;

private:
	// シーンメインのポインタ
	SceneMain* m_pMain;

	// 背景のグラフィック
	int m_bgHandle;
	// マップチップのグラフィック
	int m_mapHandle;

	// 背景の表示位置
	Vec2 m_bgPos;

	// グラフィックに含まれるマップチップの数
	int m_graphChipNumX;
	int m_graphChipNumY;
	// マップチップの配置情報
	int m_chipData[kChipNumY][kChipNumX];

	// 各マップチップごとの当たり判定用の矩形
	Rect m_colRect[kChipNumY][kChipNumX];
};