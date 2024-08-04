#include "DxLib.h"
#include "Camera.h"
#include "Stage.h"
#include "EnemyBase.h"
#include "UIGauge.h"
#include "Input.h"
#include "LoadData.h"
#include "DebugDraw.h"
#include "Player.h"

// �萔
namespace
{
	// �v���C���[���
	const char* const kfileName = "data/Model/Chara/Player.mv1";	// �v���C���[�̃t�@�C����
	constexpr float kMaxGauge = 100.0f;								// �ő�Q�[�W��
	constexpr float kGaugeCharge = 0.3f;							// 1��̍U���ő�����Q�[�W��
	constexpr float kHPRecoveryRate = 0.3f;							// �v���C���[��HP���񕜂��銄��
	constexpr float kAngleSpeed = 0.2f;								// �v���C���[�p�x�̕ω����x
	constexpr float kScale = 0.3f;									// �v���C���[���f���̊g�嗦
	constexpr float kAdj = 3.0f;									// �G�ɓ����������̈ʒu������

	const VECTOR kInitDir = VGet(0.0f, 0.0f, 0.0f);					// ��������
	const VECTOR kInitPos = VGet(0.0f, 0.0f, -40.0f);				// �����ʒu
	//const VECTOR kInitPos = VGet(5000.0f, 100.0f, -1000.0f);		// �����ʒu

	// �A�j���[�V�������
	constexpr float kAnimBlendMax = 1.0f;	 // �A�j���[�V�����u�����h�̍ő�l
	constexpr float kAnimBlendSpeed = 0.2f;	 // �A�j���[�V�����u�����h�̕ω����x
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player():
	m_gauge(0.0f),
	m_targetMoveDir(kInitDir)
{
	// �L�����N�^�[����ǂݍ���
	m_pLoadData = std::make_shared<LoadData>(*this, static_cast<int>(CharaType::kPlayer));
	m_pUIGauge = std::make_shared<UIGauge>(m_status.maxHp);

	m_hp = m_status.maxHp;
	m_pos = kInitPos;
	m_moveSpeed = 0.0f;
	m_angle = 0.0f;
	m_punchCount = 0;
	m_punchComboTime = 0;
	m_punchCoolTime = 0;
	m_avoidCoolTime = 0;
	m_avoidCount = 0;
	m_isMove = false;
	m_isFighting = false;
	m_modelHandle = MV1LoadModel(kfileName);
	m_currentState = CharacterBase::State::kFightIdle;
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
	MV1SetPosition(m_modelHandle, kInitPos);
	m_currentState = CharacterBase::State::kFightIdle;
	m_animBlendRate = kAnimBlendMax;
	PlayAnim(AnimKind::kFightIdle);

	// ���f���S�̂̃R���W�������̃Z�b�g�A�b�v
	MV1SetupCollInfo(m_modelHandle, -1);
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
	CharacterBase::State prevState = m_currentState;

	Punch(input);		// �p���`����
	Kick(input);		// �L�b�N����
	Avoid(input);		// �������
	Fighting(input);	// �\������
	Guard(input);		// �K�[�h����
	m_currentState = UpdateMoveParameter(input, camera, upMoveVec, leftMoveVec, moveVec); // �ړ�����

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

	// HP�o�[�̍X�V
	m_pUIGauge->UpdateHpBar();
}


/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	MV1DrawModel(m_modelHandle);

	// HP�Q�[�W��\��
	m_pUIGauge->DrawPlayerHP(m_hp);
	m_pUIGauge->DrawPlayerGauge(m_gauge, kMaxGauge);

#ifdef _DEBUG	// �f�o�b�O�\��
	DebugDraw debug;
	debug.DrawPlayerInfo(m_pos, m_hp, static_cast<int>(m_currentState));
	// �����蔻��`��
	debug.DrawBodyCol(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius); // �S�g
	debug.DrawAimCol(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius);		// �r
	debug.DrawLegCol(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius);		// �r
#endif
}


/// <summary>
/// �_���[�W���󂯂��ۂ̏���
/// </summary>
/// <param name="damage">�_���[�W��</param>
void Player::OnDamage(float damage)
{
	CharacterBase::OnDamage(damage);

	// �K�[�h��Ԃ̏ꍇ
	if (m_currentState == CharacterBase::State::kGuard)
	{
		OffGuard();
	}
}


