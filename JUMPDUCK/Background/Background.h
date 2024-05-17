#pragma once
#include "DxLib.h"
#include <memory>

class ManagerModel;

/// <summary>
/// �w�i�N���X
/// </summary>
class Background
{
public:
	Background();
	~Background();

	void Init() {};
	void Update() {};
	void Draw();

private:
	// �\���ʒu
	VECTOR m_pos;
	VECTOR m_pos2;
	VECTOR m_pos3;

	// �w�i
	int m_background;
	int m_background2;
	int m_background3;
	int m_bg;

	// �摜�T�C�Y
	struct Size
	{
		int width;
		int height;
	};

private:	// �萔
	static constexpr float kBgScale = 1.2f;			// �w�i�摜�̃T�C�Y
	static constexpr float kBg2Scale = 1.0f;		// �w�i�摜�̃T�C�Y
	static constexpr float kBg3Scale = 0.9f;		// �w�i�摜�̃T�C�Y
	static constexpr float kBgMove = -0.1f;			// �w�i�̈ړ���

	// �w�i�̕`��ʒu
	static constexpr float kBgPosX = 50.0f;			// �Ŕw�ʂ�X���W
	static constexpr float kBg2PosX = 300.0f;		// 2�Ԗڂ�X���W
	static constexpr float kBg3PosX = -850.0f;		// �őO�ʂ�X���W
	static constexpr float kBgPosY = 50.0f;			// Y���W
	static constexpr float kBg3PosY = 55.0f;		// �őO�ʂ�Y���W
	static constexpr float kBgPosZ = 200.0f;		// �Ŕw�ʂ�Z���W
	static constexpr float kBg2PosZ = 150.0f;		// Z���W
	static constexpr float kBg3PosZ = 100.0f;		// �őO�ʂ�Z���W
};

