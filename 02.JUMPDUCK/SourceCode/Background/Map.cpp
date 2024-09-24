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
/// �z��ւ̃|�C���^��������ăx�N�^���쐬����
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
/// �R���X�g���N�^
/// </summary>
Map::Map(): 
	chipPos(VGet(0.0f, 0.0f, 0.0f)),
	chipGraph(-1)
{
	currentData.clear();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Map::~Map()
{
	sprites.clear();
}

/// <summary>
/// ���[�h
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

	// �}�b�v�`�b�v���[�h
	chipGraph = LoadGraph("data/background/water.png");

	// WorldSprite���̐ݒ�ƈʒu������
	VECTOR chipLeftTopPos = VGet(0.0f, dataColNum * ChipSize, 0.0f); // �}�b�v�̕`��J�n�ʒu�i����j
	for (int i = 0; i < dataColNum; i++)
	{
		for (int j = 0; j < dataRowNum; j++)
		{
			if (currentData[i][j] == 0) continue;

			auto sprite = new WorldSprite();
			sprite->Init(chipGraph, ChipPixelSize, currentData[i][j]);
			VECTOR chipHalfOffset = VGet(-Map::ChipSize * 0.5f, -Map::ChipSize * 0.5f, 0);			// �}�b�v�`�b�v�̔����T�C�Y�����ɂ��炷�I�t�Z�b�g
			chipPos = VAdd(VGet(j * Map::ChipSize, (-i - 1) * Map::ChipSize, 0), chipHalfOffset);	// �^�񒆃s�{�b�g�Ȃ̂Ń}�b�v�`�b�v�����T�C�Y���炷+�n�ʂȂ̂ň����
			chipPos = VAdd(chipPos, chipLeftTopPos);
			sprite->SetTransform(chipPos, Map::ChipSize);
			sprites.push_back(sprite);
		}
	}
}


/// <summary>
/// �`��
/// </summary>
void Map::Draw()
{
	for (const auto& sprite : sprites)
	{
		sprite->Draw();
	}
}