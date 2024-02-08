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

	virtual void Init() = 0;
	virtual	void Update() = 0;
	virtual void Draw() = 0;

	// プレイヤーの位置からスクロール量を決定する
	virtual int GetScrollX() = 0;
	virtual int GetScrollY() = 0;
	// プレイヤーと当たっているか判定する
	virtual bool IsColPlayer() = 0;
	// 指定した矩形と当たっているか判定する
	virtual bool IsCollision(Rect rect, Rect& chipRect) = 0;

	// プレイヤーのポインタを設定
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

protected:
	// プレイヤーのポインタ
	Player* m_pPlayer;

	// 背景の表示位置
	Vec2 m_bgPos;
	// 背景の移動量
	float m_bgMove;

	// グラフィックに含まれるマップチップの数
	int m_graphChipNumX;
	int m_graphChipNumY;

	// 背景のグラフィック
	int m_bgHandle;	
	int m_bg2Handle;
	int m_bg3Handle;
	int m_bg4Handle;

	// マップチップのグラフィック
	int m_mapHandle;

	// 画像サイズ
	struct Size
	{
		int width;
		int height;
	};
};