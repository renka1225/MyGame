#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "Game.h"
#include "Bg.h"

class Bg;

/// <summary>
/// 背景クラス
/// </summary>
class BgStage2 : public Bg
{
public:
	BgStage2();
	virtual ~BgStage2();

	virtual void Init () override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void DrawBg() override;

	// プレイヤーの位置からスクロール量を決定する
	int GetScrollX();
	int GetScrollY();
	// プレイヤーと当たっているか判定する
	bool IsColPlayer();
	// 指定した矩形と当たっているか判定する
	bool IsCollision(Rect rect, Rect& chipRect);
};