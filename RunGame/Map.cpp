#include "Map.h"
#include "WorldSprite.h"
#include "PlatinumLoader.h"
#include <cassert>

/// <summary>
/// コンストラクタ
/// </summary>
Map::Map()
{
	m_mapHandle = LoadGraph("data/data/background/water.png");

	m_mapData.resize(kChipNumY);
	for (int y = 0; y < kChipNumY; ++y)
	{
		m_mapData[y].resize(kChipNumX);
	}
	m_loader = std::make_shared<PlatinumLoader>();
}


/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{
	m_chips.clear();
}


/// <summary>
/// 初期化
/// </summary>
void Map::Init(const TCHAR* fmfFilePath)
{
	m_loader->Load(fmfFilePath);
	m_mapData.clear();

	std::vector<int> newColData;
	m_loader->GetMapSize(m_dataRowNum, m_dataColNum);		// データの行と列の長さを入れる
	for (int i = 0; i < m_dataColNum; i++)
	{
		newColData.clear();
		for (int j = 0; j < m_dataRowNum; j++)
		{
			int spriteNo = m_loader->GetChipSpriteNo(LayerType::BackGround, j, i);
			newColData.push_back(spriteNo);
		}
		m_mapData.push_back(newColData);
	}

	// マップ描画開始位置
	VECTOR chipLeftTopPos = VGet(0.0f, kChipNumY * kChipSize, 0.0f);
	for (int y = 0; y < kChipNumY; y++)
	{
		for(int x = 0; x < kChipNumX; x++)
		{
			auto sprite = std::make_shared<WorldSprite>();
			sprite->Init(m_mapHandle, kChipPixelSize, m_mapData[y][x]);
			VECTOR chipHalfOffset = VGet(-kChipSize * 0.5f, -kChipSize * 0.5f, 0);					// マップチップの半分サイズ左下にずらすオフセット
			VECTOR chipPos = VAdd(VGet(x * kChipSize, (-y - 1) * kChipSize, 0), chipHalfOffset);	// 真ん中ピボットなのでマップチップ半分サイズずらす+地面なので一つ下に
			chipPos = VAdd(chipPos, chipLeftTopPos);
			sprite->SetTransform(chipPos, kChipSize);
			Chip chip;
			chip.pos = chipPos;
			chip.w = chip.h = kChipSize;
			chip.col = y;
			chip.row = x;
			chip.sprite = sprite;
			chip.chipKind = m_mapData[y][x];
			m_chips.push_back(chip);
		}
	}
}


/// <summary>
/// 更新
/// </summary>
void Map::Update()
{
}


/// <summary>
/// 描画
/// </summary>
void Map::Draw()
{
	for (const auto& chip : m_chips)
	{
		if (chip.chipKind > 0)
		{
			chip.sprite->Draw();
		}
	}
}


const Map::Chip& Map::GetChip(int col, int row) const
{
	for (const auto& chip : m_chips)
	{
		if (col == chip.col && row == chip.row)
		{
			return chip;
		}
	}
	// ここまでくるという事はエラーなのでエラー吐いて0,0の物を返す
	assert(0 && "データ範囲指定エラー");
	return m_chips[0];
}