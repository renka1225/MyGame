#pragma once
#include "DxLib.h"
#include <memory>
#include <vector>

class ManagerModel;
class WorldSprite;

/// <summary>
/// �w�i�N���X
/// </summary>
class Background
{
public:
	Background(std::shared_ptr<ManagerModel> pModel);
	~Background();

	void Init();
	void Update();
	void Draw();

private:
	std::shared_ptr<ManagerModel> m_pModel;
	std::vector<std::shared_ptr<WorldSprite>> m_sprite;
	std::vector<int> m_bgHandle;	// �w�i�̉摜

	VECTOR m_bgPos;		// �w�i�̕\���ʒu
	VECTOR m_bg2Pos;	// �w�i2�̕\���ʒu
	float m_bgMove;		// �w�i�̈ړ���

	// �摜�T�C�Y
	struct Size
	{
		int width;
		int height;
	};

private:	// �萔
	static constexpr int kBgNum = 4;				// �w�i�摜�̐�
	static constexpr int kWidth = 576;				// �w�i�摜�̉���
	static constexpr int kHeight = 324;				// �w�i�摜�̏c��
	static constexpr float kBgPosY = 100.0f;		// �w�i�摜�̕\���ʒuY
	static constexpr float kBgPosZ = 30.0f;			// �w�i�摜�̕\���ʒuZ
	static constexpr float kBg2PosY = 90.0f;		// �w�i�摜2�̕\���ʒuY
	static constexpr float kBg2PosZ = 20.0f;		// �w�i�摜2�̕\���ʒuZ
	static constexpr float kBgScale = 250.0f;		// �w�i�摜�̊g�嗦
	static constexpr float kBg2Scale = 200.0f;		// �w�i�摜2�̊g�嗦
	static constexpr float kBgMove = 3.0f;			// �w�i�̈ړ���
};
