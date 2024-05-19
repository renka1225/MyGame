#pragma once
#include "DxLib.h"
#include <memory>

class Cube2;
class Plane;

// ������1�N���X
class Cube
{
public:
	Cube(std::shared_ptr<Plane> pPlane, std::shared_ptr<Cube2> pCube2);
	~Cube() {};
	void Update();
	void Draw();
	void HitCube();	 // �����̂Ɨ����̂̓����蔻�� 
	void HitPlane(); // �����̂ƕ��ʂ̓����蔻�� 

private:
	std::shared_ptr<Cube2> m_pCube2;
	std::shared_ptr<Plane> m_pPlane;

	// ������1�̒��S�_
	VECTOR m_pos;
	// ������1�̃T�C�Y
	VECTOR m_scale;
	// ������1�̊p�x
	float m_angle;
	// ����������
	bool m_isHit;

	// �����̂�3D���f��
	int m_handle;
};

