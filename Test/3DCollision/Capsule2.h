#pragma once
#include "DxLib.h"

// �J�v�Z��2�N���X
class Capsule2
{
public:
	Capsule2();
	~Capsule2() {};
	void Draw();

	// �J�v�Z��2�̎n�_���擾
	VECTOR GetPos1() const { return m_pos1; }
	// �J�v�Z��2�̏I�_���擾
	VECTOR GetPos2() const { return m_pos2; }
	// �J�v�Z��2�̕����x�N�g�����擾
	VECTOR GetDir() const { return m_v3Direction; }
	//�J�v�Z��2�̒��S�_���擾
	VECTOR GetPos() const { return m_centerPos; }
	// �J�v�Z��2�̕����擾
	float GetRadius() const { return m_radius; }

private:
	// �J�v�Z�����`�������_���̈�_�̍��W
	VECTOR m_pos1;
	VECTOR m_pos2;
	// �����x�N�g��
	VECTOR m_v3Direction;
	// �J�v�Z���̒��S�_
	VECTOR m_centerPos;
	// �J�v�Z���̕�
	float m_radius;

private:
	static constexpr float kRadius = 10.0f;	// �J�v�Z���̕�
};

