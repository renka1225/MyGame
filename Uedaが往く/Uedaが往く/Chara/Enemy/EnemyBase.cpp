#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"
#include <fstream>
#include <sstream>

// �萔
namespace
{
	constexpr float kApproachRange = 70.0f;	 // �v���C���[�ɋ߂Â��͈�
	constexpr float kAttackRange = 100.0f;	 // �v���C���[���U������͈�
	constexpr int kStopMinTime = 30;		 // �ŏ��̒�~����
	constexpr int kStopMaxTime = 150;		 // �ő�̒�~����

	// �A�j���[�V�������
	constexpr float kAnimBlendMax = 1.0f;	 // �A�j���[�V�����u�����h�̍ő�l
	constexpr float kAnimBlendSpeed = 0.2f;	 // �A�j���[�V�����u�����h�̕ω����x
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyBase::EnemyBase() :
	m_isMove(false),
	m_isAttack(false),
	m_stopTime(0),
	m_angleIntervalTime(0),
	m_intervalTime(0)
{
	m_currentState = CharacterBase::State::kFightIdle;
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
/// <param name="MoveVec">�ړ���</param>
/// <param name="stage">�X�e�[�W���Q��</param>
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
EnemyBase::CharacterBase::State EnemyBase::UpdateMoveParameter(Player& player, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	CharacterBase::State nextState = m_currentState;
	
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
			if (m_stopTime <= 0)
			{
				dir = VNorm(dir);
				moveVec = VScale(dir, m_moveSpeed);

				// �ҋ@��Ԃ̏ꍇ
				if (m_currentState == CharacterBase::State::kFightIdle)
				{
					nextState = CharacterBase::State::kRun; // �ړ���Ԃɂ���
				}
			}
			else
			{
				m_stopTime--;
			}
		}
		// �v���C���[���U���͈͂ɓ������ꍇ
		//else if(distance <= kAttackRange)
		//{
		//	nextState = CharacterBase::State::kKick;	// �U����Ԃɂ���
		//}
		else
		{
			m_stopTime = kStopMinTime + GetRand(kStopMaxTime);	// ��~���Ԃ������_���Ōv�Z����
			nextState = CharacterBase::State::kFightIdle;		// �ҋ@��Ԃɂ���
		}
	}

	return nextState;
}


/// <summary>
/// �p���`�U��
/// </summary>
void EnemyBase::Punch()
{
	// �U�����̓X�L�b�v
	if (m_isAttack) return;

	// �p���`�ł��Ȃ��ꍇ
	if (m_punchCoolTime > 0)
	{
		m_punchCoolTime--;
		return;
	}

	// �R���{���͂̎�t���Ԃ̍X�V
	m_punchComboTime--;

	// �R���{���͎�t���ԓ��Ƀ{�^���������ꂽ�ꍇ
	if (m_punchComboTime > 0)
	{
		m_punchCount++;
	}
	else
	{
		m_punchCount = 0;
	}

	// �R���{���ɂ���ăp���`��ς���
	switch (m_punchCount)
	{
	case 0:
		m_punchComboTime = m_status.punchReceptionTime; // �R���{���͂̎�t���Ԃ����Z�b�g
		m_isAttack = true;
		m_isFighting = false;
		m_currentState = CharacterBase::State::kPunch1;
		PlayAnim(AnimKind::kPunch1);
		break;
	case 1:
		m_punchComboTime = m_status.punchReceptionTime;
		m_isAttack = true;
		m_isFighting = false;
		m_currentState = CharacterBase::State::kPunch2;
		PlayAnim(AnimKind::kPunch2);
		break;
	case 2:
		m_punchComboTime = m_status.punchReceptionTime;
		m_isAttack = true;
		m_isFighting = false;
		m_currentState = CharacterBase::State::kPunch3;
		PlayAnim(AnimKind::kPunch3);
		break;
	case 3:
		m_punchCount = 0;
		m_punchCoolTime = m_status.punchCoolTime;	// �N�[���_�E���^�C����ݒ�
		break;
	default:
		break;
	}
}


/// <summary>
/// �L�b�N�U��
/// </summary>
void EnemyBase::kick()
{
	//m_isAttack = true;
	//m_currentState = CharacterBase::State::kKick;
	//PlayAnim(AnimKind::kKick);

	// �U�����̓X�L�b�v
	if (m_isAttack) return;

	// �L�b�N�U��
	m_isAttack = true;
	m_isFighting = false;
	m_currentState = CharacterBase::State::kKick;
	PlayAnim(AnimKind::kKick);
}


/// <summary>
/// �������
/// </summary>
/// <param name="moveVec">�ړ��x�N�g��</param>
void EnemyBase::Avoidance(VECTOR& moveVec)
{
	// ����ł��Ȃ��ꍇ
	if (m_avoidCoolTime > 0)
	{
		m_avoidCoolTime--;
		return;
	}

	m_isFighting = false;
	m_avoidCount++;
	// ��𐔂��ő�ɂȂ����ꍇ
	if (m_avoidCount > m_status.maxAvoidCount)
	{
		m_avoidCount = 0;
		m_avoidCoolTime = m_status.avoidCoolTime;	// �N�[���_�E���^�C����ݒ�
	}
	else
	{
		m_currentState = CharacterBase::State::kAvoid;
		// �ړ��x�N�g����ݒ肷��
		//VECTOR backMoveVec = VScale(m_targetMoveDir, -1.0f);
		//m_pos = VAdd(m_pos, VScale(backMoveVec, m_status.avoidDist));
	}
}


/// <summary>
/// �\������
/// </summary>
void EnemyBase::Fighting()
{
	m_isFighting = true;
	m_currentState = CharacterBase::State::kFightWalk;
	PlayAnim(AnimKind::kFightWalk);
}


/// <summary>
/// �K�[�h����
/// </summary>
void EnemyBase::Guard()
{
	m_isGuard = true;
	m_currentState = CharacterBase::State::kGuard;
	PlayAnim(AnimKind::kGuard);
}


/// <summary>
/// �K�[�h��Ԃ�����
/// </summary>
void EnemyBase::OffGuard()
{
	m_isGuard = false;
	m_currentState = CharacterBase::State::kFightIdle;
	PlayAnim(AnimKind::kFightIdle);
}


/// <summary>
/// �G�̊p�x���X�V
/// </summary>
void EnemyBase::UpdateAngle(Player& player)
{
	m_angleIntervalTime++;

	// �G�̈ʒu����v���C���[�ʒu�܂ł̃x�N�g�������߂�
	VECTOR dir = VSub(player.GetPos(), m_pos);

	// ��莞�Ԃ�������G�l�~�[�̊p�x���X�V����
	if (m_angleIntervalTime >= m_enemyInfo.changeAngleFrame)
	{
		// �����_���Ńv���C���[�̕���������
		int randNum = GetRand(m_enemyInfo.maxProb);
		if (randNum <= m_enemyInfo.changeAngleProb)
		{
			m_angle = atan2f(dir.x, dir.z);
		}
		m_angleIntervalTime = 0;
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
	if (hitPunch && m_currentState == CharacterBase::State::kPunch1)
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
	else if (hitKick && m_currentState == CharacterBase::State::kKick)
	{
		// �L�b�N�����������ꍇ
		if (!player.GetIsGuard())
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
	if (!hit && m_currentState == CharacterBase::State::kGrab)
	{
		// �͂ݎ��s�̃A�j���[�V�������Đ�����
	}
}