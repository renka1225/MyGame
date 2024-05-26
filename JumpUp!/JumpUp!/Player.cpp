#include "Player.h"
#include "Stage.h"
#include "DrawDebug.h"
#include "Input.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player():
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_move(VGet(0.0f, 0.0f, 0.0f)),
	m_angle(0.0f),
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
	m_modelHandle = -1;
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
void Player::Update(Input& input, std::shared_ptr<Stage> stage)
{
	m_stage = stage;

	// �v���C���[�̈ړ�����
	Move(input);

	// �W�����v����
	if (m_isJump)	// �W�����v���̏ꍇ
	{
		Jump(input);
	}
	else // �n�ʂɐڒn���Ă���ꍇ
	{
		m_jumpFrame = 0;
		m_pos = VGet(m_pos.x, GroundHeight(), m_pos.z);

		// �{�^������������W�����v��Ԃɂ���
		if (input.IsTriggered("jump"))
		{
			// �����x�𑫂�
			m_move = VAdd(m_move, VGet(0.0f, kVelocity, 0.0f));
			m_isJump = true;
		}
	}
	
	// ���n����
	if (m_pos.y + m_move.y < GroundHeight())
	{
		m_pos.y = GroundHeight();
		m_isJump = false;
	}

	// �v���C���[�ʒu�A�p�x���X�V
	m_pos = VAdd(m_pos, m_move);
	MV1SetPosition(m_modelHandle, m_pos);
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle, 0.0f));

	// �v���C���[�̌X���𒲐�����
	UpdateAngle();
}


/// <summary>
/// �`��
/// </summary>
void Player::Draw(DrawDebug& drawDebug)
{
#ifdef _DEBUG	// �f�o�b�O�\��
	// �v���C���[�ʒu�\��
	drawDebug.DrawPlayerInfo(m_pos);
	// �����蔻��`��
	drawDebug.DrawCubeCol(VGet(m_pos.x, m_pos.y + kCenterPosY, m_pos.z), kWidth, kHeight, kDepth, 0x00ffff);
#endif

	// 3D���f���\��
	MV1DrawModel(m_modelHandle);
}


/// <summary>
/// �ړ�����
/// </summary>
/// <param name="input">����</param>
void Player::Move(Input& input)
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

	// �ړ���������v���C���[�̌������������肷��
	if (VSquareSize(m_move) > 0.0f)
	{
		m_angle = -atan2f(m_move.z, m_move.x) - DX_PI_F;
	}
}


/// <summary>
/// �W�����v����
/// </summary>
/// <param name="input">����</param>
void Player::Jump(Input& input)
{
	// �W�����v�t���[���𑝂₷
	m_jumpFrame++;

	// �{�^���𗣂����u�ԃW�����v
	if (input.IsReleased("jump"))
	{
		// �W�����v�̍��������߂�
		float jumpHeight = 0.0f;
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
		m_move = VScale(VGet(0.0f, m_move.y, 0.0f), jumpHeight);
	}

	// �d�͂𑫂�
	m_move = VAdd(m_move, VGet(0.0f, kGravity, 0.0f));
}


/// <summary>
/// �v���C���[�̌X���𒲐�����
/// </summary>
void Player::UpdateAngle()
{
	// �v���C���[��n�ʂɉ����ČX����
	// ���x�N�g�����쐬
	// y��
	VECTOR v3Up = VCross(m_stage->GetV3Vec1(), m_stage->GetV3Vec2());
	v3Up = VNorm(v3Up);
	// �㉺���]������
	v3Up = VScale(v3Up, -1);

	// z��
	VECTOR v3Forward = VGet(cosf(-m_angle), 0.0f, sinf(-m_angle));

	// x��
	VECTOR v3Side = VCross(v3Up, v3Forward);
	v3Side = VNorm(v3Side);

	// �x�N�g���𒼌�������
	v3Forward = VCross(v3Side, v3Up);
	v3Forward = VNorm(v3Forward);

	// z����y���̕������Z�b�g����
	MV1SetRotationZYAxis(m_modelHandle, v3Forward, v3Up, 0.0f);
}


/// <summary>
/// �n�ʂ̍�������v���C���[��Y���W�����߂�
/// </summary>
/// <returns>�n�ʂ̍���</returns>
float Player::GroundHeight()
{
	// �n�ʂ̌X�΂̊O�ς��v�Z����
	VECTOR v3Normal = VCross(m_stage->GetV3Vec1(), m_stage->GetV3Vec2());
	// y���W�����߂�
	return (-v3Normal.x * m_pos.x - v3Normal.z * m_pos.z) / v3Normal.y;
}
