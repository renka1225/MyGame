#pragma once
#include "DxLib.h"

/// <summary>
/// スプライト表示
/// </summary>
class WorldSprite
{
public:
	void Init(int textureGraph, int width, int height, int spriteNo);
	void SetTransform(const VECTOR& pos, float spriteSize);
	void Draw();

private:
	int	textureGraph;	// スプライトを作成する画像
	VECTOR pos;			// 描画ポジション
	VERTEX3D Vertex[4];	// 頂点バッファ
	WORD Index[6];		// インデックスバッファ
};

