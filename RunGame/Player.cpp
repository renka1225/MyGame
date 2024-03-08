#include "Player.h"
#include "Input.h"

Player::Player():
	m_pos(VGet(0.0f, 0.0f, 0.0f))
{
	m_handle = MV1LoadModel("data/Duck.mv1");
}


Player::~Player()
{
	MV1DeleteModel(m_handle);
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
	if (input.IsPressing("left"))
	{
		m_pos.x -= 3;
	}
	else if (input.IsPressing("right"))
	{
		m_pos.x += 3;
	}
	else if (input.IsPressing("up"))
	{
		m_pos.y += 3;
	}
	else if (input.IsPressing("down"))
	{
		m_pos.y -= 3;
	}

	// �R�c���f���̈ʒu������
	MV1SetPosition(m_handle, m_pos);
}


/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(m_handle);
}


/// <summary>
/// �I��
/// </summary>
void Player::End()
{
}
