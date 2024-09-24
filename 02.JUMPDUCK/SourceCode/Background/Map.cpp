#include<vector>
#include "Map.h"
#include "WorldSprite.h"

const int Map::kMapData[kColNum][kRowNum] =
{
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0 , 0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0 , 0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0},
	{ 8,  9, 10,  8,  9, 10,  8,  9, 10,  8,   9, 10,  8,  9, 10,  9, 10,  8,  9, 10,  8,  9,  10,  8,  9, 10,  8,  9, 10,   8,  9, 10,  8,  9,  10,  9, 10,  8,  9, 10,  8,  9, 10,  8,  9, 10,   8,  9, 10,  9, 10,  8,  9, 10}
};

const float Map::ChipSize = 12.0f;
const int Map::ChipPixelSize = 16;

/// <summary>
/// 配列へのポインタをもらってベクタを作成する
/// </summary>
std::vector<int> CreateArrayVector(const int targetData[], int num)
{
	std::vector<int> newVector;
	for (int i = 0; i < num; i++)
	{
		newVector.push_back(targetData[i]);
	}
	return newVector;
}

/// <summary>
/// コンストラクタ
/// </summary>
Map::Map(): 
	chipPos(VGet(0.0f, 0.0f, 0.0f)),
	chipGraph(-1)
{
	currentData.clear();
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{
	sprites.clear();
}

/// <summary>
/// ロード
/// </summary>
void Map::Load()
{
	currentData.clear();
	
	dataColNum = kColNum;
	dataRowNum = kRowNum;
	for (int i = 0; i < dataColNum; i++)
	{
		currentData.push_back(CreateArrayVector(kMapData[i], kRowNum));
	}

	// マップチップロード
	chipGraph = LoadGraph("data/background/water.png");

	// WorldSprite実体設定と位置初期化
	VECTOR chipLeftTopPos = VGet(0.0f, dataColNum * ChipSize, 0.0f); // マップの描画開始位置（左上）
	for (int i = 0; i < dataColNum; i++)
	{
		for (int j = 0; j < dataRowNum; j++)
		{
			if (currentData[i][j] == 0) continue;

			auto sprite = new WorldSprite();
			sprite->Init(chipGraph, ChipPixelSize, currentData[i][j]);
			VECTOR chipHalfOffset = VGet(-Map::ChipSize * 0.5f, -Map::ChipSize * 0.5f, 0);			// マップチップの半分サイズ左下にずらすオフセット
			chipPos = VAdd(VGet(j * Map::ChipSize, (-i - 1) * Map::ChipSize, 0), chipHalfOffset);	// 真ん中ピボットなのでマップチップ半分サイズずらす+地面なので一つ下に
			chipPos = VAdd(chipPos, chipLeftTopPos);
			sprite->SetTransform(chipPos, Map::ChipSize);
			sprites.push_back(sprite);
		}
	}
}


/// <summary>
/// 描画
/// </summary>
void Map::Draw()
{
	for (const auto& sprite : sprites)
	{
		sprite->Draw();
	}
}