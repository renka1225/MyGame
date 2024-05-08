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
	VECTOR m_pos;		// �ړ����鋅�̈ʒu
	VECTOR m_targetPos;	// �����Ȃ����̈ʒu
	bool m_isHit;		// �������Ă��邩

	static constexpr float kRadius = 40.0f;	// ���a
	static constexpr int kDivNum = 32;
};

