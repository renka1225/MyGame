#include "DrawDebug.h"


/// <summary>
/// コンストラクタ
/// </summary>
DrawDebug::DrawDebug()
{
}


/// <summary>
/// デストラクタ
/// </summary>
DrawDebug::~DrawDebug()
{
}


/// <summary>
/// 直方体の当たり判定描画
/// </summary>
/// <param name="pos">立方体の位置</param>
/// <param name="width">立方体の横幅</param>
/// <param name="height">立方体の縦幅</param>
/// <param name="depth">立方体の奥行き</param>
/// <param name="color">当たり判定の色</param>
void DrawDebug::DrawCubeCol(VECTOR pos, float width, float height, float depth, int color)
{
	//VECTOR pos1 = VSub(pos, VGet(width, height, depth));
	VECTOR pos1 = VGet(pos.x - width * 0.5f, pos.y + height * 0.5f, pos.z - depth * 0.5f);
	VECTOR pos2 = VGet(pos.x + width * 0.5f, pos.y - height * 0.5f, pos.z + depth * 0.5f);
	DrawCube3D(pos1, pos2, color, 0x000000, false);
}
