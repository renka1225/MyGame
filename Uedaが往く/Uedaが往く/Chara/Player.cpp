#include "DxLib.h"
#include "Camera.h"
#include "Stage.h"
#include "EnemyBase.h"
#include "UIGauge.h"
#include "Input.h"
#include "LoadData.h"
#include "Player.h"

// �萔
namespace
{
	// �v���C���[���
	const char* const kfileName = "data/Model/player.mv1";	// �v���C���[�̃t�@�C����
	constexpr float kMaxGauge = 100.0f;						// �ő�Q�[�W��
	constexpr float kGaugeCharge = 0.3f;					// 1��̍U���ő�����Q�[�W��
	constexpr float kAcceleration = 0.7f;					// �v���C���[�̉����x
	constexpr float kDeceleration = 0.7f;					// �v���C���[�̌����x
	constexpr int kMaxPunchCount = 3;						// �ő�R���{��
	constexpr int kPunchComboTime = 40;						// �p���`�R���{�̓��͎�t����
	constexpr int kPunchCoolTime = 20;						// �p���`�ł���悤�ɂȂ�܂ł̎���
	constexpr float kAvoidDist = 30.0f;						// ����̋���
	constexpr int kMaxAvoidCount = 3;						// �A���ŉ���ł����
	constexpr int kAvoidCoolTime = 30;						// ����ł���悤�ɂȂ�܂ł̎���
	constexpr float kFightWalkSpeed = 1.8f;					// �\�����̈ړ����x
	constexpr float kGuardAnimTime = 10.0f;					// �K�[�h���̃A�j���[�V�������~�߂鎞��
	constexpr float kAngleSpeed = 0.2f;						// �v���C���[�p�x�̕ω����x
	constexpr float kVelocity = 6.0f;						// �W�����v�̍���
	constexpr float kGravity = -0.25f;						// �d��
	constexpr float kScale = 0.3f;							// �v���C���[���f���̊g�嗦
	const VECTOR kInitDir = VGet(0.0f, 0.0f, 0.0f);			// ��������
	const VECTOR kInitPos = VGet(0.0f, 0.0f, -20.0f);		// �����ʒu

