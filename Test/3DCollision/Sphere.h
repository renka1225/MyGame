#pragma once
#include "DxLib.h"
#include <memory>

class Sphere2;
class Capsule2;

// ��1�N���X
class Sphere
{
public:
	Sphere(std::shared_ptr<Sphere2> pSphere2, std::shared_ptr<Capsule2> pCapsule2);
	~Sphere() {};
	void Update();
	void Draw();
	void HitSphere();	// ���Ƌ��̓����蔻��
	void HitCapsule();	// ���ƃJ�v�Z���̓����蔻��

private:
	std::shared_ptr<Sphere2> m_pSphere2;
	std::shared_ptr<Capsule2> m_pCapsule2;

	// ��1�̕\���ʒu
	VECTOR m_pos;
	// ��1�̔��a
	float m_radius;
	// ���̐F
	int m_color;
	// ����������
	bool m_isHit;

private:
	static constexpr float kRadius = 10.0f;	// ���̔��a
};

