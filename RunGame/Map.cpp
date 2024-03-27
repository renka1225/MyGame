#include "Map.h"
#include "WorldSprite.h"
#include "PlatinumLoader.h"
#include <cassert>

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
Map::~Map()
{
	m_chips.clear();
}


/// <summary>
/// ������
/// </summary>
void Map::Init(const TCHAR* fmfFilePath)
{
	m_loader->Load(fmfFilePath);
	m_mapData.clear();

	std::vector<int> newColData;
	m_loader->GetMapSize(m_dataRowNum, m_dataColNum);		// �f�[�^�̍s�Ɨ�̒���������
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

	// �}�b�v�`��J�n�ʒu
	VECTOR chipLeftTopPos = VGet(0.0f, kChipNumY * kChipSize, 0.0f);
	for (int y = 0; y < kChipNumY; y++)
	{
		for(int x = 0; x < kChipNumX; x++)
		{
			auto sprite = std::make_shared<WorldSprite>();
			sprite->Init(m_mapHandle, kChipPixelSize, m_mapData[y][x]);
			VECTOR chipHalfOffset = VGet(-kChipSize * 0.5f, -kChipSize * 0.5f, 0);					// �}�b�v�`�b�v�̔����T�C�Y�����ɂ��炷�I�t�Z�b�g
			VECTOR chipPos = VAdd(VGet(x * kChipSize, (-y - 1) * kChipSize, 0), chipHalfOffset);	// �^�񒆃s�{�b�g�Ȃ̂Ń}�b�v�`�b�v�����T�C�Y���炷+�n�ʂȂ̂ň����
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
/// �X�V
/// </summary>
void Map::Update()
{
}


/// <summary>
/// �`��
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
	// �����܂ł���Ƃ������̓G���[�Ȃ̂ŃG���[�f����0,0�̕���Ԃ�
	assert(0 && "�f�[�^�͈͎w��G���[");
	return m_chips[0];
}