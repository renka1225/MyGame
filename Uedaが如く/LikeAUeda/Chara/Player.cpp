#include "DxLib.h"
#include "Camera.h"
#include "Stage.h"
#include "EnemyBase.h"
#include "UIGauge.h"
#include "Input.h"
#include "Player.h"

// �萔
namespace
{
	// �v���C���[���
	const char* const kfileName = "data/Model/player.mv1";	// �v���C���[�̃t�@�C����
	constexpr float kMaxHp = 100.0f;						// �ő�HP
	constexpr float kMaxGauge = 100.0f;						// �ő�Q�[�W��
	constexpr float kPunchPower = 3.0f;						// �p���`�̍U����
	constexpr float kKickPower = 5.0f;						// �L�b�N�̍U����
	constexpr float kMaxSpeed = 5.0f;						// �v���C���[�̍ő�ړ����x
	constexpr float kAcceleration = 0.2f;					// �v���C���[�̉����x
	constexpr float kDeceleration = 0.2f;					// �v���C���[�̌����x
	constexpr float kAvoidDist = 60.0f;						// ����̋���
	constexpr float kAngleSpeed = 0.2f;						// �v���C���[�p�x�̕ω����x
	constexpr float kVelocity = 6.0f;						// �W�����v�̍���
	constexpr float kGravity = -0.25f;						// �d��
	constexpr float kScale = 0.3f;							// �v���C���[���f���̊g�嗦
	const VECTOR kInitDir = VGet(0.0f, 0.0f, 0.0f);			// ��������
	const VECTOR kInitPos = VGet(0.0f, 0.0f, -20.0f);		// �����ʒu

	// �R���W�������
	constexpr float kHitHeight = 43.0f;				// �����蔻��J�v�Z���̍���
	constexpr float kHitRadius = 8.0f;				// �����蔻��J�v�Z���̔��a
	constexpr float kHitAimRadius = 10.0f;			// �r�̓����蔻��J�v�Z���̒���
	constexpr float kHitLegRadius = 10.0f;			// ���̓����蔻��J�v�Z���̒���
	const VECTOR kArmPos = VGet(3.0f, 40.0f, 0.0f); // �r�̓����蔻��ʒu
	const VECTOR kLegPos = VGet(3.0f, 20.0f, 0.0f); // �r�̓����蔻��ʒu

