#include "Player.h"
#include "Input.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player():
	m_pos(VGet(kInitPosX, kInitPosY, kInitPosZ)),
	m_model(-1)
{
	m_model = MV1LoadModel("data/Model/duck.mv1");

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
	m_pos = VAdd(m_pos, VGet(0.0f, 0.0f, kMove));
}
