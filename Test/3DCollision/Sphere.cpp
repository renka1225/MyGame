#include "Sphere.h"
#include "Sphere2.h"
#include "Capsule2.h"
#include "Triangle.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Sphere::Sphere(std::shared_ptr<Sphere2> pSphere2, std::shared_ptr<Capsule2> pCapsule2, std::shared_ptr<Triangle> pTriangle):
	m_pSphere2(pSphere2),
	m_pCapsule2(pCapsule2),
	m_pTriangle(pTriangle),
	m_pos(VGet(-30.0f, 0.0f, 0.0f)),
	m_radius(kRadius),
	m_color(-1),
	m_isHit(false)
{
}


/// <summary>
/// �X�V
/// </summary>
void Sphere::Update()
{
	/*�����ړ�������*/
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT))
	{
		m_pos = VAdd(m_pos, VGet(2.0f, 0.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT))
	{
		m_pos = VAdd(m_pos, VGet(-2.0f, 0.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1))
	{
		m_pos = VAdd(m_pos, VGet(0.0f, 2.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_2))
	{
		m_pos = VAdd(m_pos, VGet(0.0f, -2.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP))
	{
		m_pos = VAdd(m_pos, VGet(0.0f, 0.0f, 2.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN))
	{
		m_pos = VAdd(m_pos, VGet(0.0f, 0.0f, -2.0f));
	}

	/*���Ƃ̓����蔻��*/
	//HitSphere();

	/*�J�v�Z���Ƃ̓����蔻��*/
	//HitCapsule();
	
	/*�O�p�`�Ƃ̓����蔻��*/
	//HitTriangle();
}


/// <summary>
/// �`��
/// </summary>
void Sphere::Draw()
{
	if (m_isHit)
	{
		m_color = 0xff0000;
	}
	else
	{
		m_color = 0x0000ff;
	}

	DrawSphere3D(m_pos, m_radius, 8, m_color, 0x000000, true);
}


/// <summary>
/// ���Ƌ��̓����蔻��
/// </summary>
void Sphere::HitSphere()
{
	// ��2�̍��W���擾
	VECTOR sphere2Pos = m_pSphere2->GetPos();

	// ���΃x�N�g��
	VECTOR v3Delta = VSub(m_pos, sphere2Pos);

	// �}�O�j�`���[�h
	float fDistanceSq = VSquareSize(v3Delta);

	// �����蔻��
	// ���ꂼ��̔��a�𑫂���2��
	if (fDistanceSq < (m_radius + 10.0f) * (m_radius + 10.0f))
	{
		m_isHit = true;
	}
	else
	{
		m_isHit = false;
	}
}


/// <summary>
/// ���ƃJ�v�Z���̓����蔻��
/// </summary>
void Sphere::HitCapsule()
{
	// �J�v�Z��2�̒��S���W���擾
	VECTOR capsule2Pos = m_pCapsule2->GetPos();
	// �J�v�Z��2�̐��ʃx�N�g�����擾
	VECTOR capsule2V3Dir = m_pCapsule2->GetDir();

	// ���΃x�N�g��
	// �I�_����n�_������
	VECTOR v3DeltaPos = VSub(capsule2Pos, m_pos);

	// �J�v�Z���̐��ʃx�N�g���Ƒ��΃x�N�g���̓���
	float dot = VDot(capsule2V3Dir, v3DeltaPos);

	// �J�v�Z���̐��ʃx�N�g���̃}�O�j�`���[�h
	float mag = VSquareSize(capsule2V3Dir);

	// t�͓_�Ɍ������@���x�N�g��(����)�����߂邽�߂̌W��
	float t = dot / mag;

	// �����Ɠ_�̋��������߂邽�߂�t�̐���
	if (t < -1.0f) t = -1.0f;   // t�̉���
	if (t > 1.0f) t = 1.0f;   // t�̏��

	// p = at + c(c:�����̒��_)�œ_�Ƃ̍ŒZ�����ɂȂ������̓_�̈ʒu�����߂�
	VECTOR v3MinPos = VAdd(VScale(capsule2V3Dir, t), capsule2Pos);   // �ŏ��ʒu��^������W

	// p�Ǝ����Ƃ̋����̃}�O�j�`���[�h
	float fDistSqr = VSquareSize(VSub(m_pos, v3MinPos));

	// �Փˋ����̌v�Z
	// ���̔��a�ƃJ�v�Z���̕��𑫂�
	float ar = kRadius + m_pCapsule2->GetRadius();

	// �����蔻��(2��̂܂ܔ�r)
	if (fDistSqr < ar * ar)
	{                       
		m_isHit = true;
	}
	else
	{
		// �[�̉~�̕����Ƃ̔���
		// �J�v�Z���̒[�̈ʒu���v�Z
		VECTOR capsule2Pos1 = m_pCapsule2->GetPos1();
		VECTOR capsule2Pos2 = m_pCapsule2->GetPos2();
		float distSqrToEnd1 = VSquareSize(VSub(m_pos, capsule2Pos1));
		float distSqrToEnd2 = VSquareSize(VSub(m_pos, capsule2Pos2));

		if (distSqrToEnd1 < ar * ar || distSqrToEnd2 < ar * ar)
		{
			m_isHit = true;
		}
		else
		{
			m_isHit = false;
		}
	}
}


/// <summary>
/// ���ƎO�p�`�̓����蔻��
/// </summary>
void Sphere::HitTriangle()
{
	VECTOR v3TriVec0, v3TriVec1, v3TriVec2;
	VECTOR v3HitVec0, v3HitVec1, v3HitVec2;
	float fCross0, fCross1, fCross2;
	
	// �O�p�`�T�C�N���x�N�g��
	v3TriVec0 = VSub(m_pTriangle->GetPos2(), m_pTriangle->GetPos1());
	v3TriVec1 = VSub(m_pTriangle->GetPos3(), m_pTriangle->GetPos2());
	v3TriVec2 = VSub(m_pTriangle->GetPos1(), m_pTriangle->GetPos3());

	// �O�p�`���_����^�[�Q�b�g�ւ̃x�N�g��
	v3HitVec0 = VSub(m_pos, m_pTriangle->GetPos1());
	v3HitVec1 = VSub(m_pos, m_pTriangle->GetPos2());
	v3HitVec2 = VSub(m_pos, m_pTriangle->GetPos3());

	// ���ꂼ��̊O��
	fCross0 = v3TriVec0.z * v3HitVec0.x - v3TriVec0.x * v3HitVec0.z;
	fCross1 = v3TriVec1.z * v3HitVec1.x - v3TriVec1.x * v3HitVec1.z;
	fCross2 = v3TriVec2.z * v3HitVec2.x - v3TriVec2.x * v3HitVec2.z;

	// �������Ă��邩�̃t���O�ϐ�
	bool bHit = false;

	// �S�ē������ɂ��邩�̔���
	if (fCross0 >= 0.0f)
	{
		if ((fCross1 >= 0.0f) && (fCross2 >= 0.0f))
		{
			bHit = true;
		}
	}
	else
	{
		if ((fCross1 < 0.0f) && (fCross2 < 0.0f))
		{
			bHit = true;
		}
	}

	// �������Ă������̏���
	if (bHit)
	{
		m_isHit = true;
	}
	else
	{
		m_isHit = false;
	}
}