	// �A�j���[�V�������
	constexpr float kAnimBlendMax = 1.0f;	 // �A�j���[�V�����u�����h�̍ő�l
	constexpr float kAnimBlendSpeed = 0.2f;	 // �A�j���[�V�����u�����h�̕ω����x
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player():
	m_gauge(0.0f),
	m_punchCount(0),
	m_punchComboTime(0),
	m_punchCoolTime(0),
	m_avoidCount(0),
	m_avoidCoolTime(0),
	m_isMove(false),
	m_isFighting(false),
	m_targetMoveDir(kInitDir),
	m_currentState(PlayerState::kFightIdle)
{
	// �L�����N�^�[����ǂݍ���
	m_pLoadData = std::make_shared<LoadData>(*this, static_cast<int>(CharaType::kPlayer));

	m_hp = m_status.maxHp;
	m_pos = kInitPos;
	m_moveSpeed = 0.0f;
	m_angle = 0.0f;
	m_modelHandle = MV1LoadModel(kfileName);

	m_animBlendRate = kAnimBlendMax;

	// ���f���S�̂̃R���W�������̃Z�b�g�A�b�v
	MV1SetupCollInfo(m_modelHandle, -1);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
/// ������
/// </summary>
void Player::Init()
{
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	MV1SetPosition(m_modelHandle, m_pos);
	PlayAnim(AnimKind::kFightIdle);
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���̓R�}���h</param>
/// <param name="stage">�X�e�[�W���Q��</param>
void Player::Update(const Input& input, const Camera& camera, EnemyBase& enemy, Stage& stage)
{
	// �p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��
	VECTOR	upMoveVec;		// ��{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	leftMoveVec;	// ���{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	moveVec;		// ���̃t���[���̈ړ��x�N�g��

	// �v���C���[�̏�Ԃ��X�V
	PlayerState prevState = m_currentState;

	// �U������
	m_currentState = Punch(input);
	m_currentState = Kick(input);
	// �������
	m_currentState = Avoidance(input, moveVec);
	// �\������
	m_currentState = Fighting(input);
	// �K�[�h����
	m_currentState = Guard(input);
	// �ړ�����
	m_currentState = UpdateMoveParameter(input, camera, upMoveVec, leftMoveVec, moveVec);

	// �G�l�~�[�Ƃ̓����蔻����`�F�b�N����
	enemy.CheckHitPlayerCol(*this, VGet(m_pos.x, m_pos.y + m_colInfo.bodyHeight, m_pos.z), m_pos, m_colInfo.bodyRadius);

	// �A�j���[�V������Ԃ��X�V
	UpdateAnimState(prevState);

	// �v���C���[�̈ړ�������ݒ�
	UpdateAngle(enemy);

	// �ړ��x�N�g�������Ƀv���C���[���ړ�������
	Move(moveVec, stage);

	// �A�j���[�V���������̍X�V
	UpdateAnim();

	// �����蔻��̈ʒu�X�V
	UpdateCol();
}


/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	MV1DrawModel(m_modelHandle);

	// HP�Q�[�W��\��
	m_pUIGauge->DrawPlayerHP(m_hp, m_status.maxHp);
	m_pUIGauge->DrawPlayerGauge(m_gauge, kMaxGauge);

#ifdef _DEBUG	// �f�o�b�O�\��
	DrawFormatString(0, 20, 0xffffff, "�v���C���[���W(%0.2f,%0.2f,%0.2f)", m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 40, 0xffffff, "hp:%0.2f",m_hp);

	// �����蔻��`��
	DrawCapsule3D(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius, 1, 0x0000ff, 0xffffff, false);	// �S�g
	DrawCapsule3D(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius, 1, 0xff00ff, 0xffffff, false);		// �r
	DrawCapsule3D(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius, 1, 0xffff00, 0xffffff, false);		// �r
#endif
}


/// <summary>
/// �G�Ƃ̓����蔻����`�F�b�N����
/// </summary>
/// <param name="enemy">�G�̎Q��</param>
/// <param name="eCapPosTop">�G�̃J�v�Z���̏�ʒu</param>
/// <param name="eCapPosBottom">�G�̃J�v�Z���̉��ʒu</param>
/// <param name="CapRadius">�G�̓����蔻��̔��a</param>
void Player::CheckHitEnemyCol(EnemyBase& enemy, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius)
{
	// �v���C���[�ƓG�̓����蔻����s��
	bool hit = HitCheck_Capsule_Capsule(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius, eCapPosTop, eCapPosBottom, eCapRadius);
	// �p���`
	bool hitPunch = HitCheck_Capsule_Capsule(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius, eCapPosTop, eCapPosBottom, eCapRadius);
	// �L�b�N
	bool hitKick = HitCheck_Capsule_Capsule(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius, eCapPosTop, eCapPosBottom, eCapRadius);

	// �p���`�����������ꍇ
	if (hitPunch && m_currentState == PlayerState::kPunch)
	{
		// �p���`�����������ꍇ
		enemy.OnDamage(m_status.punchPower);
		// TODO:�U��������������Q�[�W�𑝂₷
		m_gauge += kGaugeCharge;

	}
	// �L�b�N�����������ꍇ
	else if (hitKick && m_currentState == PlayerState::kKick)
	{
		// �L�b�N�����������ꍇ
		if (m_currentState == PlayerState::kKick)
		{
			enemy.OnDamage(m_status.kickPower);
			m_gauge += kGaugeCharge;
		}
	}
	// �U�����łȂ��A�G�ɓ��������ꍇ
	else if(hit)
	{
		// �v���C���[�̈ʒu��␳����
		VECTOR collisionNormal = VSub(m_pos, enemy.GetPos());
		collisionNormal = VNorm(collisionNormal);

		const float kAdj = 1.0f;
		m_pos = VAdd(m_pos, VScale(collisionNormal, kAdj));
	}

	// �݂͂����܂�Ȃ������ꍇ
	if(!hit && m_currentState == PlayerState::kGrab)
	{
		// �͂ݎ��s�̃A�j���[�V�������Đ�����
	}

	// �Q�[�W�ʂ̒���
	m_gauge = std::min(m_gauge, kMaxGauge);
}


/// <summary>
/// �v���C���[�̈ړ�����
/// </summary>
/// <param name="MoveVec">�ړ��x�N�g��</param>
/// <param name="stage">�X�e�[�W�Q��</param>
void Player::Move(const VECTOR& moveVec, Stage& stage)
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
	m_pos = stage.CheckPlayerCol(*this, moveVec);

