#pragma once
#include "Bg.h"

class Bg;

/// <summary>
/// ステージ1の背景クラス
/// </summary>
class BgStage1 : public Bg
{
public:
	BgStage1();
	virtual ~BgStage1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	// 背景描画
	void DrawBg();
	// プレイヤーの位置からスクロール量を決定する
	int GetScrollX();
	int GetScrollY();
	// プレイヤーと当たっているか判定する
	bool IsColPlayer();
	// 指定した矩形と当たっているか判定する
	bool IsCollision(Rect rect, Rect& chipRect);
};