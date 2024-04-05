#pragma once
#include "Rect.h"
#include "DxLib.h"
#include <vector>
#include <memory>

class WorldSprite;
class PlatinumLoader;
class Camera;
class Player;

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
	void Draw(std::shared_ptr<Camera> pCamera);

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

	const Chip& GetChip(int col, int row) const;

	int GetMapColNum() const { return kChipNumX; }
	int GetMapRowNum() const { return kChipNumY; }

private:
	std::shared_ptr<PlatinumLoader> m_pLoader;	// マップデータ読み込みのポインタ
	std::shared_ptr<Camera> m_pCamera;			// カメラのポインタ
	std::vector<std::vector<int>> m_mapData;	// マップデータ
	std::vector<Chip> m_chips;					// マップチップ

	int m_mapHandle;	// マップの画像

	int m_dataColNum = 0;
	int m_dataRowNum = 0;

private:	// 定数
	static constexpr int kChipPixelSize = 16;	// マップチップのサイズ
	static constexpr float kChipScale = 15.0f;	// マップチップの拡大率
	// チップを置く数
	static constexpr int kChipNumX = 10;
	static constexpr int kChipNumY = 10;
	static constexpr int kMapcChipNum = kChipNumX * kChipNumY;
	// マップチップ情報
	static const int kMapData[kChipNumX][kChipNumY];
	static constexpr float kChipPosZ = 0.0f;	// マップチップの位置
};