	// �v���C���[�̍��W���X�V����
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// �p���`�U������
/// </summary>
/// <param name="input">���͏���</param>
/// <returns>���݂̏��</returns>
Player::PlayerState Player::Punch(const Input& input)
{
	PlayerState nextState = m_currentState;

	// �U�����̓X�L�b�v
	if (m_isAttack) return nextState;

	// �p���`�ł��Ȃ��ꍇ
	if (m_punchCoolTime > 0)
	{
		m_punchCoolTime--;
		return nextState;
	}

	// �R���{���͂̎�t���Ԃ̍X�V
	m_punchComboTime--;

	if (input.IsTriggered("punch"))
	{
		// �R���{���͎�t���ԓ��Ƀ{�^���������ꂽ�ꍇ
		if (m_punchComboTime > 0)
		{
			m_punchCount++;
		}
		else
		{
			m_punchCount = 0;
		}

		// �R���{�����ő�ɂȂ����ꍇ
		if (m_punchCount > kMaxPunchCount)
		{
			m_punchCount = 0;
			m_punchCoolTime = kPunchCoolTime;	// �N�[���_�E���^�C����ݒ�
		}
		else
		{
			m_punchComboTime = kPunchComboTime; // �R���{���͂̎�t���Ԃ����Z�b�g
			m_isAttack = true;
			nextState = PlayerState::kPunch;
			PlayAnim(AnimKind::kPunch);
		}
	}

	return nextState;
}


/// <summary>
/// �L�b�N�U������
/// </summary>
/// <param name="input">���͏���</param>
/// <returns>���݂̏��</returns>
Player::PlayerState Player::Kick(const Input& input)
{
	PlayerState nextState = m_currentState;

	// �U�����̓X�L�b�v
	if (m_isAttack) return nextState;

	// �L�b�N�U��
	else if (input.IsTriggered("kick"))
	{
		m_isAttack = true;
		nextState = PlayerState::kKick;
		PlayAnim(AnimKind::kKick);
	}

	return nextState;
}


/// <summary>
/// �������
/// </summary>
/// <param name="input">���͏���</param>
/// <returns>���݂̏��</returns>
Player::PlayerState Player::Avoidance(const Input& input, VECTOR& moveVec)
{
	PlayerState nextState = m_currentState;

	// ����ł��Ȃ��ꍇ
	if (m_avoidCoolTime > 0)
	{
		m_avoidCoolTime--;
		return nextState;
	}

	if (input.IsTriggered("avoidance"))
	{
		m_avoidCount++;
		// ��𐔂��ő�ɂȂ����ꍇ
		if (m_avoidCount > kMaxAvoidCount)
		{
			m_avoidCount = 0;
			m_avoidCoolTime = kAvoidCoolTime;	// �N�[���_�E���^�C����ݒ�
		}
		else
		{
			nextState = PlayerState::kAvoid;
			// �ړ��x�N�g����ݒ肷��
			VECTOR backMoveVec = VScale(m_targetMoveDir, -1.0f);
			m_pos = VAdd(m_pos, VScale(backMoveVec, kAvoidDist));
		}
	}

	return nextState;
}


/// <summary>
/// �\��������
/// </summary>
/// <param name="input">���͏���</param>
/// <param name="enemy">�G���Q��</param>
/// <returns>���݂̏��</returns>
Player::PlayerState Player::Fighting(const Input& input)
{
	PlayerState nextState = m_currentState;

	if (input.IsTriggered("fighting"))
	{
		m_isFighting = true;
		nextState = PlayerState::kFightWalk;
		PlayAnim(AnimKind::kFightWalk);
	}
	else if(input.IsReleased("fighting"))
	{
		m_isFighting = false;
		nextState = PlayerState::kFightIdle;
		PlayAnim(AnimKind::kFightIdle);
	}

	return nextState;
}


/// <summary>
/// �K�[�h����
/// </summary>
/// <param name="input">���͏���</param>
/// <returns>���݂̏��</returns>
Player::PlayerState Player::Guard(const Input& input)
{
	PlayerState nextState = m_currentState;

	if (input.IsTriggered("guard"))
	{
		m_isGuard = true;
		nextState = PlayerState::kGuard;
		PlayAnim(AnimKind::kGuard);
	}
	else if (input.IsReleased("guard"))
	{
		m_isGuard = false;
		nextState = PlayerState::kFightIdle;
		PlayAnim(AnimKind::kFightIdle);
	}

	return nextState;
}


/// <summary>
/// �ړ��p�����[�^��ݒ肷��
/// </summary>
/// <param name="input">���͏���</param>
/// <param name="camera">�J����</param>
/// <param name="upMoveVec">������ւ̈ړ��x�N�g��</param>
/// <param name="leftMoveVec">�������ւ̈ړ��x�N�g��</param>
/// <param name="moveVec">�ړ��x�N�g��</param>
/// <returns>���݂̏��</returns>
Player::PlayerState Player::UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	PlayerState nextState = m_currentState;

