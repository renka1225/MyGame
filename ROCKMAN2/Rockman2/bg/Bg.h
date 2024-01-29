#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "Game.h"

class Player;
/// <summary>
/// 背景クラス
/// </summary>
class Bg
{
public:
	Bg();
	virtual ~Bg();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	// プレイヤーの位置からスクロール量を決定する
	int GetScrollX();
	int GetScrollY();

	// プレイヤーのポインタを設定
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	// プレイヤーと当たっているか判定する
	bool IsColPlayer();
	// 指定した矩形と当たっているか判定する
	bool IsCollision(Rect rect, Rect& chipRect);

protected:
	// プレイヤーのポインタ
	Player* m_pPlayer;

	// 背景のグラフィック
	int m_bgHandle;
	// マップチップのグラフィック
	int m_mapHandle;

	// 背景の表示位置
	Vec2 m_bgPos;

	// グラフィックに含まれるマップチップの数
	int m_graphChipNumX;
	int m_graphChipNumY;
};