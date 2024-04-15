#include "DxLib.h"
#include <vector>

class WorldSprite;

/// <summary>
/// 2D�̔w�i�}�b�v
/// </summary>
class Map
{
public:
	Map();
	~Map();

	void Load();
	void Update();
	void Draw();

private:
	std::vector<WorldSprite*> sprites;

	// ���ׂ�`�b�v��
	std::vector<std::vector<int>> currentData;
	int dataColNum = 0;
	int dataRowNum = 0;

	VECTOR chipPos;

	int chipGraph;	// �}�b�v�`�b�v�摜

	// �}�b�v�`�b�v�̃T�C�Y
	static const float	ChipSize;
	static const int	ChipPixelSize;

private:
	static const int kColNum = 5;		// �}�b�v�s
	static const int kRowNum = 20;		// �}�b�v��
	static const int kMapData[kColNum][kRowNum];
};