	/*�v���C���[�̈ړ������x�N�g�������߂�*/
	// ��{�^�����������Ƃ�
	upMoveVec = VSub(camera.GetAngle(), camera.GetPos());
	upMoveVec.y = 0.0f;

	// ���{�^�����������Ƃ�
	leftMoveVec = VCross(upMoveVec, VGet(0.0f, 1.0f, 0.0f));

	// �x�N�g���̐��K��
	upMoveVec = VNorm(upMoveVec);
	leftMoveVec = VNorm(leftMoveVec);

	// ���̃t���[���ł̈ړ��x�N�g����������
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// �ړ�������(true:�ړ�����)
	bool isPressMove = false;

	// �U�����A�K�[�h���łȂ��ꍇ
	if (!m_isAttack && !m_isGuard)
	{
		// �{�^������������ړ�
		if (input.IsPressing("up"))
		{
			moveVec = VAdd(moveVec, upMoveVec);
			isPressMove = true;
		}
		if (input.IsPressing("down"))
		{
			moveVec = VAdd(moveVec, VScale(upMoveVec, -1.0f));
			isPressMove = true;
		}
		if (input.IsPressing("left"))
		{
			moveVec = VAdd(moveVec, leftMoveVec);
			isPressMove = true;
		}
		if (input.IsPressing("right"))
		{
			moveVec = VAdd(moveVec, VScale(leftMoveVec, -1.0f));
			isPressMove = true;
		}

		// �ړ��{�^����������Ă���ꍇ
		if (isPressMove)
		{
			// �ҋ@��Ԃ̏ꍇ
			if (m_currentState == PlayerState::kFightIdle)
			{
				nextState = PlayerState::kRun; // �ړ���Ԃɂ���
			}

			// �v���C���[������������ݒ肷��
			m_targetMoveDir = VNorm(moveVec);

			// �v���C���[�̉����x��ݒ肷��
			if (m_moveSpeed < m_status.maxMoveSpeed)
			{
				m_moveSpeed += kAcceleration;
				m_moveSpeed = (std::min)(m_moveSpeed, m_status.maxMoveSpeed);
			}
			// �v���C���[�̈ړ��x�N�g����ݒ肷��
			// �\�����͈ړ����x��x������
			if (m_isFighting)
			{
				moveVec = VScale(m_targetMoveDir, kFightWalkSpeed);
			}
			else
			{
				moveVec = VScale(m_targetMoveDir, m_moveSpeed);
			}
		}
		// �ړ����Ȃ��ꍇ
		else
		{
			// �ړ���Ԃ̏ꍇ
			if (m_currentState == PlayerState::kRun)
			{
				// �ҋ@��Ԃɂ���
				nextState = PlayerState::kFightIdle;
				m_moveSpeed = 0.0f;
			}

			// �v���C���[������������
			if (m_moveSpeed > 0.0f)
			{
				m_moveSpeed -= kDeceleration;
				m_moveSpeed = (std::max)(0.0f, m_moveSpeed);
			}
			moveVec = VScale(m_targetMoveDir, m_moveSpeed);
		}
	}

	return nextState;
}


/// <summary>
/// �v���C���[�̉�]�𐧌䂷��
/// </summary>
void Player::UpdateAngle(EnemyBase& enemy)
{
	// �v���C���[�̊p�x���X�V
	if (m_isFighting)
	{
		// �G�̕�����������
		VECTOR dir = VSub(enemy.GetPos(), m_pos);
		m_angle = atan2f(dir.x, dir.z);
	}
	else
	{
		m_angle = atan2f(m_targetMoveDir.x, m_targetMoveDir.z);
	}
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));
}


