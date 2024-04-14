#pragma once
#include "Rect.h"
#include "DxLib.h"
#include <vector>
#include <memory>

class WorldSprite;
class PlatinumLoader;

/// <summary>
/// マップ管理クラス
/// </summary>
class Map
{
public:
	Map();
	~Map();

	void Init(const TCHAR* fmfFilePath);
	void Update();
	void Draw();

	/// <summary>
	/// マップチップ構造体
	/// </summary>
	struct Chip
	{
		VECTOR pos;		// 座標
		float w, h;		// 幅、高さ
		int	col, row;	// 配置されている列、行
		int	chipKind;	// マップチップ種別
		std::shared_ptr<WorldSprite> sprite;
	};

	const Chip& GetChip(int col, int row) const;	// チップ数取得

	int GetMapColNum() const { return kChipNumX; }
	int GetMapRowNum() const { return kChipNumY; }

private:
	std::shared_ptr<PlatinumLoader> m_pLoader;	// マップデータ読み込みのポインタ
	std::vector<std::vector<int>> m_mapData;	// マップデータ
	std::vector<Chip> m_chips;					// マップチップ

	int m_dataColNum;	// 縦のチップ数
	int m_dataRowNum;	// 横のチップ数

	int m_mapHandle;	// マップの画像

private:	// 定数
	static constexpr int kChipPixelSize = 32;	// マップチップのサイズ
	static constexpr float kChipScale = 20.0f;	// マップチップの拡大率
	// チップを置く数
	static constexpr int kChipNumX = 10;
	static constexpr int kChipNumY = 2;
	// マップチップ情報
	static constexpr float kChipPosZ = 0.0f;			// マップチップのZ座標
};