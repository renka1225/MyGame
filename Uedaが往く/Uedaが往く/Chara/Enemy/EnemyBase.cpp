#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"

// �萔
namespace
{
	constexpr float kApproachRange = 70.0f;	 // �v���C���[�ɋ߂Â��͈�
	constexpr float kAttackRange = 100.0f;	 // �v���C���[���U������͈�
	constexpr int kStopMinTime = 30;		 // �ŏ��̒�~����
	constexpr int kStopMaxTime = 150;		 // �ő�̒�~����

	constexpr int kMaxProb = 100;			 // �ő�m��%
	constexpr int kChangeAngleProb = 30;	 // �p�x���X�V����m��%
	constexpr int kChangeAngleFrame = 30;	 // �p�x���X�V����t���[����

	// �A�j���[�V�������
	constexpr float kAnimBlendMax = 1.0f;	 // �A�j���[�V�����u�����h�̍ő�l
	constexpr float kAnimBlendSpeed = 0.2f;	 // �A�j���[�V�����u�����h�̕ω����x
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyBase::EnemyBase():
	m_isMove(false),
	m_isAttack(false),
	m_stopFrame(0),
	m_angleFrame(0),
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

	// �X�e�[�W�Ɠ����蔻����s���č��W��ۑ�����
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
		// �v���C���[���U���͈͂ɓ������ꍇ
		else if(distance <= kAttackRange)
		{
			nextState = EnemyState::kKick;	// �U����Ԃɂ���
		}
		else
		{
			m_stopFrame = kStopMinTime + GetRand(kStopMaxTime);	// ��~���Ԃ������_���Ōv�Z����
			nextState = EnemyState::kFightIdle;	// �ҋ@��Ԃɂ���
		}

		DrawFormatString(0, 160, 0xffffff, "%f", distance);
	}

	return nextState;
}


/// <summary>
/// �U������
/// </summary>
/// <param name="input">���͏��</param>
/// <returns>���݂̏��</returns>
EnemyBase::EnemyState EnemyBase::Attack()
{
	EnemyState nextState = m_currentState;

	// TODO:�����_���ōU�����s��
	if (!m_isAttack && m_currentState != EnemyState::kRun)
	{
		int randNum = GetRand(kMaxProb);
		
		// �p���`�U��
		if (randNum <= 30)
		{
			m_isAttack = true;
			nextState = EnemyState::kPunch;
			PlayAnim(AnimKind::kPunch);
		}
		// �L�b�N�U��
		else if(randNum <= 60)
		{
			m_isAttack = true;
			nextState = EnemyState::kKick;
			PlayAnim(AnimKind::kKick);
		}
	}

	return nextState;
}


/// <summary>
/// �G�̊p�x���X�V
/// </summary>
void EnemyBase::UpdateAngle(Player& player)
{
	m_angleFrame++;

	// �G�̈ʒu����v���C���[�ʒu�܂ł̃x�N�g�������߂�
	VECTOR dir = VSub(player.GetPos(), m_pos);

	// ��莞�Ԃ�������G�l�~�[�̊p�x���X�V����
	if (m_angleFrame >= kChangeAngleFrame)
	{
		// �����_���Ńv���C���[�̕���������
		int randNum = GetRand(kMaxProb);
		if (randNum <= kChangeAngleProb)
		{
			m_angle = atan2f(dir.x, dir.z);
		}
		m_angleFrame = 0;
	}

	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));
}


/// <summary>
/// �v���C���[�Ƃ̓����蔻����`�F�b�N����
/// </summary>
/// <param name="player">�v���C���[�Q��</param>
/// <param name="eCapPosTop">�����蔻��J�v�Z���̒��_�ʒu</param>
/// <param name="eCapPosBottom">�����蔻��J�v�Z���̒��_�ʒu</param>
/// <param name="eCapRadius">�����蔻��J�v�Z���̔��a</param>
void EnemyBase::CheckHitPlayerCol(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius)
{
	// �v���C���[�ƓG�̓����蔻����s��
	bool hit = HitCheck_Capsule_Capsule(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius, eCapPosTop, eCapPosBottom, eCapRadius);
	// �p���`
	bool hitPunch = HitCheck_Capsule_Capsule(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius, eCapPosTop, eCapPosBottom, eCapRadius);
	// �L�b�N
	bool hitKick = HitCheck_Capsule_Capsule(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius, eCapPosTop, eCapPosBottom, eCapRadius);

	// �v���C���[�ƃG�l�~�[�̈ʒu�x�N�g�������߂�
	VECTOR pToEVec = VSub(m_pos, player.GetPos());
	pToEVec = VNorm(pToEVec);
	// �w�ォ��U��������
	bool isBackAttack = VDot(player.GetDir(), pToEVec) < 0.0f;

	// �p���`�����������ꍇ
	if (hitPunch && m_currentState == EnemyState::kPunch)
	{
		// �v���C���[���K�[�h���Ă��Ȃ����A�w�ォ��U�������ꍇ
		if (isBackAttack || !player.GetIsGuard())
		{
			player.OnDamage(m_status.punchPower);
		}
		else
		{
			player.OnDamage(0.0f);
		}
	}
	// �L�b�N�����������ꍇ
	else if (hitKick && m_currentState == EnemyState::kKick)
	{
		// �L�b�N�����������ꍇ
		if (player.GetIsGuard())
		{
			player.OnDamage(m_status.kickPower);
		}
		else
		{
			player.OnDamage(0.0f);
		}
	}
	// �U�����łȂ��A�v���C���[�ɓ��������ꍇ
	else if (hit)
	{
		// �G�l�~�[�̈ʒu��␳����
		VECTOR collisionNormal = VSub(m_pos, player.GetPos());
		collisionNormal = VNorm(collisionNormal);

		const float kAdj = 1.0f;
		m_pos = VAdd(m_pos, VScale(collisionNormal, kAdj));
	}

	// �݂͂����܂�Ȃ������ꍇ
	if (!hit && m_currentState == EnemyState::kGrab)
	{
		// �͂ݎ��s�̃A�j���[�V�������Đ�����
	}
}