	// �A�j���[�V�������
	constexpr float kAnimBlendMax = 1.0f;	 // �A�j���[�V�����u�����h�̍ő�l
	constexpr float kAnimBlendSpeed = 0.2f;	 // �A�j���[�V�����u�����h�̕ω����x
	constexpr float kPlayAnimSpeed = 0.5f;	 // �ʏ�̃A�j���[�V�����̑��x
	constexpr float kAttackAnimSpeed = 0.8f; // �U���A�j���[�V�����̑��x
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player() :
	m_hp(kMaxHp),
	m_gauge(0.0f),
	m_pos(kInitPos),
	m_isMove(false),
	m_isAttack(false),
	m_targetMoveDir(kInitDir),
	m_angle(0.0f),
	m_moveSpeed(0.0f),
	m_currentState(State::kFightIdle),
	m_modelHandle(-1),
	m_currentPlayAnim(-1),
	m_currentAnimCount(0.0f),
	m_prevPlayAnim(-1),
	m_prevAnimCount(0.0f),
	m_animBlendRate(kAnimBlendMax)
{
	m_modelHandle = MV1LoadModel(kfileName);
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
	m_pUIGauge = std::make_shared<UIGauge>();
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	MV1SetPosition(m_modelHandle, m_pos);
	PlayAnim(AnimKind::kFightIdle);
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���̓R�}���h</param>
/// <param name="stage">�X�e�[�W���Q��</param>
void Player::Update(const Input& input, const Camera& camera, Stage& stage)
{
	// �p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��
	VECTOR	upMoveVec;		// ��{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	leftMoveVec;	// ���{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	moveVec;		// ���̃t���[���̈ړ��x�N�g��

	// �v���C���[�̏�Ԃ��X�V
	State prevState = m_currentState;

	// �U������
	m_currentState = Attack(input);
	// �������
	m_currentState = Avoidance(input, moveVec);
	// �ړ�����
	m_currentState = UpdateMoveParameter(input, camera, upMoveVec, leftMoveVec, moveVec);

	// �A�j���[�V������Ԃ��X�V
	UpdateAnimState(prevState);

	// �v���C���[�̈ړ�������ݒ�
	UpdateAngle();

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
	m_pUIGauge->DrawPlayerHP(m_hp, kMaxHp);
	m_pUIGauge->DrawPlayerGauge(m_gauge, kMaxGauge);

#ifdef _DEBUG	// �f�o�b�O�\��
	DrawFormatString(0, 20, 0xffffff, "�v���C���[���W(%2f,%2f,%2f)", m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 40, 0xffffff, "hp:%f",m_hp);

	// �����蔻��`��
	DrawCapsule3D(m_col.hitTopPos, m_col.hitBottomPos, kHitRadius, 1, 0x0000ff, 0xffffff, false);
	DrawCapsule3D(m_col.armStartPos, m_col.armEndPos, kHitAimRadius, 1, 0xff00ff, 0xffffff, false);
	DrawCapsule3D(m_col.legStartPos, m_col.legEndPos, kHitLegRadius, 1, 0xffff00, 0xffffff, false);
#endif
}


/// <summary>
/// �_���[�W���󂯂��Ƃ�
/// </summary>
void Player::OnDamage()
{
	DrawString(0, 80, "���������I", 0xfffffff);

	m_hp = std::min(m_hp, kMaxHp);
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
	// �����蔻��J�v�Z���̈ʒu���v�Z����
	VECTOR pCapPosTop = VGet(m_pos.x, m_pos.y + kHitHeight, m_pos.z);

	// �v���C���[�ƓG�̓����蔻����s��
	bool hit = HitCheck_Capsule_Capsule(pCapPosTop, m_pos, kHitRadius, eCapPosTop, eCapPosBottom, kHitRadius);
	// �p���`
	bool hitPunch = HitCheck_Capsule_Capsule(m_col.armStartPos, m_col.armEndPos, kHitAimRadius, eCapPosTop, eCapPosBottom, kHitRadius);
	// �L�b�N
	bool hitKick = HitCheck_Capsule_Capsule(m_col.legStartPos, m_col.legEndPos, kHitAimRadius, eCapPosTop, eCapPosBottom, kHitRadius);
	// �L�b�N

	// �p���`�����������ꍇ
	if (hitPunch && m_currentState == State::kPunch)
	{
		// �p���`�����������ꍇ
		enemy.OnDamage(kPunchPower);
		// TODO:�U��������������Q�[�W�𑝂₷
		m_gauge += 3.0f;

	}
	// �L�b�N�����������ꍇ
	else if (hitKick && m_currentState == State::kKick)
	{
		// �L�b�N�����������ꍇ
		if (m_currentState == State::kKick)
		{
			enemy.OnDamage(kKickPower);
			m_gauge += 5.0f;
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
	}

	// �݂͂����܂�Ȃ������ꍇ
	if(!hit && m_currentState == State::kGrab)
	{
		// �͂ݎ��s�̃A�j���[�V�������Đ�����
	}

	// �Q�[�W�ʂ̒���
	m_gauge = std::min(m_gauge, kMaxHp);
}


/// <summary>
/// �v���C���[�̓����蔻��̈ʒu���X�V����
/// </summary>
void Player::UpdateCol()
{
	// �v���C���[�̌��������Ƃɉ�]�s����擾����
	MATRIX rotationMatrix = MGetRotY(m_angle);

	// �v���C���[�S�̂̓����蔻��ʒu���X�V
	m_col.hitTopPos = VAdd(m_pos, VTransform(VGet(0.0f, kHitHeight, 0.0f), rotationMatrix));
	m_col.hitBottomPos = m_pos;

	// �r�̓����蔻��ʒu���X�V
	VECTOR armOffset = VGet(5.0f, 40.0f, 2.0f);  // �r�̃I�t�Z�b�g
	VECTOR armEndOffset = VGet(0.0f, 0.0f, 3.0f);  // �r�̏I���ʒu�I�t�Z�b�g
	m_col.armStartPos = VAdd(m_pos, VTransform(armOffset, rotationMatrix));
	m_col.armEndPos = VAdd(m_col.armStartPos, VTransform(armEndOffset, rotationMatrix));

	// �r�̓����蔻��ʒu���X�V
	VECTOR legOffset = VGet(-2.0f, -5.0f, 0.0f);  // ���̃I�t�Z�b�g
	VECTOR legEndOffset = VGet(0.0f, 0.0f, -3.0f);  // ���̏I���ʒu�I�t�Z�b�g
	m_col.legStartPos = VAdd(m_pos, VTransform(legOffset, rotationMatrix));
	m_col.legEndPos = VAdd(m_col.legStartPos, VTransform(legEndOffset, rotationMatrix));
}


/// <summary>
/// �v���C���[�̈ړ�����
/// </summary>
void Player::Move(const VECTOR& MoveVector, Stage& stage)
{
	if (fabs(MoveVector.x) > 0.0f || fabs(MoveVector.z) > 0.0f)
	{
		m_isMove = true;
	}
	else
	{
		m_isMove = false;
	}

	// �����蔻����s���č��W��ۑ�����
	m_pos = stage.CheckCollision(*this, MoveVector);

	// �v���C���[�̍��W���X�V����
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// �U������
/// </summary>
/// <param name="input">���͏���</param>
/// <returns>���݂̏��</returns>
Player::State Player::Attack(const Input& input)
{
	State nextState = m_currentState;

	if (!m_isAttack)
	{
		// �p���`�U��
		if (input.IsTriggered("punch"))
		{
			m_isAttack = true;
			nextState = State::kPunch;
			PlayAnim(AnimKind::kPunch);
		}
		// �L�b�N�U��
		else if (input.IsTriggered("kick"))
		{
			m_isAttack = true;
			nextState = State::kKick;
			PlayAnim(AnimKind::kKick);
		}
	}

	return nextState;
}


/// <summary>
/// �������
/// </summary>
/// <param name="input">���͏���</param>
/// <returns>���݂̏��</returns>
Player::State Player::Avoidance(const Input& input, VECTOR& moveVec)
{
	// �U�����̏ꍇ�͉������Ȃ�
	if (m_currentState == State::kPunch || m_currentState == State::kKick) return m_currentState;

	State nextState = m_currentState;

	if (input.IsTriggered("avoidance") && !m_isAttack)
	{
		m_isAttack = true;
		nextState = State::kAvoid;

		// �ړ��x�N�g����ݒ肷��
		VECTOR backMoveVec = VScale(m_targetMoveDir, -1.0f);
		m_pos = VAdd(m_pos, VScale(backMoveVec, kAvoidDist));
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
Player::State Player::UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	State nextState = m_currentState;

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

	// �U�����łȂ��ꍇ
	if (!m_isAttack)
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
			if (m_currentState == State::kFightIdle)
			{
				nextState = State::kRun; // �ړ���Ԃɂ���
			}

			// �v���C���[������������ݒ肷��
			m_targetMoveDir = VNorm(moveVec);

			// �v���C���[�̉����x��ݒ肷��
			if (m_moveSpeed < kMaxSpeed)
			{
				m_moveSpeed += kAcceleration;
				m_moveSpeed = (std::min)(m_moveSpeed, kMaxSpeed);
			}
			// �v���C���[�̈ړ��x�N�g����ݒ肷��
			moveVec = VScale(m_targetMoveDir, m_moveSpeed);
		}
		// �ړ����Ȃ��ꍇ
		else
		{
			// �ړ���Ԃ̏ꍇ
			if (m_currentState == State::kRun)
			{
				// �ҋ@��Ԃɂ���
				nextState = State::kFightIdle;
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
void Player::UpdateAngle()
{
	// �v���C���[�̊p�x���X�V
	m_angle = atan2f(m_targetMoveDir.x, m_targetMoveDir.z);
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));
}


/// <summary>
/// �A�j���[�V������Ԃ̍X�V
/// </summary>
/// <param name="prevState">���݂̃A�j���[�V�������</param>
void Player::UpdateAnimState(State prevState)
{
	// �U�����͏�Ԃ��X�V���Ȃ�
	if (m_isAttack) return;

	// �ҋ@��Ԃ���
	if (prevState == State::kFightIdle)
	{
		// �ړ��A�j���[�V�������Đ�
		if(m_currentState == State::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == State::kPunch)PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == State::kKick)	PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == State::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// �ړ���Ԃ���
	else if (prevState == State::kRun)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if(m_currentState == State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == State::kPunch) PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == State::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == State::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// �p���`��Ԃ���
	else if (prevState == State::kPunch)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == State::kRun) PlayAnim(AnimKind::kRun);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == State::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == State::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// �L�b�N��Ԃ���
	else if (prevState == State::kKick)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == State::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == State::kPunch) PlayAnim(AnimKind::kPunch);
		// ����A�j���[�V�������Đ�
		if (m_currentState == State::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// �����Ԃ���
	else if (prevState == State::kAvoid)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == State::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == State::kPunch) PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == State::kKick) PlayAnim(AnimKind::kKick);
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
			m_currentAnimCount += kAttackAnimSpeed;
		}
		else
		{
			m_currentAnimCount += kPlayAnimSpeed;
		}

