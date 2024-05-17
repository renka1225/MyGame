#include "DxLib.h"
#include <vector>

class WorldSprite;

/// <summary>
/// 2Dの背景マップ
/// </summary>
class Map
{
public:
	Map();
	~Map();

	void Load();
	void Update() {};
	void Draw();

private:
	std::vector<WorldSprite*> sprites;

	// 並べるチップ数
	std::vector<std::vector<int>> currentData;
	int dataColNum = 0;
	int dataRowNum = 0;

	VECTOR chipPos;

	int chipGraph;	// マップチップ画像

	// マップチップのサイズ
	static const float	ChipSize;
	static const int	ChipPixelSize;

private:
	static const int kColNum = 5;		// マップ行
	static const int kRowNum = 60;		// マップ列
	static const int kMapData[kColNum][kRowNum];
};