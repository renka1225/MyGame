#pragma once
#include "DxLib.h"
#include <memory>

class WorldSprite;

/// <summary>
/// �w�i�N���X
/// </summary>
class Background
{
public:
	Background();
	~Background();

	void Init();
	void Update();
	void Draw();

private:
	std::shared_ptr<WorldSprite> m_sprite;

	int m_background;	// �w�i�̉摜
	VECTOR m_pos;		// �w�i�̕\���ʒu

private:	// �萔
	static constexpr int kWidth = 2304;		// �摜�̉���
	static constexpr int kHeight = 1296;	// �摜�̏c��
	static constexpr float kScele = 100.0f;	// �摜�̊g�嗦
};

