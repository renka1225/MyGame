#pragma once
#include "DxLib.h"
#include <memory>

class Capsule2;

// �J�v�Z��1�N���X
class Capsule
{
public:
	Capsule(std::shared_ptr<Capsule2> pCapsule2);
	~Capsule() {};
	void Update();
	void Draw();
	void HitCapsule();	// �J�v�Z���ƃJ�v�Z���̓����蔻��

private:
	std::shared_ptr<Capsule2> m_pCapsule2;

	// �J�v�Z�����`�������_���̈�_�̍��W
	VECTOR m_pos1;
	VECTOR m_pos2;
	// �J�v�Z���̒��S�_
	VECTOR m_centerPos;
	// �����x�N�g��
	VECTOR m_v3Direction;
	// �J�v�Z���̕�
	float m_radius;
	// �J�v�Z���̐F
	int m_color;
	// ���̐F
	bool m_isHit;

	// VECTOR4�̍\����
	struct VECTOR4
	{
		float x, y, z, w;
	};

	// VECTOR4�̐ς��v�Z
	float VECTOR4Dot(VECTOR4 a, VECTOR4 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	// �s��̍s���擾����
	VECTOR4 GetRow(MATRIX mat, int row)
	{
		return VECTOR4{ mat.m[row][0], mat.m[row][1], mat.m[row][2], mat.m[row][3] };
	}

private:
	static constexpr float kRadius = 10.0f;	// �J�v�Z���̕�
};

