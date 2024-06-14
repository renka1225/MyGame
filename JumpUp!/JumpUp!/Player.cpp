#include "DxLib.h"
#include "Stage.h"
#include "Camera.h"
#include "Input.h"
#include "DrawDebug.h"
#include "Player.h"

// �萔
namespace
{
	constexpr float kScale = 0.1f;		// �v���C���[���f���̊g�嗦
	constexpr float kMove = 1.0f;		// �v���C���[�ړ���
	constexpr float kAngleSpeed = 0.2f;	// �v���C���[�p�x�̕ω����x
	constexpr float kVelocity = 3.0f;	// �W�����v�̍���
	constexpr float kGravity = -0.2f;	// �d��
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player():
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_isMove(false),
	m_targetMoveDir(VGet(0.0f, 0.0f, 0.0f)),
	m_angle(0.0f),
	m_jumpPower(0.0f),
	m_modelHandle(-1),
	m_currentState(State::kStand)
{
	m_modelHandle = MV1LoadModel("data/model/player.mv1");
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
	// �p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��
	VECTOR	upMoveVec;		// ��{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	leftMoveVec;	// ���{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	moveVec;		// ���̃t���[���̈ړ��x�N�g��
	State prevState = m_currentState;
	m_currentState = UpdateMoveParameter(input, camera, upMoveVec, leftMoveVec, moveVec);

	// TODO:�A�j���[�V�����X�e�[�g�̍X�V

	// �v���C���[�̈ړ�������ݒ�
	UpdateAngle();

	// �ړ��x�N�g�������Ƀv���C���[���ړ�������
	Move(moveVec, stage);

	// TODO:�A�j���[�V��������
	UpdateAnim();
}


/// <summary>
/// �`��
/// </summary>
void Player::Draw(DrawDebug& drawDebug)
{
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG	// �f�o�b�O�\��
	// �v���C���[�ʒu�\��
	drawDebug.DrawPlayerInfo(m_pos);
#endif
}


/// <summary>
/// �V��ɓ���������
/// </summary>
void Player::OnHitRoof()
{
}


/// <summary>
/// ���ɓ��������Ƃ�
/// </summary>
void Player::OnHitFloor()
{
}


/// <summary>
/// ������
/// </summary>
void Player::OnFall()
{
}



/// <summary>
/// �v���C���[�̈ړ�����
/// </summary>
void Player::Move(const VECTOR& MoveVector, Stage& stage)
{
	if (fabs(MoveVector.x) > 0.01f || fabs(MoveVector.z) > 0.01f)
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

	// �v���C���[�̈ړ������x�N�g�������߂�

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

	// �v���C���[���W�����v���łȂ��A�{�^���������ꂽ��W�����v����
	if (m_currentState != State::kJump && input.IsTriggered("jump"))
	{
		// Y�������̑��x���Z�b�g
		m_jumpPower = kVelocity;

		// ��Ԃ��u�W�����v�v�ɂ���
		nextState = State::kJump;
	}

	// �W�����v���͏d�͂𔽉f����
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
		// �v���C���[�̈ړ��x�N�g����ݒ肷��
		moveVec = VScale(m_targetMoveDir, kMove);
	}
	// �ړ����Ȃ��ꍇ
	else
	{
		// �ړ���Ԃ�������
		if (m_currentState == State::kRun)
		{
			// �ҋ@��Ԃɂ���
			nextState = State::kStand;
		}
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
	// �v���C���[�̊p�x�𒲐�����
	float targetAngle;	// �ڕW�p�x
	float difference;	// �ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�

	// �ڕW�̕����x�N�g������p�x�����߂�
	targetAngle = atan2f(m_targetMoveDir.x, m_targetMoveDir.z);

	// �ڕW�̊p�x�ƌ��݂̊p�x�̍������߂�
	difference = targetAngle - m_angle;

	// ����180�x�ȏ�ɂȂ�Ȃ��悤�ɒ�������
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	// �p�x�̍���0�ɋ߂Â���
	if (difference > 0.0f)
	{
		// �����v���X�̏ꍇ�͈���
		difference -= kAngleSpeed;
		difference = std::min(0.0f, difference);
	}
	else
	{
		// �����}�C�i�X�̏ꍇ�͑���
		difference += kAngleSpeed;
		difference = std::max(difference, 0.0f);
	}

	// �v���C���[�̊p�x���X�V
	m_angle = targetAngle - difference;
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));
}


/// <summary>
/// �A�j���[�V��������
/// </summary>
void Player::UpdateAnim()
{
}