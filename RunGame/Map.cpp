#include "Map.h"
#include "Player.h"
#include "WorldSprite.h"
#include "PlatinumLoader.h"
#include "Camera.h"
#include "Game.h"
#include <cassert>


/// <summary>
/// コンストラクタ
/// </summary>
Map::Map():
	m_pCamera(nullptr)
{
	m_chips.clear();
	m_pLoader = std::make_shared<PlatinumLoader>();
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
	m_pLoader->GetMapSize(m_dataRowNum, m_dataColNum);		// データの行と列の長さを入れる
	for (int i = 0; i < m_dataColNum; i++)
	{
		newColData.clear();
		for (int j = 0; j < m_dataRowNum; j++)
		{
			int spriteNo = m_pLoader->GetChipSpriteNo(LayerType::BackGround, j, i);
			newColData.push_back(spriteNo);
		}
		m_mapData.push_back(newColData);
	}

	m_mapHandle = LoadGraph("data/background/water.png");	// マップチップ画像読み込み

	// WorldSprite実体設定と位置初期化
	VECTOR chipLeftTopPos = VGet(0.0f, kChipNumY * kChipScale, 0.0f);	// マップの描画開始位置（左上）
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			auto sprite = std::make_shared<WorldSprite>();
			sprite->Init(m_mapHandle, kChipPixelSize, m_mapData[y][x]);
			VECTOR chipHalfOffset = VGet(-kChipScale * 0.5f, -kChipScale * 0.5f, 0.0f);				// マップチップの半分サイズ左下にずらすオフセット
			VECTOR chipPos = VAdd(VGet(x * 7.0f, (-y - 1) * kChipScale, 0.0f), chipHalfOffset);		// 真ん中ピボットなのでマップチップ半分サイズずらす+地面なので一つ下に
			chipPos = VAdd(chipPos, chipLeftTopPos);
			sprite->SetTransform(chipPos, kChipScale);

			Chip chip;
			chip.pos = chipPos;
			chip.w = chip.h = kChipScale;
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
	// 処理なし
}


/// <summary>
/// 描画
/// </summary>
void Map::Draw(std::shared_ptr<Camera> pCamera)
{
	// カメラ位置取得
	m_pCamera = pCamera;
	VECTOR cameraPos = m_pCamera->GetPos();

	for (const auto& chip : m_chips)
	{
		// ワールド座標からスクリーン座標に変換
		VECTOR chipScreenPos = ConvWorldPosToScreenPos(chip.pos);

		// 画面内のマップチップのみ描画する
		if (chip.pos.x >= cameraPos.x - Game::kScreenWidth * 0.5f &&
			chip.pos.x <= cameraPos.x + Game::kScreenWidth * 0.5f)
		{
			if (chip.chipKind == 0) continue;
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
	// MEMO:エラー時
	assert(0 && "データ範囲指定エラー");
	return m_chips[0];
}