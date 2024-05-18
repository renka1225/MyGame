#include "Cube.h"
#include "Plane.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Cube::Cube(std::shared_ptr<Plane> pPlane):
	m_pPlane(pPlane),
	m_centerPos(VGet(0.0f, 0.0f, 0.0f)),
	m_pos1(VAdd(m_centerPos, VGet(-10.0f, 0.0f, 0.0f))),
	m_pos2(VAdd(m_centerPos, VGet(0.0f, 10.0f, 10.0f))),
	m_angle(DX_PI_F / 180.0f),
	m_color(-1),
	m_isHit(false)
{
}


/// <summary>
/// �X�V
/// </summary>
void Cube::Update()
{
	/*�����̂��ړ�������*/
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

	// �\���ʒu�X�V
	m_pos1 = VAdd(m_centerPos, VGet(-10.0f, 0.0f, 0.0f));
	m_pos2 = VAdd(m_centerPos, VGet(0.0f, 10.0f, 10.0f));

	/*���ʂƂ̓����蔻��*/
	HitPlane();
}


/// <summary>
/// �`��
/// </summary>
void Cube::Draw()
{
	if (m_isHit)
	{
		m_color = 0xff0000;
	}
	else
	{
		m_color = 0x0000ff;
	}

	DrawCube3D(m_pos1, m_pos2, m_color, 0x000000, true);
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
	m_centerPos.y = (-v3Normal.x * m_centerPos.x - v3Normal.z * m_centerPos.z) / v3Normal.y + 0.5f;

	// ���߂��l��������
	m_centerPos = VGet(m_centerPos.x, m_centerPos.y, m_centerPos.z);

	////  �Ζʂɍ��킹�����W��Ԃɕϊ��ł�����x�N�g���̍쐬
	//// �ϊ����y��
	//VECTOR v3Up = VCross(m_pPlane->GetV3Vec2(), m_pPlane->GetV3Vec1());
	//// �ϊ����z��
	//VECTOR v3Forward = VGet(cosf(m_angle), 0.0f, sinf(m_angle));
	//// �ϊ����x��
	//VECTOR v3Side = VCross(v3Up, v3Forward);
	//v3Forward = VCross(v3Side, v3Up);

	// �����̂��Ζʂɉ����ČX����
	MATRIX matRotation = MGetIdent();
	//matRotation.m[0][0] = v3Side.x;
	//matRotation.m[1][0] = v3Side.y;
	//matRotation.m[2][0] = v3Side.z;
	//matRotation.m[0][1] = v3Up.x;
	//matRotation.m[1][1] = v3Up.y;
	//matRotation.m[2][1] = v3Up.z;
	//matRotation.m[0][2] = v3Forward.x;
	//matRotation.m[1][2] = v3Forward.y;
	//matRotation.m[2][2] = v3Forward.z;
}
