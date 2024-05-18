#include "Capsule.h"
#include "Capsule2.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Capsule::Capsule(std::shared_ptr<Capsule2> pCapsule2):
	m_pCapsule2(pCapsule2),
	m_pos1(VGet(0.0f, 0.0f, 0.0f)),
	m_pos2(VGet(-30.0f, 0.0f, 10.0f)),
	m_centerPos(VScale(VAdd(m_pos1, m_pos2), 0.5f)),
	m_v3Direction(VSub(m_pos2, m_pos1)),
	m_radius(kRadius),
	m_color(-1),
	m_isHit(false)
{
}


/// <summary>
/// �X�V
/// </summary>
void Capsule::Update()
{
	/*�J�v�Z�����ړ�������*/
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT))
	{
		m_centerPos = VAdd(m_centerPos, VGet(2.0f, 0.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT))
	{
		m_centerPos = VAdd(m_centerPos, VGet(-2.0f, 0.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1))
	{
		m_centerPos = VAdd(m_centerPos, VGet(0.0f, 2.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_2))
	{
		m_centerPos = VAdd(m_centerPos, VGet(0.0f, -2.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP))
	{
		m_centerPos = VAdd(m_centerPos, VGet(0.0f, 0.0f, 2.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN))
	{
		m_centerPos = VAdd(m_centerPos, VGet(0.0f, 0.0f, -2.0f));
	}

	// �J�v�Z���̍��W���X�V
	m_pos1 = VSub(m_centerPos, VGet(0.0f, 0.0f, 0.0f));
	m_pos2 = VAdd(m_centerPos, VGet(-30.0f, 0.0f, 10.0f));

	/*�J�v�Z���Ƃ̓����蔻��*/
	HitCapsule();
}

/// <summary>
/// �`��
/// </summary>
void Capsule::Draw()
{
	if (m_isHit)
	{
		m_color = 0xff0000;
	}
	else
	{
		m_color = 0x0000ff;
	}

	// �J�v�Z����`��
	DrawCapsule3D(m_pos1, m_pos2, m_radius, 8, m_color, 0x000000, true);
}


/// <summary>
/// �J�v�Z���Ƃ̓����蔻��
/// </summary>
void Capsule::HitCapsule()
{
	// �v�Z�p�̕ϐ�
	float s,t;

	// �^�[�Q�b�g�Ǝ����̑��΃x�N�g�����쐬
	VECTOR v3DeltaPos = VSub(m_pCapsule2->GetPos(), m_centerPos);
	// �s��̊|���Z���ł���悤��4�ڂ̗v�f�𑝂₷
	VECTOR4 v4DeltaPos = { v3DeltaPos.x, v3DeltaPos.y, v3DeltaPos.z, 0.0f };

	// ���݂��̕����x�N�g���̊O�ς����Ė@���x�N�g�����o��
	VECTOR v3Normal = VCross(m_pCapsule2->GetDir(), m_v3Direction);

	// ���s��Ԃ��𔻒肷��
	bool bParallel = false;

	// �@���x�N�g���̑傫�����������菬�����ꍇ�A���s���
	if (VSquareSize(v3Normal) < 0.001f)
	{
		bParallel = true;
	}
	
	// ���s�����s�łȂ����̌v�Z
	if (!bParallel) // ���s�łȂ� 
	{
		// 4*4�̒P�ʍs����쐬
		MATRIX matSolve = MGetIdent();

		// �P�ʍs��ɐ��l������
		// 1���:�����̃x�N�g��
		matSolve.m[0][0] = m_v3Direction.x;
		matSolve.m[1][0] = m_v3Direction.y;
		matSolve.m[2][0] = m_v3Direction.z;
		matSolve.m[3][0] = 0.0f;

		// 2���:�^�[�Q�b�g�̕����x�N�g���𔽓]����������
		matSolve.m[0][1] = -m_pCapsule2->GetDir().x;
		matSolve.m[1][1] = -m_pCapsule2->GetDir().y;
		matSolve.m[2][1] = -m_pCapsule2->GetDir().z;
		matSolve.m[3][1] = 0.0f;

		// 3��:�݂��̖@���x�N�g��(�O��)
		matSolve.m[0][2] = v3Normal.x;
		matSolve.m[1][2] = v3Normal.y;
		matSolve.m[2][2] = v3Normal.z;
		matSolve.m[3][2] = 0.0f;

		// �t�s��ɂ���
		matSolve = MInverse(matSolve);

		// �s��̌v�Z
		// �s���擾
		VECTOR4 row0 = GetRow(matSolve, 0);
		VECTOR4 row1 = GetRow(matSolve, 1);

		// �p�����[�^s���o��
		s = VECTOR4Dot(row0, v4DeltaPos);
		// �p�����[�^t���o��
		t = VECTOR4Dot(row1, v4DeltaPos);
	}
	else // ���s
	{
		s = VDot(m_v3Direction, v3DeltaPos) / VSquareSize(m_v3Direction);
		t = VDot(m_pCapsule2->GetDir(), VScale(v3DeltaPos, -1)) / VSquareSize(m_pCapsule2->GetDir());
	}

	//�r����������
	if (s < 0.0f) s = 0.0f; // s�̉���
	if (s > 1.0f) s = 1.0f; // s�̏��
	if (t < 0.0f) t = 0.0f; // t�̉���
	if (t > 1.0f) t = 1.0f; // t�̏��

	// �T�C�Y�������ꂽ�����̕����x�N�g���Ǝ����̍��W�̑��΃x�N�g��(���Z)���o��
	VECTOR v3MinPos1 = VAdd(VScale(m_v3Direction, s), m_centerPos);
	// �T�C�Y�������ꂽ�^�[�Q�b�g�̕����x�N�g���ƃ^�[�Q�b�g�̍��W�̑��΃x�N�g��(���Z)���o��
	VECTOR v3MinPos2 = VAdd(VScale(m_pCapsule2->GetDir(), t), m_pCapsule2->GetPos());

	// ��L�̑��΃x�N�g���̃}�O�j�`���[�h
	float fDistSqr = VSquareSize(VSub(v3MinPos1, v3MinPos2));

	// �����ƃ^�[�Q�b�g�̔��a�̍��v
	float ar = m_pCapsule2->GetRadius() + m_radius;

	// ���΃x�N�g���Ɣ��a�̍��v�̔�r(�}�O�j�`���[�h�̂܂܌v�Z����)
	if (fDistSqr < ar * ar) // ���a�̍��v��菬������
	{
		if (!bParallel)
		{
			m_isHit = true;
		}
		else
		{
			m_isHit = false;
		}
	}
	else // ���a�̍��v���傫����
	{
		if (!bParallel)
		{
			m_isHit = false;
		}
		else
		{
			m_isHit = false;
		}
	}
}
