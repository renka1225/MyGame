#include "Sphere.h"
#include <cmath>

Sphere::Sphere() :
	m_pos(VGet(200.0f, 100.0f, 0.0f)),
	m_targetSpherePos(VGet(500.0f, 300.0f, 0.0f)),
	m_cupsulePos1(VGet(800.0f, 100.0f, 0.0f)),
	m_cupsulePos2(VGet(900.0f, 200.0f, 10.0f)),
	m_isHit(false)
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

	// ���Ƃ̓����蔻��
	HitSphere();
	// �J�v�Z���Ƃ̓����蔻��
	//HitCupsule();
}

void Sphere::Draw()
{
	// ����`�悷��
	DrawSphere3D(m_targetSpherePos, kRadius, kDivNum, 0xffffff, 0xffffff, true);
	// �J�v�Z����`�悷��
	DrawCapsule3D(m_cupsulePos1, m_cupsulePos2, kCupsuleRadius, 8, 0xffffff, 0xffffff, true);

	// �������Ă��鎞�͋��̐F��ς���
	int color = 0x0000ff;
	if (m_isHit)
	{
		color = 0xff0000;
	}

	DrawSphere3D(m_pos, kRadius, kDivNum, color, 0xffffff, true);
}


/// <summary>
/// ���Ƃ̓����蔻��
/// </summary>
void Sphere::HitSphere()
{
	// ���΃x�N�g�����v�Z
	VECTOR v3Delta = VSub(m_pos, m_targetSpherePos);
	// �}�O�j�`���[�h
	float fDistanceSq = v3Delta.x * v3Delta.x + v3Delta.y * v3Delta.y + v3Delta.z * v3Delta.z;

	// �}�O�j�`���[�h�����a��2�斢���̏ꍇ�������Ă�
	if (fDistanceSq < ((kRadius + kRadius) * (kRadius + kRadius)))
	{
		m_isHit = true;
	}
	else
	{
		m_isHit = false;
	}
}


/// <summary>
/// �J�v�Z���Ƃ̓����蔻��
/// </summary>
void Sphere::HitCupsule()
{
	// �_1����_2�Ɍ������P�ʃx�N�g�����v�Z
	VECTOR direction = VSub(m_cupsulePos2, m_cupsulePos1);

	// �_1���狅�̒��S�ւ̑��΃x�N�g�����v�Z
	VECTOR v3Delta = VSub(m_pos, m_cupsulePos1);

	// �Փ˂��镨�̂̐��ʃx�N�g���Ƒ��΃x�N�g���̓��ς����߂�
	// �_1����_2�����ɋ��̒��S���琂�������낵�����̓_�����߂���
	float dot = VDot(direction, v3Delta);

	// �Փ˕��̂̐��ʃx�N�g���̃}�O�j�`���[�h
	float mag = VSize(v3Delta);

	// �_�Ɍ������@���x�N�g��(����)�����߂�
	float t = dot / mag;

	// �����Ɠ_�̋��������߂邽�߂�t�̐���
	if (t < -1.0f) t = -1.0f; // t�̉���
	if (t > 1.0f) t = 1.0f;   // t�̏��

	// p = at + c(c:�����̒��_)�œ_�Ƃ̍ŒZ�����ɂȂ�J�v�Z����̓_�̈ʒu�����߂�
	//VECTOR v3MinPos = VAdd(VGet(cupsulePos.x * t, cupsulePos.y * t, cupsulePos.z * t), cupsulePos);   // �ŏ��ʒu��^������W
	direction = VGet(direction.x * t, direction.y * t, direction.z * t);
	VECTOR v3MinPos = VAdd(m_pos, direction);   // �ŏ��ʒu��^������W

	// p�Ƌ��Ƃ̋����̃}�O�j�`���[�h
	float fDistSqr = VSize(VSub(v3MinPos, m_pos));

	// �Փˋ����̌v�Z
	float ar = kRadius + kCupsuleRadius;

	// �����蔻��(2��̂܂ܔ�r)
	if (fDistSqr < (ar * ar))
	{
		m_isHit = true;
	}
	else
	{
		m_isHit = false;
	}
}
