#include "WorldSprite.h"


/// <summary>
/// 初期化
/// </summary>
/// <param name="textureGraph">テクスチャの画像ハンドル</param>
/// <param name="width">画像の横幅</param>
/// <param name="height">画像の縦幅</param>
/// <param name="spriteNo">スプライト番号</param>
void WorldSprite::Init(int textureGraph, int width, int height, int spriteNo)
{
	this->textureGraph = textureGraph;

	// 4頂点分のuvデータを設定
	int texW, texH;
	GetGraphTextureSize(textureGraph, &texW, &texH);
	int chipNumX = texW / width;
	int chipNoX = spriteNo % chipNumX;
	int chipNumY = texH / height;
	int chipNoY = spriteNo % chipNumY;
	float URate = 1.0f / static_cast<float>(chipNumX); // テクスチャ全部を1.0とした時のuのサイズ
	float VRate = 1.0f / static_cast<float>(chipNumY); // テクスチャ全部を1.0とした時のvのサイズ
	Vertex[0].u = (chipNoX + 0.0f) * URate;
	Vertex[0].v = (chipNoY + 0.0f) * VRate;
	Vertex[1].u = (chipNoX + 1.0f) * URate;
	Vertex[1].v = (chipNoY + 0.0f) * VRate;
	Vertex[2].u = (chipNoX + 0.0f) * URate;
	Vertex[2].v = (chipNoY + 1.0f) * VRate;
	Vertex[3].u = (chipNoX + 1.0f) * URate;
	Vertex[3].v = (chipNoY + 1.0f) * VRate;

	// ディフューズ、スペキュラは初期化時に固定
	for (int i = 0; i < 4; i++)
	{
		Vertex[i].dif = GetColorU8(255, 255, 255, 255);
		Vertex[i].spc = GetColorU8(0, 0, 0, 0);

		// 回転をサポートしないのでノーマルも固定
		Vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
		// 補助テクスチャをサポートしないのでuv固定
		Vertex[i].su = 0.0f;
		Vertex[i].sv = 0.0f;
	}

	// ２ポリゴン分のインデックスデータをセット
	Index[0] = 0;
	Index[1] = 1;
	Index[2] = 2;
	Index[3] = 3;
	Index[4] = 2;
	Index[5] = 1;
}


/// <summary>
/// サイズとポジションに応じて4頂点分の頂点座標を調整する
/// </summary>
/// <param name="pos">ポジション</param>
/// <param name="spriteSize">配置するワールドスプライトのサイズ</param>
void WorldSprite::SetTransform(const VECTOR& pos, float spriteSize)
{
	this->pos = pos;
	// ピボット中心で設定
	Vertex[0].pos = VScale(VGet(-2.0f, 1.0f, 0.0f), spriteSize * 0.5f);
	Vertex[1].pos = VScale(VGet(2.0f, 1.0f, 0.0f), spriteSize * 0.5f);
	Vertex[2].pos = VScale(VGet(-2.0, -1.0f, 0.0f), spriteSize * 0.5f);
	Vertex[3].pos = VScale(VGet(2.0f, -1.0f, 0.0f), spriteSize * 0.5f);
	for (int i = 0; i < 4; i++)
	{
		Vertex[i].pos = VAdd(Vertex[i].pos, pos);
	}
}


/// <summary>
/// 描画
/// </summary>
void WorldSprite::Draw()
{
	DrawPolygonIndexed3D(Vertex, 4, Index, 2, textureGraph, true);
}
