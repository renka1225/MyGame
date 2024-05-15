#pragma once
#include "DxLib.h"

// �J�v�Z��2�N���X
class Capsule2
{
public:
	Capsule2();
	~Capsule2() {};
	void Draw();

	//�J�v�Z��2�̒��S�_���擾
	VECTOR GetPos() const { return m_centerPos; }
	// �J�v�Z��2�̕����x�N�g�����擾
	VECTOR GetDir() const { return m_v3Direction; }

private:
	// �J�v�Z�����`�������_���̈�_�̍��W
	VECTOR m_pos1;
	VECTOR m_pos2;
	// �J�v�Z���̒��S�_
	VECTOR m_centerPos;

	// �����x�N�g��
	VECTOR m_v3Direction;
};

