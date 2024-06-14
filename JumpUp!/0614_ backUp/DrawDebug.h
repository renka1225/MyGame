#pragma once
#include "DxLib.h"

/// <summary>
/// デバック表示クラス
/// </summary>
class DrawDebug
{
public:
	// グリッド表示
	void DrawGrid();
	// プレイヤーの情報を描画
	void DrawPlayerInfo(VECTOR pos);
	// 直方体の当たり判定を描画
	void DrawCubeCol(int handle, float angle, int color);
};