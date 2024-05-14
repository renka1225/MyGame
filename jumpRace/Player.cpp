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
	m_angle(0.0f),
	m_clearStagingTime(0),
	m_isClear(false)
{
	m_model = MV1DuplicateModel(m_pModel->GetPlayerModel());

	// 3D���f���̃T�C�Y����
	MV1SetScale(m_model, VGet(kScale, kScale, kScale));

	// �V���h�E�}�b�v�n���h���̍쐬
	shadowMapHandle = MakeShadowMap(256, 256);

	// �V���h�E�}�b�v�őz�肷�郉�C�g�̕�����ݒ肷��
	SetShadowMapLightDirection(shadowMapHandle, VGet(0.0f, 0.0f, -3.0f));
	// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ肷��
	SetShadowMapDrawArea(shadowMapHandle, VGet(-1000.0f, -1.0f, -1000.0f), VGet(1000.0f, 1000.0f, 1000.0f));
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	// �V���h�E�}�b�v�̍폜
	DeleteShadowMap(shadowMapHandle);
	MV1DeleteModel(m_model);
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
/// <param name="input">�{�^������</param>
void Player::Update(Input& input)
{
	// �N���A��
	if (m_isClear)
	{
		m_clearStagingTime++;
	}

	// �d�͂𑫂�
	m_pos = VAdd(m_pos, VGet(0.0f, kGravity, 0.0f));

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

	// �R�c���f���̕`��
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
	m_pos = VAdd(m_pos, VGet(0.0f, kJumpHeight, kMoveZ));
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