		// �A�j���[�V�����̍Đ����Ԃ����[�v
		if (m_currentAnimCount > animTotalTime)
		{
			// �U���A�j���[�V�������I��������ҋ@��ԂɈڍs
			if (m_isAttack)
			{
				m_isAttack = false;
				m_currentState = State::kFightIdle;
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
			m_prevAnimCount += kAttackAnimSpeed;
		}
		else
		{
			m_prevAnimCount += kPlayAnimSpeed;
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


/// <summary>
/// �A�j���[�V�������Đ�����
/// </summary>
/// <param name="playAnim">�Đ�����A�j���[�V�������</param>
void Player::PlayAnim(AnimKind playAnimIndex)
{
	// 1�O�̃A�j���[�V�������A�^�b�`����Ă���ꍇ�폜����
	if (m_prevPlayAnim != -1)
	{
		MV1DetachAnim(m_modelHandle, m_prevPlayAnim);
		m_prevPlayAnim = -1;
	}

	// ���ݍĐ����̃A�j���[�V������1�O�Ɉړ�����
	m_prevPlayAnim = m_currentPlayAnim;
	m_prevAnimCount = m_currentAnimCount;

	// �V���ɃA�j���[�V�������A�^�b�`����
	m_currentPlayAnim = MV1AttachAnim(m_modelHandle, static_cast<int>(playAnimIndex), -1, false);
	m_currentAnimCount = 0.0f;

	// �u�����h����Prev���L���łȂ��ꍇ�A1.0�ɂ���
	if (m_prevPlayAnim == -1)
	{
		m_animBlendRate = kAnimBlendMax;
	}
	else
	{
		m_animBlendRate = 0.0f;
	}
}