/// <summary>
/// �A�j���[�V������Ԃ̍X�V
/// </summary>
/// <param name="prevState">���݂̃A�j���[�V�������</param>
void Player::UpdateAnimState(PlayerState prevState)
{
	// �U�����͏�Ԃ��X�V���Ȃ�
	if (m_isAttack) return;

	// �ҋ@��Ԃ���
	if (prevState == PlayerState::kFightIdle)
	{
		// �ړ��A�j���[�V�������Đ�
		if(m_currentState == PlayerState::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kPunch)PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kKick)	PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �\���A�j���[�V�������Đ�
		if(m_currentState == PlayerState::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �ړ���Ԃ���
	else if (prevState == PlayerState::kRun)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if(m_currentState == PlayerState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kPunch) PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �\���A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �p���`��Ԃ���
	else if (prevState == PlayerState::kPunch)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kRun) PlayAnim(AnimKind::kRun);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �\���A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �L�b�N��Ԃ���
	else if (prevState == PlayerState::kKick)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kPunch) PlayAnim(AnimKind::kPunch);
		// ����A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �\���A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �����Ԃ���
	else if (prevState == PlayerState::kAvoid)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kPunch) PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kKick) PlayAnim(AnimKind::kKick);
		// �\���A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �\����Ԃ���
	else if (prevState == PlayerState::kFightWalk)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kPunch) PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �K�[�h��Ԃ���
	else if (prevState == PlayerState::kGuard)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kPunch) PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �\���A�j���[�V�������Đ�
		if (m_currentState == PlayerState::kFightWalk) PlayAnim(AnimKind::kFightWalk);
	}
}


/// <summary>
/// �A�j���[�V��������
/// </summary>
void Player::UpdateAnim()
{
	float animTotalTime; // �Đ����̃A�j���[�V��������

	// �u�����h����1�ȉ��̏ꍇ
	if (m_animBlendRate < kAnimBlendMax)
	{
		m_animBlendRate += kAnimBlendSpeed;
		m_animBlendRate = std::min(m_animBlendRate, kAnimBlendMax);
	}

	// ���ݍĐ����̃A�j���[�V�����̏���
	if (m_currentPlayAnim != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_currentPlayAnim);

		// �A�j���[�V�����ɂ���čĐ��X�s�[�h��ς���
		if (m_currentState == PlayerState::kPunch)
		{
			m_currentAnimCount += m_animSpeed.punch;
		}
		else if (m_currentState == PlayerState::kKick)
		{
			m_currentAnimCount += m_animSpeed.kick;
		}
		else if(m_currentState == PlayerState::kAvoid)
		{
			m_currentAnimCount += m_animSpeed.avoid;
		}
		else if (m_currentState == PlayerState::kFightWalk)
		{
			// �ړ����̂݃A�j���[�V�������Đ�
			if (m_isMove)
			{
				m_currentAnimCount += m_animSpeed.fightWalk;
			}
			else
			{
				m_currentAnimCount = 0.0f;
			}
		}
		else if (m_currentState == PlayerState::kGuard)
		{
			// ��x�̂݃A�j���[�V�������Đ�
			m_currentAnimCount += m_animSpeed.guard;
			m_currentAnimCount = std::min(m_currentAnimCount, kGuardAnimTime);

			// �K�[�h�A�j���[�V�������I�������ҋ@��ԂɈڍs
			if (!m_isGuard)
			{
				m_currentState = PlayerState::kFightIdle;
				PlayAnim(AnimKind::kFightIdle);
			}
		}
		else
		{
			m_currentAnimCount += m_animSpeed.fightIdle;
		}

		
		// �p���`�R���{�̏ꍇ
		if (m_currentAnimCount >= kPunchComboTime && m_punchCount > 0 && m_currentState == PlayerState::kPunch)
		{
			// �p���`�R���{�̏ꍇ
			m_currentAnimCount = 0.0f;
			m_punchCount--;
			PlayAnim(AnimKind::kPunch);
		}
		if (m_currentAnimCount > animTotalTime)
		{
			// �U���A�j���[�V�������I��������ҋ@��ԂɈڍs
			if (m_isAttack)
			{
				m_isAttack = false;
				m_currentState = PlayerState::kFightIdle;
				PlayAnim(AnimKind::kFightIdle);
			}
			// ����A�j���[�V�������I�������ҋ@��ԂɈڍs
			else if (m_currentState == PlayerState::kAvoid)
			{
				m_currentState = PlayerState::kFightIdle;
				PlayAnim(AnimKind::kFightIdle);
			}
			else
			{
				// �A�j���[�V�����̍Đ����Ԃ����[�v
				m_currentAnimCount = static_cast<float>(fmod(m_currentAnimCount, animTotalTime));
			}
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