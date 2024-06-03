#include "DrawDebug.h"

/// <summary>
/// グリッド表示
/// </summary>
void DrawDebug::DrawGrid()
{
	for (int x = -50; x <= 50; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -50), VGet(static_cast<float>(x), 0, 50), 0xffff00);
	}
	for (int z = -50; z <= 50; z += 10)
	{
		DrawLine3D(VGet(-50, 0, static_cast<float>(z)), VGet(50, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-の方向が分かりやすいように表示を追加する
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(-50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X-", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z-", 0xffffff);
	}
}


/// <summary>
/// プレイヤーの情報を描画
/// </summary>
/// <param name="pos">プレイヤーの座標</param>
void DrawDebug::DrawPlayerInfo(VECTOR pos)
{
	DrawFormatString(0, 20, 0xffffff, "Player座標(x:%f, y:%f, z:%f)", pos.x, pos.y, pos.z);
}


/// <summary>
/// 直方体の当たり判定を描画
/// </summary>
/// <param name="handle">モデルのハンドル</param>
void DrawDebug::DrawCubeCol(int handle, float angle, int color)
{
	// モデルの情報を取得
	VECTOR pos = MV1GetPosition(handle);		// 座標
	VECTOR scale = MV1GetScale(handle);			// サイズ
	VECTOR halfScale = VScale(scale, 0.5f);		// 半径

	VECTOR pos1 = VScale(VSub(pos, halfScale), angle);	// 左上手前の座標
	VECTOR pos2 = VScale(VAdd(pos, halfScale), angle);	// 右下奥の座標

	DrawCube3D(pos1, pos2, color, 0x000000, false);
}


// VECTOR pos, VECTOR scale, float angle, int color
//// 直方体の左上手前の座標を求める
//VECTOR pos1 = VGet(pos.x - scale.x * 0.5f, pos.y + scale.y * 0.5f, pos.z - scale.z * 0.5f);
//pos1 = VScale(pos1, angle);
//// 直方体の右下奥の座標を求める
//VECTOR pos2 = VGet(pos.x + scale.x * 0.5f, pos.y - scale.z * 0.5f, pos.z + scale.z * 0.5f);
//pos2 = VScale(pos2, angle);
//
//DrawCube3D(pos1, pos2, color, 0x000000, false);