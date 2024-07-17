#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"

// �萔
namespace
{
	constexpr float kApproachRange = 70.0f;	// �v���C���[�ɋ߂Â��͈�
	constexpr int kStopMinTime = 30;		// �ŏ��̒�~����
	constexpr int kStopMaxTime = 150;		// �ő�̒�~����
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyBase::EnemyBase():
	m_isMove(false),
	m_isAttack(false),
	m_stopFrame(0),
	m_currentState(EnemyState::kFightIdle)
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBase::~EnemyBase()
{
}


/// <summary>
/// �ړ�����
/// </summary>
/// <param name="MoveVec"></param>
/// <param name="stage"></param>
void EnemyBase::Move(const VECTOR& moveVec, Player& player, Stage& stage)
{
	if (fabs(moveVec.x) > 0.0f || fabs(moveVec.z) > 0.0f)
	{
		m_isMove = true;
	}
	else
	{
		m_isMove = false;
	}

	// �����蔻����s���č��W��ۑ�����
	m_pos = stage.CheckEnemyCol(*this, moveVec);

	// �v���C���[�̍��W���X�V����
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// �ړ��p�����[�^��ݒ肷��
/// </summary>
/// <param name="player">�v���C���[�Q��</param>
/// <param name="upMoveVec">������ւ̈ړ��x�N�g��</param>
/// <param name="leftMoveVec">�������ւ̈ړ��x�N�g��</param>
/// <param name="moveVec">�ړ��x�N�g��</param>
/// <returns>���݂̏��</returns>
EnemyBase::EnemyState EnemyBase::UpdateMoveParameter(Player& player, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	EnemyState nextState = m_currentState;
	
	// ���̃t���[���ł̈ړ��x�N�g����������
	moveVec = VGet(0.0f, 0.0f, 0.0f);


	// �U�����łȂ��ꍇ
	if (!m_isAttack)
	{
		// �G�l�~�[�ƃv���C���[�̋������v�Z
		VECTOR dir = VSub(player.GetPos(), m_pos);
		float distance = VSize(dir);

		// �v���C���[����苗�����ꂽ�ꍇ
		if (distance > kApproachRange)
		{
			// ���b��������G�l�~�[���ړ�������
			if (m_stopFrame <= 0)
			{
				dir = VNorm(dir);
				moveVec = VScale(dir, m_moveSpeed);

				// �ҋ@��Ԃ̏ꍇ
				if (m_currentState == EnemyState::kFightIdle)
				{
					nextState = EnemyState::kRun; // �ړ���Ԃɂ���
				}
			}
			else
			{
				m_stopFrame--;
			}
		}
		else
		{
			m_stopFrame = kStopMinTime + GetRand(kStopMaxTime);	// ��~���Ԃ������_���Ōv�Z����
			nextState = EnemyState::kFightIdle;	// �ҋ@��Ԃɂ���
		}
	}

	return nextState;
}


/// <summary>
/// �G�̊p�x���X�V
/// </summary>
void EnemyBase::UpdateAngle(Player& player)
{
	// �G�̈ʒu����v���C���[�̈ʒu�̃x�N�g�������߂�
	VECTOR dir = VSub(player.GetPos(), m_pos);
	m_angle = atan2f(dir.x, dir.z);
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));
}


/// <summary>
///  �v���C���[�Ƃ̓����蔻����`�F�b�N����
/// </summary>
/// <param name="player">�v���C���[�Q��</param>
/// <param name="eCapPosTop">�����蔻��J�v�Z���̒��_�ʒu</param>
/// <param name="eCapPosBottom">�����蔻��J�v�Z���̒��_�ʒu</param>
/// <param name="eCapRadius">�����蔻��J�v�Z���̔��a</param>
void EnemyBase::CheckCollision(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius)
{

}