/// <summary>
/// �񕜏���
/// </summary>
void Player::Recovery()
{
	// �������̑O��HP���񕜂���
	m_hp = std::min(m_hp + m_status.maxHp * kHPRecoveryRate, m_status.maxHp);
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

	// 1�R���{�ڂ����������ꍇ
	if (hitPunch && m_currentState == CharacterBase::State::kPunch1)
	{
		// �p���`�����������ꍇ
		enemy.OnDamage(m_status.punchPower);
		m_gauge += kGaugeCharge;

	}
	// 2�R���{�ڂ����������ꍇ
	if (hitPunch && m_currentState == CharacterBase::State::kPunch2)
	{
		// �p���`�����������ꍇ
		enemy.OnDamage(m_status.secondPunchPower);
		m_gauge += kGaugeCharge;
	}
	// 3�R���{�ڂ����������ꍇ
	if (hitPunch && m_currentState == CharacterBase::State::kPunch3)
	{
		// �p���`�����������ꍇ
		enemy.OnDamage(m_status.thirdPunchPower);
		m_gauge += kGaugeCharge;
	}
	// �L�b�N�����������ꍇ
	else if (hitKick && m_currentState == CharacterBase::State::kKick)
	{
		// �L�b�N�����������ꍇ
		if (m_currentState == CharacterBase::State::kKick)
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

		m_pos = VAdd(m_pos, VScale(collisionNormal, kAdj));
	}

	// �݂͂����܂�Ȃ������ꍇ
	if(!hit && m_currentState == CharacterBase::State::kGrab)
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
void Player::Punch(const Input& input)
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
}


/// <summary>
/// �L�b�N�U������
/// </summary>
/// <param name="input">���͏���</param>
/// <returns>���݂̏��</returns>
void Player::Kick(const Input& input)
{
	// �U�����̓X�L�b�v
	if (m_isAttack) return;

	// �L�b�N�U��
	else if (input.IsTriggered("kick"))
	{
		m_isAttack = true;
		m_isFighting = false;
		m_currentState = CharacterBase::State::kKick;
		PlayAnim(AnimKind::kKick);
	}
}


/// <summary>
/// �������
/// </summary>
/// <param name="input">���͏���</param>
/// <returns>���݂̏��</returns>
void Player::Avoid(const Input& input)
{
	// ����ł��Ȃ��ꍇ
	if (m_avoidCoolTime > 0)
	{
		m_avoidCoolTime--;
		return;
	}

	if (input.IsTriggered("avoidance"))
	{
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
			VECTOR backMoveVec = VScale(m_targetMoveDir, -1.0f);
			m_pos = VAdd(m_pos, VScale(backMoveVec, m_status.avoidDist));
		}
	}
}


/// <summary>
/// �\��������
/// </summary>
/// <param name="input">���͏���</param>
/// <param name="enemy">�G���Q��</param>
/// <returns>���݂̏��</returns>
void Player::Fighting(const Input& input)
{
	if (input.IsTriggered("fighting"))
	{
		m_isFighting = true;
		m_currentState = CharacterBase::State::kFightWalk;
		PlayAnim(AnimKind::kFightWalk);
	}
	else if(input.IsReleased("fighting"))
	{
		m_isFighting = false;
		m_currentState = CharacterBase::State::kFightIdle;
		PlayAnim(AnimKind::kFightIdle);
	}
}


/// <summary>
/// �K�[�h����
/// </summary>
/// <param name="input">���͏���</param>
/// <returns>���݂̏��</returns>
void Player::Guard(const Input& input)
{
	if (input.IsTriggered("guard"))
	{
		m_isGuard = true;
		m_currentState = CharacterBase::State::kGuard;
		PlayAnim(AnimKind::kGuard);
	}
	else if (input.IsReleased("guard"))
	{
		m_isGuard = false;
		m_currentState = CharacterBase::State::kFightIdle;
		PlayAnim(AnimKind::kFightIdle);
	}
}


/// <summary>
/// �K�[�h��Ԃ���������
/// </summary>
void Player::OffGuard()
{
	m_isGuard = false;
	m_currentState = CharacterBase::State::kFightIdle;
	PlayAnim(AnimKind::kFightIdle);
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
Player::CharacterBase::State Player::UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	CharacterBase::State nextState = m_currentState;

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
			if (m_currentState == CharacterBase::State::kFightIdle)
			{
				nextState = CharacterBase::State::kRun; // �ړ���Ԃɂ���
			}

			// �v���C���[������������ݒ肷��
			m_targetMoveDir = VNorm(moveVec);

			// �v���C���[�̉����x��ݒ肷��
			if (m_moveSpeed < m_status.maxMoveSpeed)
			{
				m_moveSpeed += m_status.acceleration;
				m_moveSpeed = (std::min)(m_moveSpeed, m_status.maxMoveSpeed);
			}
			// �v���C���[�̈ړ��x�N�g����ݒ肷��
			// �\�����͈ړ����x��x������
			if (m_isFighting)
			{
				moveVec = VScale(m_targetMoveDir, m_status.fightWalkSpeed);
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
			if (m_currentState == CharacterBase::State::kRun)
			{
				// �ҋ@��Ԃɂ���
				nextState = CharacterBase::State::kFightIdle;
				m_moveSpeed = 0.0f;
			}

			// �v���C���[������������
			if (m_moveSpeed > 0.0f)
			{
				m_moveSpeed -= m_status.deceleration;
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