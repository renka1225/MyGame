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
Map::Map():
	m_pCamera(nullptr)
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
	m_pLoader->GetMapSize(m_dataRowNum, m_dataColNum);		// �f�[�^�̍s�Ɨ�̒���������
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

	m_mapHandle = LoadGraph("data/background/water.png");	// �}�b�v�`�b�v�摜�ǂݍ���

	// WorldSprite���̐ݒ�ƈʒu������
	VECTOR chipLeftTopPos = VGet(0.0f, kChipNumY * kChipScale, 0.0f);	// �}�b�v�̕`��J�n�ʒu�i����j
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			auto sprite = std::make_shared<WorldSprite>();
			sprite->Init(m_mapHandle, kChipPixelSize, m_mapData[y][x]);
			VECTOR chipHalfOffset = VGet(-kChipScale * 0.5f, -kChipScale * 0.5f, 0.0f);				// �}�b�v�`�b�v�̔����T�C�Y�����ɂ��炷�I�t�Z�b�g
			VECTOR chipPos = VAdd(VGet(x * 7.0f, (-y - 1) * kChipScale, 0.0f), chipHalfOffset);		// �^�񒆃s�{�b�g�Ȃ̂Ń}�b�v�`�b�v�����T�C�Y���炷+�n�ʂȂ̂ň����
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
/// �X�V
/// </summary>
void Map::Update()
{
	// �����Ȃ�
}


/// <summary>
/// �`��
/// </summary>
void Map::Draw(std::shared_ptr<Camera> pCamera)
{
	// �J�����ʒu�擾
	m_pCamera = pCamera;
	VECTOR cameraPos = m_pCamera->GetPos();

	for (const auto& chip : m_chips)
	{
		// ���[���h���W����X�N���[�����W�ɕϊ�
		VECTOR chipScreenPos = ConvWorldPosToScreenPos(chip.pos);

		// ��ʓ��̃}�b�v�`�b�v�̂ݕ`�悷��
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
	// MEMO:�G���[��
	assert(0 && "�f�[�^�͈͎w��G���[");
	return m_chips[0];
}