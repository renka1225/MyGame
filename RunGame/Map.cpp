#include "Map.h"
#include "WorldSprite.h"
#include "PlatinumLoader.h"
#include "Camera.h"
#include "Game.h"
#include <cassert>


/// <summary>
/// コンストラクタ
/// </summary>
Map::Map()
{
	m_chips.clear();
	m_pLoader = std::make_shared<PlatinumLoader>();
	m_mapHandle = LoadGraph("data/background/water.png");	// マップチップ画像読み込み
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
	m_pLoader->Load(fmfFilePath);
	m_mapData.clear();

	std::vector<int> newColData;
	m_pLoader->GetMapSize(m_dataRowNum, m_dataColNum);		// データの行と列の長さを代入
	for (int x = 0; x < m_dataColNum; x++)
	{
		newColData.clear();
		for (int y = 0; y < m_dataRowNum; y++)
		{
			int spriteNo = m_pLoader->GetChipSpriteNo(LayerType::BackGround, y, x);
			newColData.push_back(spriteNo);
		}
		m_mapData.push_back(newColData);
	}

	// WorldSprite実体設定と位置初期化
	VECTOR chipLeftTopPos = VGet(0.0f, m_dataColNum * kChipScale, kChipPosZ);	// マップの描画開始位置（左上）
	for (int x = 0; x < m_dataColNum; x++)
	{
		for (int y = 0; y < m_dataRowNum; y++)
		{
			auto sprite = std::make_shared<WorldSprite>();
			sprite->Init(m_mapHandle, kChipPixelSize, m_mapData[x][y]);
			VECTOR chipHalfOffset = VGet(-kChipScale * 0.5f, -kChipScale * 0.5f, kChipPosZ);											// マップチップの半分サイズ左下にずらすオフセット
			VECTOR chipPos = VAdd(VGet(y * kChipScale * 0.5f, (-x - 1) * kChipScale + kChipPosYAdjustment, kChipPosZ), chipHalfOffset);	// 真ん中ピボットなのでマップチップ半分サイズずらす+地面なので一つ下に
			chipPos = VAdd(chipPos, chipLeftTopPos);
			sprite->SetTransform(chipPos, kChipScale);

			Chip chip;
			chip.pos = chipPos;
			chip.w = chip.h = kChipScale;
			chip.col = x;
			chip.row = y;
			chip.sprite = sprite;
			chip.chipKind = m_mapData[x][y];
			m_chips.push_back(chip);
		}
	}
}


/// <summary>
/// 更新
/// </summary>
void Map::Update()
{
	// 処理なし
}


/// <summary>
/// 描画
/// </summary>
void Map::Draw()
{
	for (const auto& chip : m_chips)
	{
		// 画面内のマップチップのみ描画する
		VECTOR DrawChipPos = VAdd(chip.pos, VGet(10.0f, 0.0f, 0.0f));
		if(!CheckCameraViewClip(DrawChipPos))
		{
			if (chip.chipKind == 0) continue;
			chip.sprite->Draw();
		}
	}
}


/// <summary>
/// 指定位置のマップチップを取得する
/// </summary>
/// <param name="col">y</param>
/// <param name="row">x</param>
/// <returns></returns>
const Map::Chip& Map::GetChip(int col, int row) const
{
	for (const auto& chip : m_chips)
	{
		// 画面内のマップチップのみ処理
		VECTOR DrawChipPos = VAdd(chip.pos, VGet(10.0f, 0.0f, 0.0f));
		if (!CheckCameraViewClip(DrawChipPos))
		{
			if (col == chip.col && row == chip.row)
			{
				return chip;
			}
		}
	}
	// MEMO:エラー時
	assert(0 && "データ範囲指定エラー");
	return m_chips[0];
}