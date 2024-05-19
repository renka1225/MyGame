#include "Cube.h"
#include "Cube2.h"
#include "Plane.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Cube::Cube(std::shared_ptr<Plane> pPlane, std::shared_ptr<Cube2> pCube2):
	m_pPlane(pPlane),
	m_pCube2(pCube2),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_scale(VGet(0.05f, 0.05f, 0.05f)),
	m_angle(DX_PI_F / 180.0f),
	m_isHit(false)
{
	m_handle = MV1LoadModel("data/cube.mv1");

	MV1SetScale(m_handle, m_scale);
}


/// <summary>
/// �X�V
/// </summary>
void Cube::Update()
{
	/*�����̂��ړ�������*/
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

	// �\���ʒu�X�V
	MV1SetPosition(m_handle, m_pos);

	/*�����̂Ƃ̓����蔻��*/
	//HitCube();

	/*���ʂƂ̓����蔻��*/
	HitPlane();
}


/// <summary>
/// �`��
/// </summary>
void Cube::Draw()
{
	MV1DrawModel(m_handle);

	if (m_isHit)
	{
		DrawString(0, 0, "��������", 0xffffff);
	}
}


/// <summary>
/// �����̂Ɨ����̂̓����蔻��
/// </summary>
void Cube::HitCube()
{
	// �^�[�Q�b�g�Ƃ̑��΃x�N�g�������߂�
	VECTOR v3SubAbs = VSub(m_pos, m_pCube2->GetPos());

	// ���΃x�N�g�����΃x�N�g���ɒ���
	// ���ꂼ��̎���̑��΋����𐬕��Ɏ��x�N�g�����쐬
	v3SubAbs = VGet(abs(v3SubAbs.x), abs(v3SubAbs.y), abs(v3SubAbs.z));
	//v3SubAbs = VNorm(v3SubAbs);

	// ���ꂼ��̐�����ł̏Փˋ��������߂�
	// �Փˋ����͂��ꂼ��̑Ή������ӂ̒����𑫂���2�Ŋ���������
	VECTOR v3AddScale = VScale(VAdd(m_scale, m_pCube2->GetScale()), 0.5f);
	// �����蔻��͈̔͂��L����
	v3AddScale = VAdd(v3AddScale, VGet(14.0f, 14.0f, 14.0f));

	// �f�o�b�O�\��
	//DrawFormatString(0, 0, 0xffffff, "v3SubAbs.x:%f, v3SubAbs.y:%f, v3SubAbs.z:%f", v3SubAbs.x, v3SubAbs.y, v3SubAbs.z);
	//DrawFormatString(0, 30, 0xffffff, "v3AddScale.x:%f, v3AddScale.y:%f, v3AddScale.z:%f", v3AddScale.x, v3AddScale.y, v3AddScale.z);

	// �e�����̓����蔻��
	bool isXHit = v3SubAbs.x < v3AddScale.x;
	bool isYHit = v3SubAbs.y < v3AddScale.y;
	bool isZHit = v3SubAbs.z < v3AddScale.z;

	if (isXHit && isYHit && isZHit)
	{
		m_isHit = true;
	}
	else
	{
		m_isHit = false;
	}
}


/// <summary>
/// �����̂ƕ��ʂ̓����蔻��
/// </summary>
void Cube::HitPlane()
{
	// �O�ς̌v�Z
	// �O�ϋ��߂����ꂼ��̐������A�ʂ̕������̌W���ɂȂ�
	// ���ʂ̕����� : ax + by + cz + d = 0
	VECTOR v3Normal = VCross(m_pPlane->GetV3Vec1(), m_pPlane->GetV3Vec2());
	
	// �������������āAy���W���o�����ɂ���
	m_pos.y = (-v3Normal.x * m_pos.x - v3Normal.z * m_pos.z) / v3Normal.y + 5.0f;

	// ���߂��l��������
	m_pos = VGet(m_pos.x, m_pos.y, m_pos.z);


	/*�����̂��Ζʂɉ����ČX����*/
	// ���x�N�g���̍쐬
	// y��
	VECTOR v3Up = VCross(m_pPlane->GetV3Vec2(), m_pPlane->GetV3Vec1());
	// �P�ʃx�N�g���ɂ���
	v3Up = VNorm(v3Up);

	// z��(�^�[�Q�b�g����)
	VECTOR v3Forward = VGet(cosf(m_angle), 0.0f, sinf(m_angle));

	// x��
	VECTOR v3Side = VCross(v3Up, v3Forward);
	// �P�ʃx�N�g���ɂ���
	v3Side = VNorm(v3Side);

	// �x�N�g���𒼌�������
	v3Forward = VCross(v3Side, v3Up);
	v3Forward = VNorm(v3Forward);

	// z����y���̕������Z�b�g����
	MV1SetRotationZYAxis(m_handle, v3Forward, v3Up, m_angle);

	// �����̂̈ʒu���X�V
	MV1SetPosition(m_handle, m_pos);
}
