#pragma once
#include "DxLib.h"

// ��2�N���X
class Sphere2
{
public:
	Sphere2();
	~Sphere2() {};
	void Draw();

	// ��2�̍��W���擾
	VECTOR GetPos() const { return m_pos; }

private:
	VECTOR m_pos;	// �\���ʒu
};

