#include "Map.h"
#include "Player.h"
#include "WorldSprite.h"
#include "PlatinumLoader.h"
#include "Camera.h"
#include "Game.h"
#include <cassert>


/// <summary>
/// �R���X�g���N�^
/// </summary>
Map::Map()
{
	m_chips.clear();
	m_pLoader = std::make_shared<PlatinumLoader>();
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
	m_pLoader->Load(fmfFilePath);
	m_mapData.clear();

	std::vector<int> newColData;
	m_pLoader->GetMapSize(m_dataRowNum, m_dataColNum);		// �f�[�^�̍s�Ɨ�̒������擾
	for (int y = 0; y < m_dataRowNum; y++)
	{
		newColData.clear();
		for (int x = 0; x < m_dataColNum; x++)
		{
			int spriteNo = m_pLoader->GetChipSpriteNo(LayerType::BackGround, x, y);
			newColData.push_back(spriteNo);
		}
		m_mapData.push_back(newColData);
	}

	m_mapHandle = LoadGraph("data/background/1.png");	// �}�b�v�`�b�v�摜�ǂݍ���

	// WorldSprite���̐ݒ�ƈʒu������
	VECTOR chipLeftTopPos = VGet(0.0f, kChipNumY * kChipScale, kChipPosZ);	// �}�b�v�̕`��J�n�ʒu�i����j
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			auto sprite = std::make_shared<WorldSprite>();
			sprite->Init(m_mapHandle, kChipPixelSize, m_mapData[y][x]);
			VECTOR chipHalfOffset = VGet(-kChipScale * 0.5f, -kChipScale * 0.5f, kChipPosZ);							// �}�b�v�`�b�v�̔����T�C�Y�����ɂ��炷�I�t�Z�b�g
			VECTOR chipPos = VAdd(VGet(x * kChipScale * 0.5f, (-y - 1) * kChipScale, kChipPosZ), chipHalfOffset);	// �^�񒆃s�{�b�g�Ȃ̂Ń}�b�v�`�b�v�����T�C�Y���炷+�n�ʂȂ̂ň����
			chipPos = VAdd(chipPos, chipLeftTopPos);
			sprite->SetTransform(chipPos, kChipPixelSize);

			Chip chip;
			chip.pos = chipPos;
			chip.w = chip.h = kChipPixelSize;
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
	// �����Ȃ�
}


/// <summary>
/// �`��
/// </summary>
void Map::Draw()
{
	for (const auto& chip : m_chips)
	{
		// ��ʓ��̃}�b�v�`�b�v�̂ݕ`�悷��
		if(!CheckCameraViewClip(chip.pos))
		{
			if (chip.chipKind == 0) continue;
			chip.sprite->Draw();
		}
	}
}


/// <summary>
/// �w��ʒu�̃}�b�v�`�b�v���擾����
/// </summary>
/// <param name="col">y</param>
/// <param name="row">x</param>
/// <returns></returns>
const Map::Chip& Map::GetChip(int col, int row) const
{
	for (const auto& chip : m_chips)
	{
		if (col == chip.col && row == chip.row)
		{
			return chip;
		}
	}
	// MEMO:�G���[��
	assert(0 && "�f�[�^�͈͎w��G���[");
	return m_chips[0];
}