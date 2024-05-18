#pragma once
#include "DxLib.h"

// ���ʃN���X
class Plane
{
public:
	Plane();
	~Plane() {};
	void Update();
	void Draw();

	// ���ʂ�X�����̌X�΂��擾
	VECTOR GetV3Vec1() const { return m_v3Vec1; }
	// ���ʂ�Y�����̌X�΂��擾
	VECTOR GetV3Vec2() const { return m_v3Vec2; }

private:
	// ���_�f�[�^
	VERTEX3D Vertex[4];
	WORD Index[6];

	// X�����̌X��
	VECTOR m_v3Vec1;
	// Y�����̌X��
	VECTOR m_v3Vec2;

	// �o�ߎ���
	int m_time;
	// �\���摜
	int m_handle;
};