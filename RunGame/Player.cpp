#include "Player.h"
#include "Map.h"
#include "Input.h"
#include "ManagerModel.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pModel">3D���f��</param>
Player::Player(std::shared_ptr<ManagerModel> pModel, std::shared_ptr<Map> pMap):
	m_pModel(pModel),
	m_pMap(pMap),
	m_pos(VGet(kInitPosX, kGroundHeight, 0.0f)),
	m_move(VGet(0.0f, 0.0f, 0.0f)),
	m_isJump(false),
	m_jumpFrame(0)
{
	m_modelHandle = MV1DuplicateModel(m_pModel->GetPlayerHandle());
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
	// �����Ȃ�
}


/// <summary>
/// �X�V
/// </summary>
void Player::Update(Input& input)
{
	// 3D���f���̃T�C�Y����
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	// 3D���f����]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, kDirY, 0.0f));

	// �E�Ɉړ�
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
	if (m_pos.y < 0.0f)
	{
		m_pos.y = kGroundHeight;
		m_move.y = 0;
		m_isJump = false;
	}

	// 3D���f���̈ʒu���X�V
	m_pos = VAdd(m_pos, m_move);
	MV1SetPosition(m_modelHandle, m_pos);

	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y + kColPosAdjustment, m_pos.z, kWidth, kHeight);
}


/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG
	// MEMO:�v���C���[���W�`��
	DrawFormatString(0, 20, 0xffffff, "�v���C���[���W(x:%f,y:%f,z:%f)\n", m_pos.x, m_pos.y, m_pos.z);
	// MEMO:�����蔻��̕\��
	m_colRect.Draw(0x00fffff, false);
#endif

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
		if (m_jumpFrame < kLittleJumpFrame)
		{
			jumpHeight = kLittleJumpHeight;
		}
		else if(m_jumpFrame < kMediumJumpFrame)
		{
			jumpHeight = kMediumJumpHeight;
		}
		else
		{
			jumpHeight = kBigJumpHeight;
		}
		m_move.y = VDot(m_move, VGet(0.0f,jumpHeight, 0.0f));
	}

	m_move = VSub(m_move, VGet(0.0f, kGravity, 0.0f));
}