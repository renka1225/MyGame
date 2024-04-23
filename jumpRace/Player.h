#pragma once
#include "DxLib.h"

class Input;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update(Input& input);
	void Draw();

	void Move();	// �v���C���[���ړ�������

	VECTOR GetPos() const { return m_pos; }

private:
	VECTOR m_pos;	// �ʒu
	int m_model;	// 3D���f��

private:	// �萔
	static constexpr float kScale = 0.5f;							// �v���C���[�̃T�C�Y
	static constexpr float kMove = -3.0f;							// �ړ���
	static constexpr float kInitPosX = 0.0f;						// �����ʒuX
	static constexpr float kInitPosY = 10.0f;						// �����ʒuY
	static constexpr float kInitPosZ = 100.0f;						// �����ʒuZ
};