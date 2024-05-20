#pragma once
#include "DxLib.h"

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();

private:
	VECTOR m_pos;		// �v���C���[�ʒu
	VECTOR m_move;		// �ړ���
	int m_modelHandle;	// �v���C���[��3D���f��

private:
	static constexpr float kScale = 0.1f;	// �v���C���[���f���̊g�嗦
};

