#include "Player.h"
#include "ManagerModel.h"
#include "WorldSprite.h"
#include "Input.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player(std::shared_ptr<ManagerModel> pModel) :
	m_pModel(pModel),
	m_pos(VGet(kInitPosX, kInitPosY, kInitPosZ)),
	m_move(VGet(0.0f, 0.0f, 0.0f)),
	m_isClear(false),
	m_clearStagingTime(0),
	m_angle(0.0f)
{
	m_model = MV1DuplicateModel(m_pModel->GetPlayerModel());

	// 3D���f���̃T�C�Y����
	MV1SetScale(m_model, VGet(kScale, kScale, kScale));
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	MV1DeleteModel(m_model);
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">�{�^������</param>
void Player::Update(Input& input)
{
	// �N���A��
	if (m_isClear)
	{
		m_clearStagingTime++;
	}

	// �d�͂𑫂�
	m_move = VGet(0.0f, kGravity, 0.0f);
	m_pos = VAdd(m_pos, m_move);

	// �n�ʂɒ��n������
	if (m_pos.y < kInitPosX)
	{
		m_pos = VGet(0.0f, 0.0f, m_pos.z);
	}

	// �|�W�V�����ݒ�
	MV1SetPosition(m_model, m_pos);
}


/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	// �v���C���A�v���C���[�̉��ɉe��`�悷��
	if (!m_isClear)
	{
		int shadowColor;
		if (m_pos.y > 0.0f)	// �v���C���[�̍����ɂ���ĉe�F��ς���
		{
			shadowColor = 0x7dbd7d;
		}
		else
		{
			shadowColor = 0x008080;
		}
		SetDrawBlendMode(DX_BLENDMODE_MULA, 255);
		DrawCircle(kShadowPosX, kShadowPosY, kShadowRadius, shadowColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	// ���f���̕`��
	MV1DrawModel(m_model);

#ifdef _DEBUG
	// MEMO:�v���C���[���W�`��
	DrawFormatString(0, 60, 0xffffff, "�v���C���[���W(x:%f,y:%f,z:%f)\n", m_pos.x, m_pos.y, m_pos.z);
#endif
}


/// <summary>
/// �v���C���[���ړ�������
/// </summary>
void Player::Move()
{
	m_move = VGet(0.0f, kJumpHeight, kMoveZ);
	m_pos = VAdd(m_pos, m_move);
}


/// <summary>
/// �N���A���̉��o
/// </summary>
void Player::ClearStaging()
{
	if (!m_isClear)
	{
		m_pos = VGet(kClearInitPosX, 0.0f, kClearInitPosZ);	// �v���C���[���ړ�������
		m_isClear = true;
	}
	else if(m_clearStagingTime >= kClearStagingStartTime)
	{
		// �v���C���[����]������
		m_angle += kRotRad;
		MV1SetRotationXYZ(m_model, VGet(0.0f, m_angle * DX_PI_F / 180.0f, 0.0f));

		// ���t���[�����ƂɃW�����v������
		int jumpFrame = m_clearStagingTime % 40;
		if (jumpFrame == kJumpFrame)
		{
			m_pos = VAdd(m_pos, VGet(0.0f, kJumpHeight, 0.0f));
		}
	}
}
