#include "DxLib.h"
#include "Camera.h"
#include "Player.h"
#include "Stage.h"
#include "Input.h"
#include <cmath>

// �萔
namespace
{
	constexpr float kNear = 1.0f;							// �J�����̎�O�N���b�v����
	constexpr float kFar = 5000.0f;							// �J�����̉��N���b�v����
	constexpr float kDist = 150.0f;							// �J��������v���C���[�܂ł̋���
	constexpr float kHeight = 60.0f;						// �J�����̒����_
	constexpr float kAngle = 0.03f;							// �J�����𓮂����p�x
	constexpr float kInitAngleH = -DX_PI_F / 1.5f;			// �J�����̏������s�p�x
	constexpr float kInitAngleV = -0.3f;					// �J�����̏��������p�x
	constexpr float kMinAngleV = DX_PI_F * 0.5f - 0.6f;		// �ŏ��̐����p�x
	constexpr float kMaxAngleV = -DX_PI_F * 0.5f + 0.6f;	// �ő�̐����p�x
	constexpr float kColSize = 3.0f;						// �J�����̓����蔻��T�C�Y
	constexpr float kHitLength = 0.1f;						// �J�������X�e�[�W�ɓ������������肷�鋗��
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera():
	m_pos(VGet(0.0f, kHeight, 0.0f)),
	m_target(VGet(0.0f, 0.0f, 0.0f)),
	m_angleH(kInitAngleH),
	m_angleV(kInitAngleV)
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
	// �����Ȃ�
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

	// �J�����̍��W�����߂�
	// X���ɃJ��������v���C���[�܂ł̋������L�т��x�N�g���𐂒������ɉ�]����(Z����])
	m_pos = VTransform(VGet(-kDist, 0.0f, 0.0f), rotZ);
	// ��������(Y����])�ɉ�]����
	m_pos = VTransform(m_pos, rotY);
	// �����_�̍��W�𑫂�
	m_pos = VAdd(m_pos, m_target);

	// �����_����J�����̍��W�܂ł̊ԂɃX�e�[�W�̃|���S�������邩���ׂ�
	float notHitLength = 0.0f;	// �|���S���ɓ�����Ȃ�����
	float hitLength = kDist;	// �|���S���ɓ����鋗��

	do
	{
		// �J�������X�e�[�W�ɓ����邩�e�X�g���鋗��
		// ������Ȃ������Ɠ����鋗���̒��Ԃ����߂�
		float testLength = notHitLength + (hitLength - notHitLength) * 0.5f;
		// ���̃t���[���̃J�������W�����߂�
		auto nextPos = VTransform(VGet(-testLength, 0.0f, 0.0f), rotZ);
		nextPos = VTransform(nextPos, rotY);
		nextPos = VAdd(nextPos, m_target);

		// �V�������W�ŕǂɓ����邩�e�X�g����
		auto hitResult = MV1CollCheck_Capsule(stage.GetStageHandle(), -1, m_target, nextPos, kColSize);
		int hitNum = hitResult.HitNum;
		MV1CollResultPolyDimTerminate(hitResult);

		// ���������ꍇ
		if (hitNum != 0)
		{
			// �����鋗����testLenth�ɕύX����
			hitLength = testLength;
			// �J�������W���X�V
			m_pos = nextPos;
		}
		else
		{
			// ������Ȃ�������testLenth�ɕύX����
			notHitLength = testLength;
		}
	} while (hitLength - notHitLength > kHitLength); // hitLength��NoHitLength���\���ɋ߂Â��Ă��Ȃ��ꍇ���[�v����

}
