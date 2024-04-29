#include "Player.h"
#include "ManagerModel.h"
#include "Input.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_pos(VGet(kInitPosX, kInitPosY, kInitPosZ))
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
//#ifdef _DEBUG
//	// MEMO:�f�o�b�O�ړ��p
//	if (input.IsPressing("down"))
//	{
//		m_pos.z -= 1.0f;
//	}
//	if (input.IsPressing("up"))
//	{
//		m_pos.z += 1.0f;
//	}
//#endif

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
