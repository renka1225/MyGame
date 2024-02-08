#pragma once
#include "Bg.h"

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
	virtual int GetScrollX() override;
	virtual int GetScrollY() override;
	// プレイヤーと当たっているか判定する
	virtual bool IsColPlayer() override;
	// 指定した矩形と当たっているか判定する
	virtual bool IsCollision(Rect rect, Rect& chipRect) override;
};