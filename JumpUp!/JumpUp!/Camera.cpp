#include "DxLib.h"
#include "Camera.h"
#include "Player.h"
#include "Input.h"
#include <cmath>

// �萔
namespace
{
	constexpr float kNear = 1.0f;							// �J�����̎�O�N���b�v����
	constexpr float kFar = 1000.0f;							// �J�����̉��N���b�v����
	constexpr float kDist = 96.0f;							// �J�����̋���
	constexpr float kHeight = 40.0f;						// �J�����̒����_
	constexpr float kAngle = 0.03f;							// �J�����𓮂����p�x
	constexpr float kMinAngleV = DX_PI_F * 0.5f - 0.6f;		// �ŏ��̐����p�x
	constexpr float kMaxAngleV = -DX_PI_F * 0.5f + 0.6f;	// �ő�̐����p�x
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera():
	m_pos(VGet(0.0f, kHeight, 0.0f)),
	m_target(VGet(0.0f, 0.0f, 0.0f)),
	m_angleH(-DX_PI_F / 2),
	m_angleV(0.0f)
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
}


/// <summary>
/// ������
/// </summary>
void Camera::Init()
{
	SetCameraNearFar(kNear, kFar);
}


/// <summary>
/// �X�V
/// </summary>
void Camera::Update(Input& input, const Player& player, const Stage& stage)
{
	// ������
	if (input.IsPressing("rotateL"))
	{
		m_angleH -= kAngle;
	}
	// �E����
	if (input.IsPressing("rotateR"))
	{
		m_angleH += kAngle;
	}
	// �����
	if (input.IsPressing("rotateU"))
	{
		m_angleV -= kAngle;
		// ������p�x�ȏ�ɂȂ�Ȃ��悤�ɂ���
		m_angleV = std::max(m_angleV, kMaxAngleV);
	}
	// ������
	if (input.IsPressing("rotateD"))
	{
		m_angleV += kAngle;
		// ������p�x�ȉ��ɂȂ�Ȃ��悤�ɂ���
		m_angleV = std::min(kMinAngleV, m_angleV);
	}

	// �J�����̒����_��ݒ肷��
	m_target = VAdd(player.GetPos(), VGet(0.0f, kHeight, 0.0f));

	// �J�����ʒu�␳
	FixCameraPos(stage);
	SetCameraPositionAndTarget_UpVecY(m_pos, m_target);
}


/// <summary>
/// �J�����ʒu��␳����
/// </summary>
void Camera::FixCameraPos(const Stage& stage)
{
	// ���������̉�]
	auto rotY = MGetRotY(m_angleH);
	// ���������̉�]
	auto rotZ = MGetRotZ(m_angleV);

	// �J��������v���C���[�܂ł̋������Z�b�g����
	float cameraToPlayerLength = kDist;

	// �J�����̍��W�����߂�
	// 1.X���ɃJ��������v���C���[�܂ł̋������L�т��x�N�g���𐂒������ɉ�]����(Z����])
	// 2.��������(Y����])�ɉ�]����
	// 3.�����_�̍��W�𑫂�
	m_pos = VAdd(VTransform(VTransform(VGet(-cameraToPlayerLength, 0.0f, 0.0f), rotZ), rotY), m_target);

	// �����_����J�����̍��W�܂ł̊ԂɃX�e�[�W�̃|���S�������邩���ׂ�
	float notHitLength = 0.0f;				// �|���S���ɓ�����Ȃ�����
	float hitLength = cameraToPlayerLength;	// �|���S���ɓ����鋗��
	// �����邩�ǂ���
	float testLength = notHitLength + (hitLength - notHitLength) * 0.5f;
	// �e�X�g�p�̃J�������W���Z�o
	auto testPosition = VAdd(VTransform(VTransform(VGet(-testLength, 0.0f, 0.0f), rotZ), rotY), m_target);
}
