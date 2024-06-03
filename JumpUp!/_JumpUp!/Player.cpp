#include "Player.h"
#include "MyLib.h"
#include "Stage.h"
#include "DrawDebug.h"
#include "Input.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player():
	Collidable(Tag::Player),
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
void Player::Init(std::shared_ptr<Physics> physics)
{
	// ���g�̕������o�^
	physics->Entry(this);
	// ���������̏�����
	//m_rigidbody.Init();
	//m_rigidbody.SetPos(m_pos);
	//m_rigidbody.SetScale(VGet(kScale, kScale, kScale));

	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// ������
/// </summary>
void Player::Final(std::shared_ptr<Physics> physics)
{
	// �������o�^����
	physics->Exit(this);
}


/// <summary>
/// �X�V
/// </summary>
void Player::Update(Input& input, Stage& stage)
{
	// �v���C���[�̈ړ�����
	Move(input);

	if (m_isJump)	// �W�����v���̏ꍇ
	{
		// �W�����v�������s��
		Jump(input);
		// ���n�������s��
		if (m_pos.y + m_move.y < OnHitFloor(stage))
		{
			m_pos.y = OnHitFloor(stage);
			m_isJump = false;
		}
	}
	else // �n�ʂɐڒn���Ă���ꍇ
	{
		m_jumpFrame = 0;
		// �v���C���[�̈ʒu�𒲐�
		m_pos = VGet(m_pos.x, OnHitFloor(stage), m_pos.z);
		
		// �{�^������������W�����v��Ԃɂ���
		if (input.IsTriggered("jump"))
		{
			// �����x�𑫂�
			m_move = VAdd(m_move, VGet(0.0f, 0.0f, 0.0f));
			m_isJump = true;
		}
	}

	// �v���C���[�ʒu�A�p�x���X�V
	m_pos = VAdd(m_pos, m_move);
	MV1SetPosition(m_modelHandle, m_pos);

	// �v���C���[�̌X���𒲐�����
	UpdateAngle(stage);

	// �X�e�[�W�Ƃ̓����蔻��
	if (IsHitStage(stage))
	{
		OnHit(stage);
	}
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

	// ���x���Z�b�g����
	m_rigidbody.SetVelocity(m_move);

	// �ړ����������肷��
	MATRIX mtx = MGetRotY(-m_cameraAngle - DX_PI_F / 2);
	m_move = VTransform(m_move, mtx);

	// �ړ���������v���C���[�̌������������肷��
	if (!m_isJump && VSquareSize(m_move) > 0.0f)
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
		float jumpHeight = kVelocity;
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
		//m_move = VScale(VGet(0.0f, m_move.y, 0.0f), jumpHeight);
		m_move = VGet(0, jumpHeight, 0);
	}

	// �d�͂𑫂�
	m_move = VAdd(m_move, VGet(0.0f, kGravity, 0.0f));
}


/// <summary>
/// �v���C���[�̌X���𒲐�����
/// </summary>
void Player::UpdateAngle(Stage& stage)
{
	// �W�����v���͌X�����X�V���Ȃ�
	if (m_isJump) return;

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
	if (IsHitStage(stage)) // �X�e�[�W�̏�ʂɓ��������ꍇ
	{
		return stage.GetStagePos().y + MV1GetScale(stage.GetStageHandle()).y;
	}
	else // �n�ʂɓ��������ꍇ
	{
		return (-v3Normal.x * m_pos.x - v3Normal.z * m_pos.z) / v3Normal.y;
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


/// <summary>
/// �Փ˂����Ƃ��̏���
/// </summary>
void Player::OnHit(Stage& stage)
{
#ifdef _DEBUG
	DrawString(0, 40, "��������", 0xffffff);
#endif

	// TODO:���������ꏊ�ɂ���Ĉʒu��ς���

	// �X�e�[�W�ʒu���擾����
	VECTOR stagePos = stage.GetStagePos();

	// �����瓖���������`�F�b�N����
	m_pos.x += m_move.x;
	if (m_move.x > 0.0f)
	{
		m_pos.x = stagePos.x - MV1GetScale(stage.GetStageHandle()).x * 0.5f;
	}
	else if (m_move.x < 0.0f)
	{
		m_pos.x = stagePos.x + MV1GetScale(stage.GetStageHandle()).x * 0.5f;
	}

	// �c���瓖���������`�F�b�N����
	/*m_pos.y += m_move.y;
	if (m_move.y > 0.0f)
	{
		m_pos.y = stagePos.y - MV1GetScale(stage.GetStageHandle()).y * 0.5f;
		m_move.y *= -1.0f;
	}
	else if (m_move.y < 0.0f)
	{
		m_pos.y = stagePos.y + MV1GetScale(stage.GetStageHandle()).y * 0.5f;
	}*/
}