#include "DxLib.h"
#include "Stage.h"
#include "Camera.h"
#include "Input.h"
#include "Sound.h"
#include "DrawDebug.h"
#include "Player.h"

// �萔
namespace
{
	// �v���C���[���
	constexpr float kScale = 0.12f;								// �v���C���[���f���̊g�嗦
	constexpr float kMaxSpeed = 3.0f;							// �v���C���[�̍ő�ړ����x
	constexpr float kAcceleration = 0.2f;						// �v���C���[�̉����x
	constexpr float kDeceleration = 0.2f;						// �v���C���[�̌����x
	constexpr float kAngleSpeed = 0.2f;							// �v���C���[�p�x�̕ω����x
	constexpr float kVelocity = 6.0f;							// �W�����v�̍���
	constexpr float kGravity = -0.25f;							// �d��
	const VECTOR kInitDir = VGet(0.0f, 0.0f, 0.0f);				// ��������
	const VECTOR kInitPos = VGet(-160.0f, 50.0f, -350.0f);		// �����ʒu
	const VECTOR kDebugPos = VGet(0.0f, 1000.0f, 0.0f);			// �v���C���[���S�[���܂ňړ�����(�f�o�b�O�p)
		
	// �A�j���[�V�������
	constexpr float kAnimBlendMax = 1.0f;	 // �A�j���[�V�����u�����h�̍ő�l
	constexpr float kAnimBlendSpeed = 0.2f;	 // �A�j���[�V�����u�����h�̕ω����x
	constexpr float kPlayAnimSpeed = 0.5f;	 // �A�j���[�V�����̑��x
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player():
	m_pos(kInitPos),
	m_isMove(false),
	m_targetMoveDir(kInitDir),
	m_angle(0.0f),
	m_jumpPower(0.0f),
	m_moveSpeed(0.0f),
	m_isGoal(false),
	m_modelHandle(-1),
	m_currentState(State::kStand),
	m_currentPlayAnim(-1),
	m_currentAnimCount(0.0f),
	m_prevPlayAnim(-1),
	m_prevAnimCount(0.0f),
	m_animBlendRate(kAnimBlendMax)
{
	m_modelHandle = MV1LoadModel("data/Model/player.mv1");
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
	PlayAnim(AnimKind::kStand);
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���̓R�}���h</param>
/// <param name="stage">�X�e�[�W���Q��</param>
void Player::Update(const Input& input, const Camera& camera, Stage& stage)
{
#ifdef _DEBUG
	// �v���C���[���S�[���܂ňړ�������
	if (input.IsTriggered("debug")) m_pos = kDebugPos;
#endif

	/*�p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��*/
	VECTOR	upMoveVec;		// ��{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	leftMoveVec;	// ���{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	moveVec;		// ���̃t���[���̈ړ��x�N�g��

	// �v���C���[�̏�Ԃ��X�V
	State prevState = m_currentState;
	m_currentState = UpdateMoveParameter(input, camera, upMoveVec, leftMoveVec, moveVec);

	// �A�j���[�V������Ԃ̍X�V
	UpdateAnimState(prevState);

	// �v���C���[�̈ړ�������ݒ�
	UpdateAngle();

	// �ړ��x�N�g�������Ƀv���C���[���ړ�������
	Move(moveVec, stage);

	// �A�j���[�V���������̍X�V
	UpdateAnim();

	if (stage.CheckHitFlag(*this, m_pos))
	{
		m_isGoal = true;
	}
}


/// <summary>
/// �`��
/// </summary>
void Player::Draw(DrawDebug& drawDebug)
{
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG	// �f�o�b�O�\��
	// �v���C���[�ʒu�\��
	drawDebug.DrawPlayerInfo(m_pos, m_currentState);
#endif
}


/// <summary>
/// �V��ɓ���������
/// </summary>
void Player::OnHitRoof()
{
	// Y�������̑��x�𔽓]����
	m_jumpPower *= -1;
}


/// <summary>
/// ���ɓ��������Ƃ�
/// </summary>
void Player::OnHitFloor()
{
	m_jumpPower = 0.0f;

	// �W�����v���̏ꍇ
	if (m_currentState == State::kJump)
	{
		// �ړ����̏ꍇ
		if (m_isMove)
		{
			// �ړ���Ԃɂ���
			PlayAnim(AnimKind::kRun);
			m_currentState = State::kRun;
		}
		else
		{
			// �ҋ@��Ԃɂ���
			PlayAnim(AnimKind::kStand);
			m_currentState = State::kStand;
		}

		// ���n���̓A�j���[�V�����̃u�����h�͍s��Ȃ�
		m_animBlendRate = kAnimBlendMax;
	}
}


/// <summary>
/// ������
/// </summary>
void Player::OnFall()
{
	if (m_currentState != State::kJump)
	{
		// �W�����v��(������)�ɂ���
		m_currentState = State::kJump;

		// �A�j���[�V�����͗������̂��̂ɂ���
		PlayAnim(AnimKind::kFall);
	}
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
/// �ړ��p�����[�^��ݒ肷��
/// </summary>
/// <returns></returns>
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

	// �{�^���������ꂽ��W�����v����
	if (m_currentState != State::kJump && input.IsTriggered("jump"))
	{
		// �W�����vSE��炷
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kJumpSE)], DX_PLAYTYPE_BACK);

		// Y�������̑��x���Z�b�g
		m_jumpPower = kVelocity;

		// �W�����v��Ԃɂ���
		nextState = State::kJump;
	}

	// �d�͂𔽉f����
	if (m_currentState == State::kJump)
	{
		m_jumpPower += kGravity;
	}

	// �ړ��{�^����������Ă���ꍇ
	if (isPressMove)
	{
		// �ҋ@��Ԃ������ꍇ
		if (m_currentState == State::kStand)
		{
			// �ړ���Ԃɂ���
			nextState = State::kRun;
		}

		// �v���C���[������������ݒ肷��
		m_targetMoveDir = VNorm(moveVec);

		// �v���C���[�̉����x��ݒ肷��
		if (m_moveSpeed < kMaxSpeed)
		{
			m_moveSpeed += kAcceleration;
			m_moveSpeed = std::min(m_moveSpeed, kMaxSpeed);
		}
		// �v���C���[�̈ړ��x�N�g����ݒ肷��
		moveVec = VScale(m_targetMoveDir, m_moveSpeed);

		// �ړ�SE��炷
		if (m_currentState != State::kJump && !CheckSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kRunSE)]))
		{
			PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kRunSE)], DX_PLAYTYPE_BACK);
		}
	}
	// �ړ����Ȃ��ꍇ
	else
	{
		// �ړ���Ԃ�������
		if (m_currentState == State::kRun)
		{
			// �ҋ@��Ԃɂ���
			nextState = State::kStand;
			m_moveSpeed = 0.0f;
		}

		// �v���C���[������������
		if (m_moveSpeed > 0.0f)
		{
			m_moveSpeed -= kDeceleration;
			m_moveSpeed = std::max(0.0f, m_moveSpeed);
		}
		moveVec = VScale(m_targetMoveDir, m_moveSpeed);

		// �ړ�SE���~�߂�
		StopSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kRunSE)]);
	}

	// �ړ��x�N�g����Y������Y�������̑��x�ɂ���
	moveVec.y = m_jumpPower;

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
/// <param name="prevState">���݂̏��</param>
void Player::UpdateAnimState(State prevState)
{
	// �ҋ@��Ԃ���ړ��ɕς�����ꍇ
	if (prevState == State::kStand && m_currentState == State::kRun)
	{
		// �ړ��A�j���[�V�������Đ�����
		PlayAnim(AnimKind::kRun);
	}
	// �ҋ@��Ԃ���W�����v��Ԃɕς�����ꍇ
	else if (prevState == State::kStand && m_currentState == State::kJump)
	{
		// �W�����v��Ԃ��Đ�����
		PlayAnim(AnimKind::kJump);
	}
	// �ړ�����ҋ@��Ԃɕς�����ꍇ
	else if (prevState == State::kRun && m_currentState == State::kStand)
	{
		// �ҋ@�A�j���[�V�������Đ�����
		PlayAnim(AnimKind::kStand);
	}
	// �ړ���Ԃ���W�����v��Ԃɕς�����ꍇ
	else if (prevState == State::kRun && m_currentState == State::kJump)
	{
		// �W�����v�A�j���[�V�������Đ�����
		PlayAnim(AnimKind::kJump);
	}
	// �W�����v���̏ꍇ
	else if (m_currentState == State::kJump)
	{
		// �������Ă��āA�Đ����̃A�j���[�V�������㏸���p�������ꍇ
		if (m_jumpPower < 0.0f)
		{
			// �����A�j���[�V�������Đ�����
			if (MV1GetAttachAnim(m_modelHandle, m_currentPlayAnim) == static_cast<int>(State::kJump))
			{
				PlayAnim(AnimKind::kFall);
			}
		}
		else
		{
			PlayAnim(AnimKind::kJump);
		}
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
		m_currentAnimCount += kPlayAnimSpeed;

		// �A�j���[�V�����̍Đ����Ԃ����[�v
		if (m_currentAnimCount > animTotalTime)
		{
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
		m_prevPlayAnim += static_cast<int>(kPlayAnimSpeed);

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