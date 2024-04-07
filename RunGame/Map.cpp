#include "Map.h"
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
	m_mapHandle = LoadGraph("data/background/water.png");	// �}�b�v�`�b�v�摜�ǂݍ���
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
	m_pLoader->GetMapSize(m_dataRowNum, m_dataColNum);		// �f�[�^�̍s�Ɨ�̒�������
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

	// WorldSprite���̐ݒ�ƈʒu������
	VECTOR chipLeftTopPos = VGet(0.0f, m_dataColNum * kChipScale, kChipPosZ);	// �}�b�v�̕`��J�n�ʒu�i����j
	for (int x = 0; x < m_dataColNum; x++)
	{
		for (int y = 0; y < m_dataRowNum; y++)
		{
			auto sprite = std::make_shared<WorldSprite>();
			sprite->Init(m_mapHandle, kChipPixelSize, m_mapData[x][y]);
			VECTOR chipHalfOffset = VGet(-kChipScale * 0.5f, -kChipScale * 0.5f, kChipPosZ);											// �}�b�v�`�b�v�̔����T�C�Y�����ɂ��炷�I�t�Z�b�g
			VECTOR chipPos = VAdd(VGet(y * kChipScale * 0.5f, (-x - 1) * kChipScale + kChipPosYAdjustment, kChipPosZ), chipHalfOffset);	// �^�񒆃s�{�b�g�Ȃ̂Ń}�b�v�`�b�v�����T�C�Y���炷+�n�ʂȂ̂ň����
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
		VECTOR DrawChipPos = VAdd(chip.pos, VGet(10.0f, 0.0f, 0.0f));
		if(!CheckCameraViewClip(DrawChipPos))
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
		// ��ʓ��̃}�b�v�`�b�v�̂ݏ���
		VECTOR DrawChipPos = VAdd(chip.pos, VGet(10.0f, 0.0f, 0.0f));
		if (!CheckCameraViewClip(DrawChipPos))
		{
			if (col == chip.col && row == chip.row)
			{
				return chip;
			}
		}
	}
	// MEMO:�G���[��
	assert(0 && "�f�[�^�͈͎w��G���[");
	return m_chips[0];
}