#include "Player.h"
#include "Input.h"
#include "ManagerModel.h"

/// <summary>
/// �萔
/// </summary>
namespace
{
	// �ړ���
	constexpr float kMove = 0.5f;
	// �d��
	constexpr float kGravity = 0.5f;
	// �����x
	constexpr float kVelocity = 10.0f;
	// Y�������̌���
	constexpr float kDirY = -90.0f * DX_PI_F / 180.0f;
	// �T�C�Y
	constexpr float kScale = 0.5f;

	// �n�ʂ̍���
	constexpr float kGroundHeight = 0.0f;
}

/// <summary>
/// �W�����v�֘A�̒萔
/// </summary>
namespace Jump
{
	// �W�����v�t���[��
	constexpr int kLittleJumpFrame = 10;		// ���W�����v
	constexpr int kMediumJumpFrame = 30;		// ���W�����v
	// �W�����v�̍���
	constexpr float kLittleJumpHeight = 0.5f;	// ���W�����v
	constexpr float kMediumJumpHeight = 0.8f;	// ���W�����v
	constexpr float kBigJumpHeight = 1.0f;		// ��W�����v
}

Player::Player(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_pos(VGet(0.0f, kGroundHeight, 0.0f)),
	m_move(VGet(0.0f, 0.0f, 0.0f)),
	m_isJump(false),
	m_jumpFrame(0)
{
	m_modelHandle = MV1DuplicateModel(m_pModel->GetPlayerHandle());
}


/// <summary>
/// ������
/// </summary>
void Player::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
void Player::Update(Input& input)
{
	// ���t���[���E�Ɉړ�
	m_pos = VAdd(m_pos, VGet(kMove, 0.0f, 0.0f));

	if (m_isJump)	// �W�����v��
	{
		Jump(input);
	}
	else			// ���n��
	{
		m_jumpFrame = 0;
		m_isJump = false;

		// �W�����v�J�n
		if (input.IsTriggered("jump"))
		{
			m_isJump = true;
			m_move = VAdd(m_move, VGet(0.0f, kVelocity, 0.0f));
		}
	}

	// ���n����
	VECTOR rangeGround = VSub(m_pos, VGet(0.0f, kGroundHeight, 0.0f));	// �n�ʂ܂ł̋���
	if (rangeGround.y < 0.0f)
	{
		m_pos.y = kGroundHeight;
		m_move.y = 0;
		m_isJump = false;
	}

	// 3D���f���̃T�C�Y������
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	// 3D���f����Y�������ɉ�]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, kDirY, 0.0f));
	// 3D���f���̈ʒu���X�V
	m_pos = VAdd(m_pos, m_move);
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG
	// MEMO:�v���C���[�̍��W�`��
	DrawFormatString(0, 20, 0xffffff, "�v���C���[���W(x:%f,y:%f,z:%f)\n", m_pos.x, m_pos.y, m_pos.z);
	// MEMO:�n�ʈʒu�`��
	DrawLine3D(VGet(-100, kGroundHeight, 0), VGet(10000, kGroundHeight, 0), 0x0000ff);
#endif

}


/// <summary>
/// �I��
/// </summary>
void Player::End()
{
}


/// <summary>
/// �W�����v����
/// </summary>
void Player::Jump(Input& input)
{
	m_jumpFrame++;

	// �{�^���𗣂����u�ԃW�����v
	if (input.IsReleased("jump"))
	{
		// �W�����v�̍��������߂�
		float jumpHeight;
		if (m_jumpFrame < Jump::kLittleJumpFrame)
		{
			jumpHeight = Jump::kLittleJumpHeight;
		}
		else if(m_jumpFrame < Jump::kMediumJumpFrame)
		{
			jumpHeight = Jump::kMediumJumpHeight;
		}
		else
		{
			jumpHeight = Jump::kBigJumpHeight;
		}
		m_move.y = VDot(m_move, VGet(0.0f,jumpHeight, 0.0f));
	}

	m_move = VSub(m_move, VGet(0.0f, kGravity, 0.0f));
}