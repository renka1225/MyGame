#pragma once
#include "DxLib.h"

/// <summary>
/// デバック表示クラス
/// </summary>
class DrawDebug
{
public:
	DrawDebug();
	~DrawDebug();
	// 直方体の当たり判定を描画
	void DrawCubeCol(VECTOR pos, float width, float height, float depth, int color);
};

