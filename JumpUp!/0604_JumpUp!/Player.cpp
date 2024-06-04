#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "Input.h"
#include "DrawDebug.h"

// �萔
namespace
{
	// �v���C���[�̏��
	constexpr float kScale = 0.1f;		// �v���C���[���f���̊g�嗦
	constexpr float kMove = 1.0f;		// �v���C���[�ړ���
	constexpr float kVelocity = 3.0f;	// �W�����v�̍���
	constexpr float kGravity = -0.2f;	// �d��

	// �����蔻��
	constexpr float kCenterPosY = 12.0f;	// �v���C���[�̒��S�_�𒲐�
	constexpr float kWidth = 10.0f;			// ����
	constexpr float kHeight = 24.0f;		// �c��
	constexpr float kDepth = 5.0f;			// ���s���̕�

	// �W�����v�t���[��
	constexpr int kLittleJumpFrame = 10;	// ���W�����v
	constexpr int kMediumJumpFrame = 30;	// ���W�����v
	// �W�����v�̍���
	constexpr float kLittleJumpHeight = 0.5f;	// ���W�����v
	constexpr float kMediumJumpHeight = 0.8f;	// ���W�����v
	constexpr float kBigJumpHeight = 1.0f;		// ��W�����v
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player():
	m_currentState(State::Idle),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_move(VGet(0.0f, 0.0f, 0.0f)),
	m_angle(0.0f),
	m_jumpPower(0.0f),
	m_jumpFrame(0),
	m_isJump(false),
	m_cameraAngle(0.0f)
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
/// <param name="stage">�X�e�[�W�����Q��</param>
void Player::Update(Input& input, Stage& stage)
{
	// �v���C���[�̈ړ�����
	Move(input, stage);
	// �ړ���������v���C���[�̌������������肷��
	if (VSquareSize(m_move) > 0.0f)
	{
		m_angle = -atan2f(m_move.z, m_move.x) - DX_PI_F;
	}

	// �n�ʂɐڒn���Ă���ꍇ
	if (m_currentState != State::Jump)
	{
		m_jumpFrame = 0;
		m_move.y = kGravity;

		// ���n�������s��
		if (m_pos.y + m_jumpPower < OnHitFloor(stage))
		{
			m_pos = VGet(m_pos.x, OnHitFloor(stage), m_pos.z);
		}

		// �{�^������������W�����v��Ԃɂ���
		if (input.IsTriggered("jump"))
		{
			// y�������̑��x���Z�b�g
			m_currentState = State::Jump;
			m_isJump = true;
		}
	}

	// �W�����v�������s��
	if (m_currentState == State::Jump)
	{
		Jump(input, stage);
	}

	// �v���C���[�ʒu���X�V
	m_move.y = m_jumpPower;
	m_pos = VAdd(m_pos, m_move);
	MV1SetPosition(m_modelHandle, m_pos);

	// �v���C���[�̌X���𒲐�����
	UpdateAngle(stage);

	// �ړ��p�����[�^��ݒ肷��
	//VECTOR	upMoveVec;		// �����{�^���u���v����͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	//VECTOR	leftMoveVec;	// �����{�^���u���v����͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	//VECTOR	moveVec;		// ���̃t���[���̈ړ��x�N�g��
	//State prevState = m_currentState;
	//m_currentState = UpdateMoveParameterWithPad(input, upMoveVec, leftMoveVec, moveVec);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="drawDebug"></param>
void Player::Draw(DrawDebug& drawDebug)
{
	// 3D���f���\��
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG	// �f�o�b�O�\��
	// �v���C���[�ʒu�\��
	drawDebug.DrawPlayerInfo(m_pos);
	// �����蔻��`��
	drawDebug.DrawCubeCol(m_modelHandle, m_angle, 0x00ffff);
#endif
}


/// <summary>
/// ���������ۂ̏���
/// </summary>
/// <param name="stage"></param>
void Player::OnHit(Stage& stage)
{
#ifdef _DEBUG
	DrawString(0, 0, "��������", 0xffffff);
#endif

}


/// <summary>
/// �V��ɓ��������ۂ̏���
/// </summary>
void Player::OnHitRoof()
{
	// Y�������̑��x�𔽓]
	m_jumpPower = -m_jumpPower;
}


/// <summary>
/// ���ɓ��������ۂ̏���
/// </summary>
void Player::OnHitFloor()
{
	m_currentState = State::Idle;
	m_isJump = false;
}


/// <summary>
/// �������̏���
/// </summary>
void Player::OnFall()
{
	if (m_currentState != State::Jump)
	{
		// �W�����v��(�������j�ɂ���
		m_currentState = State::Jump;
	}
}


/// <summary>
/// ���݂̏�Ԃ�ݒ肷��
/// </summary>
/// <param name="input"></param>
/// <param name="upMoveVec"></param>
/// <param name="leftMoveVec"></param>
/// <param name="moveVec"></param>
/// <returns></returns>
Player::State Player::UpdateMoveParameterWithPad(const Input& input, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{


	return State();
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="input">����</param>
void Player::Move(Input& input, Stage& stage)
{
	m_move = VGet(0.0f, 0.0f, 0.0f);

	// �{�^������������ړ�
	if (input.IsPressing("up"))
	{
		m_move = VAdd(m_move, VGet(0.0f, 0.0f, kMove));
	}
	if (input.IsPressing("down"))
	{
		m_move = VAdd(m_move, VGet(0.0f, 0.0f, -kMove));
	}
	if (input.IsPressing("left"))
	{
		m_move = VAdd(m_move, VGet(-kMove, 0.0f, 0.0f));
	}
	if (input.IsPressing("right"))
	{
		m_move = VAdd(m_move, VGet(kMove, 0.0f, 0.0f));
	}

	// �΂߂̈ړ����x�����ɂ���
	if (VSize(m_move) > 0.0f)
	{
		m_move = VNorm(m_move);
		m_move = VScale(m_move, kMove);
	}

	// �ړ����������肷��
	MATRIX mtx = MGetRotY(-m_cameraAngle - DX_PI_F / 2);
	m_move = VTransform(m_move, mtx);

	// �����蔻������āA�V�������W��ۑ�����
	m_pos = stage.CheckCollision(*this, m_move);

	// �v���C���[�̃��f���̍��W���X�V����
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// �W�����v����
/// </summary>
/// <param name="input">����</param>
void Player::Jump(Input& input, Stage& stage)
{
	// 1�񂾂��W�����v����
	if (m_isJump)
	{
		// �W�����v�t���[���𑝂₷
		m_jumpFrame++;

		// �W�����v�̍����𒲐�����
		if (input.IsReleased("jump"))
		{
			static float jumpHeight = 0.0f;
			if (m_jumpFrame < kLittleJumpFrame)
			{
				jumpHeight = kLittleJumpHeight;
			}
			else if (m_jumpFrame < kMediumJumpFrame)
			{
				jumpHeight = kMediumJumpHeight;
			}
			else
			{
				jumpHeight = kBigJumpHeight;
			}
		}

		// �W�����v�͂����߂�
		m_jumpPower = kVelocity;
		m_isJump = false;
	}

	// �d�͂𑫂�
	m_jumpPower += kGravity;

	// ���n�������s��
	if (m_pos.y + m_jumpPower < OnHitFloor(stage))
	{
		m_pos.y = OnHitFloor(stage);
		m_currentState = State::Idle;
		m_isJump = false;
	}
}


/// <summary>
/// �v���C���[�̌X���𒲐�����
/// </summary>
void Player::UpdateAngle(Stage& stage)
{
	// �W�����v���͌X�����X�V���Ȃ�
	if (m_currentState == State::Jump) return;

	// �v���C���[��n�ʂɉ����ČX����
	// ���x�N�g�����쐬
	// y��
	VECTOR v3Up = VCross(stage.GetV3Vec1(), stage.GetV3Vec2());
	v3Up = VNorm(v3Up);

	// z��
	VECTOR v3Forward = VGet(cosf(-m_angle), 0.0f, sinf(-m_angle));

	// x��
	VECTOR v3Side = VCross(v3Up, v3Forward);
	v3Side = VNorm(v3Side);

	// �x�N�g���𒼌�������
	v3Forward = VCross(v3Side, v3Up);
	v3Forward = VNorm(v3Forward);

	// z����y���̕������Z�b�g����
	if (IsHitStage(stage))
	{
		// ���ʕ����ɓ��������ꍇ�̓v���C���[���X���Ȃ�
		v3Up = VGet(0.0f, 1.0f, 0.0f);
	}
	else
	{
		// �Ζʂɓ��������ꍇ�̓v���C���[���Ζʂɉ����ČX����
		// �㉺���]������
		v3Up = VScale(v3Up, -1);
	}

	MV1SetRotationZYAxis(m_modelHandle, v3Forward, v3Up, 0.0f);
}


/// <summary>
/// �n�ʂ̈ʒu����v���C���[��Y���W�����߂�
/// </summary>
/// <returns>�n�ʂ̍���</returns>
float Player::OnHitFloor(Stage& stage)
{
	// �n�ʂ̌X�΂̊O�ς��v�Z����
	VECTOR v3Normal = VCross(stage.GetV3Vec1(), stage.GetV3Vec2());

	// �X�e�[�W�̏�ʂɓ��������ꍇ
	if (IsHitStage(stage))
	{
		return stage.GetStagePos().y + MV1GetScale(stage.GetStageHandle()).y - m_jumpPower;
	}
	else // �n�ʂɓ��������ꍇ
	{
		return (-v3Normal.x * m_pos.x - v3Normal.z * m_pos.z) / v3Normal.y - m_jumpPower;
	}
}


/// <summary>
/// �X�e�[�W�Ƃ̏Փ˔�����s��
/// </summary>
bool Player::IsHitStage(Stage& stage)
{
	/*�v���C���[�ƒn�ʂ̓����蔻��*/
	// ���΃x�N�g�������߂�
	VECTOR v3SubAbs = VSub(m_pos, stage.GetStagePos());
	v3SubAbs = VGet(abs(v3SubAbs.x), abs(v3SubAbs.y), abs(v3SubAbs.z));

	// �Փˋ��������߂�
	// �Փˋ����͂��ꂼ��̑Ή������ӂ̒����𑫂���2�Ŋ���������
	VECTOR v3AddScale = VScale(VAdd(MV1GetScale(m_modelHandle), MV1GetScale(stage.GetStageHandle())), 0.5f);
	// TODO;�����蔻��͈̔͂��L����(������)
	v3AddScale = VAdd(v3AddScale, VGet(0.0f, 20.0f, 0.0f));

	// �e�����̓����蔻��
	bool isXHit = v3SubAbs.x < v3AddScale.x;
	bool isYHit = v3SubAbs.y < v3AddScale.y;
	bool isZHit = v3SubAbs.z < v3AddScale.z;

	if (isXHit && isYHit && isZHit) return true;

	return false;
}