/// <summary>
/// �A�j���[�V�����X�e�[�g�̍X�V
/// </summary>
/// <param name="prevState"></param>
void EnemyBase::UpdateAnimState(EnemyState prevState)
{
	// �U�����͏�Ԃ��X�V���Ȃ�
	if (m_isAttack) return;

	// �ҋ@��Ԃ���
	if (prevState == EnemyState::kFightIdle)
	{
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kPunch)PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kKick)	PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// �ړ���Ԃ���
	else if (prevState == EnemyState::kRun)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kPunch) PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// �p���`��Ԃ���
	else if (prevState == EnemyState::kPunch)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kRun) PlayAnim(AnimKind::kRun);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// �L�b�N��Ԃ���
	else if (prevState == EnemyState::kKick)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kPunch) PlayAnim(AnimKind::kPunch);
		// ����A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// �����Ԃ���
	else if (prevState == EnemyState::kAvoid)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kPunch) PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kKick) PlayAnim(AnimKind::kKick);
	}
}


/// <summary>
/// �A�j���[�V��������
/// </summary>
void EnemyBase::UpdateAnim()
{
	float animTotalTime; // �Đ����̃A�j���[�V��������

	// �u�����h����1�ȉ��̏ꍇ
	if (m_animBlendRate < kAnimBlendMax)
	{
		m_animBlendRate += kAnimBlendSpeed;
		if (m_animBlendRate >= kAnimBlendMax)
		{
			m_animBlendRate = kAnimBlendMax;
		}
	}

	// ���ݍĐ����̃A�j���[�V�����̏���
	if (m_currentPlayAnim != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_currentPlayAnim);
		if (m_isAttack)
		{
			m_currentAnimCount += m_animSpeed.punch;
		}
		else
		{
			m_currentAnimCount += m_animSpeed.fightIdle;
		}

		// �A�j���[�V�����̍Đ����Ԃ����[�v
		if (m_currentAnimCount > animTotalTime)
		{
			// �U���A�j���[�V�������I��������ҋ@��ԂɈڍs
			if (m_isAttack)
			{
				m_isAttack = false;
				m_currentState = EnemyState::kFightIdle;
				PlayAnim(AnimKind::kFightIdle);
			}

			m_currentAnimCount = static_cast<float>(fmod(m_currentAnimCount, animTotalTime));
		}

		// �Đ����Ԃ��X�V
		MV1SetAttachAnimTime(m_modelHandle, m_currentPlayAnim, m_currentAnimCount);
		// �A�j���[�V�����̃u�����h����ݒ肷��
		MV1SetAttachAnimBlendRate(m_modelHandle, m_currentPlayAnim, m_animBlendRate);


	}

	// 1�O�ɍĐ����Ă����A�j���[�V�����̏���
	if (m_prevPlayAnim != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_prevPlayAnim);
		if (m_isAttack)
		{
			m_prevAnimCount += m_animSpeed.punch;
		}
		else
		{
			m_prevAnimCount += m_animSpeed.fightIdle;
		}

		// �A�j���[�V�����̍Đ����Ԃ����[�v
		if (m_prevPlayAnim > animTotalTime)
		{
			m_prevAnimCount = static_cast<float>(fmod(m_prevAnimCount, animTotalTime));
		}

		// �Đ����Ԃ��X�V
		MV1SetAttachAnimTime(m_modelHandle, m_prevPlayAnim, m_prevAnimCount);
		// �A�j���[�V�����̃u�����h����ݒ肷��
		MV1SetAttachAnimBlendRate(m_modelHandle, m_prevPlayAnim, kAnimBlendMax - m_animBlendRate);
	}
}