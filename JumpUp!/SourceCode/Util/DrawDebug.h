#pragma once
#include "DxLib.h"
#include "Player.h"

class Player;

/// <summary>
/// デバック表示クラス
/// </summary>
class DrawDebug
{
public:
	// グリッド表示
	void DrawGrid();
	// プレイヤーの情報を描画
	void DrawPlayerInfo(VECTOR pos, Player::State state);
	// カメラの情報を描画
	void DrawCameraInfo(VECTOR pos, VECTOR target);
	// タイム表示
	void DrawTime(int frame);
};