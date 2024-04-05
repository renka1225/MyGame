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
/// �}�b�v�Ǘ��N���X
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
	/// �}�b�v�`�b�v�\����
	/// </summary>
	struct Chip
	{
		VECTOR pos;		// ���W
		float w, h;		// ���A����
		int	col, row;	// �z�u����Ă����A�s
		int	chipKind;	// �}�b�v�`�b�v���
		std::shared_ptr<WorldSprite> sprite;
	};

	const Chip& GetChip(int col, int row) const;

	int GetMapColNum() const { return kChipNumX; }
	int GetMapRowNum() const { return kChipNumY; }

private:
	std::shared_ptr<PlatinumLoader> m_pLoader;	// �}�b�v�f�[�^�ǂݍ��݂̃|�C���^
	std::shared_ptr<Camera> m_pCamera;			// �J�����̃|�C���^
	std::vector<std::vector<int>> m_mapData;	// �}�b�v�f�[�^
	std::vector<Chip> m_chips;					// �}�b�v�`�b�v

	int m_mapHandle;	// �}�b�v�̉摜

	int m_dataColNum = 0;
	int m_dataRowNum = 0;

private:	// �萔
	static constexpr int kChipPixelSize = 16;	// �}�b�v�`�b�v�̃T�C�Y
	static constexpr float kChipScale = 15.0f;	// �}�b�v�`�b�v�̊g�嗦
	// �`�b�v��u����
	static constexpr int kChipNumX = 10;
	static constexpr int kChipNumY = 10;
	static constexpr int kMapcChipNum = kChipNumX * kChipNumY;
	// �}�b�v�`�b�v���
	static const int kMapData[kChipNumX][kChipNumY];
	static constexpr float kChipPosZ = 0.0f;	// �}�b�v�`�b�v�̈ʒu
};