#pragma once
#include "DxLib.h"

/// <summary>
/// ��
/// </summary>
class Sphere
{
public:
	Sphere();
	~Sphere();
	void Init();
	void Update();
	void Draw();

private:
	// ���Ƃ̓����蔻��
	void HitSphere();
	// �J�v�Z���Ƃ̓����蔻��
	void HitCupsule();

private:
	VECTOR m_pos;				// �ړ����鋅�̈ʒu
	VECTOR m_targetSpherePos;	// �����Ȃ����̈ʒu
	VECTOR m_cupsulePos1;		// �J�v�Z����1�߂̓_�̍��W
	VECTOR m_cupsulePos2;		// �J�v�Z����2�߂̓_�̍��W
	bool m_isHit;				// �������Ă��邩

	static constexpr float kRadius = 5.0f;	// ���a
	static constexpr int kDivNum = 32;

	static constexpr float kCupsuleRadius = 5.0f;	// �J�v�Z���̓����蔼�a
};

