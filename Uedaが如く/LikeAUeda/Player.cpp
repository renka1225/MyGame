#include "DxLib.h"
#include "Camera.h"
#include "Stage.h"
#include "Input.h"
#include "Player.h"

// �萔
namespace
{
	// �v���C���[���
	constexpr float kScale = 0.3f;						// �v���C���[���f���̊g�嗦
	constexpr float kMaxSpeed = 3.0f;					// �v���C���[�̍ő�ړ����x
	constexpr float kAcceleration = 0.2f;				// �v���C���[�̉����x
	constexpr float kDeceleration = 0.2f;				// �v���C���[�̌����x
	constexpr float kAngleSpeed = 0.2f;					// �v���C���[�p�x�̕ω����x
	constexpr float kVelocity = 6.0f;					// �W�����v�̍���
	constexpr float kGravity = -0.25f;					// �d��
	const VECTOR kInitDir = VGet(0.0f, 0.0f, 0.0f);		// ��������
	const VECTOR kInitPos = VGet(0.0f, 0.0f, 0.0f);		// �����ʒu
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
	m_currentState(State::kStand),
	m_modelHandle(-1)
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
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���̓R�}���h</param>
/// <param name="stage">�X�e�[�W���Q��</param>
void Player::Update(const Input& input, const Camera& camera, Stage& stage)
{
	/*�p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��*/
	VECTOR	upMoveVec;		// ��{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	leftMoveVec;	// ���{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	moveVec;		// ���̃t���[���̈ړ��x�N�g��

	// �v���C���[�̏�Ԃ��X�V
	State prevState = m_currentState;
	m_currentState = UpdateMoveParameter(input, camera, upMoveVec, leftMoveVec, moveVec);

	// �v���C���[�̈ړ�������ݒ�
	UpdateAngle();

	// �ړ��x�N�g�������Ƀv���C���[���ړ�������
	Move(moveVec, stage);
}


/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG	// �f�o�b�O�\��
	DrawFormatString(0, 20, 0xffffff, "�v���C���[���W(%2f,%2f,%2f)", m_pos.x, m_pos.y, m_pos.z);
#endif
}


/// <summary>
/// ���ɓ��������Ƃ�
/// </summary>
void Player::OnHitFloor()
{
	m_jumpPower = 0.0f;

	// �ړ����̏ꍇ
	if (m_isMove)
	{
		// �ړ���Ԃɂ���
		m_currentState = State::kRun;
	}
	else
	{
		// �ҋ@��Ԃɂ���
		m_currentState = State::kStand;
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
			m_moveSpeed = (std::min)(m_moveSpeed, kMaxSpeed);
		}
		// �v���C���[�̈ړ��x�N�g����ݒ肷��
		moveVec = VScale(m_targetMoveDir, m_moveSpeed);
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
			m_moveSpeed = (std::max)(0.0f, m_moveSpeed);
		}
		moveVec = VScale(m_targetMoveDir, m_moveSpeed);
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