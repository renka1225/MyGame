#include "Sphere.h"

Sphere::Sphere() :
	m_pos(VGet(200.0f, 100.0f, 0.0f)),
	m_targetPos(VGet(500.0f, 300.0f, 0.0f))
{
}

Sphere::~Sphere()
{
}

void Sphere::Init()
{
}

void Sphere::Update()
{
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_pos.x += 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		m_pos.x -= 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		m_pos.y += 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		m_pos.y -= 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		m_pos.z += 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_Z))
	{
		m_pos.z -= 10.0f;
	}

	// ���΃x�N�g�����v�Z
	VECTOR v3Delta = VSub(m_pos, m_targetPos);
	// �}�O�j�`���[�h
	float fDistanceSq = v3Delta.x * v3Delta.x + v3Delta.y * v3Delta.y + v3Delta.z * v3Delta.z;

	// �����蔻��
	// �}�O�j�`���[�h�����a��2�斢���̏ꍇ�������Ă�
	if (fDistanceSq < (kRadius * kRadius * 4))
	{
		m_isHit = true;
	}
	else
	{
		m_isHit = false;
	}
}

void Sphere::Draw()
{
	//����`�悷��
	DrawSphere3D(m_targetPos, kRadius, kDivNum, 0xffffff, 0xffffff, true);

	// �������Ă��鎞�͋��̐F��ς���
	int color = 0x0000ff;
	if (m_isHit)
	{
		color = 0xff0000;
	}

	DrawSphere3D(m_pos, kRadius, kDivNum, color, 0xffffff, true);
}
