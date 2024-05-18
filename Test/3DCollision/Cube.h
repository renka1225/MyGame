#pragma once
#include "DxLib.h"
#include <memory>

class Plane;

// ������1�N���X
class Cube
{
public:
	Cube(std::shared_ptr<Plane> pPlane);
	~Cube() {};
	void Update();
	void Draw();
	void HitPlane(); // �����̂ƕ��ʂ̓����蔻�� 

private:
	std::shared_ptr<Plane> m_pPlane;

	// ������1�̒��S�_
	VECTOR m_centerPos;
	// ������1�̕\���ʒu
	VECTOR m_pos1;
	VECTOR m_pos2;
	// ������1�̊p�x
	float m_angle;
	// �����̂̐F
	int m_color;
	// ����������
	bool m_isHit;

};

