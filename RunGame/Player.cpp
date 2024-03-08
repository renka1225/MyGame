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
/// ‰Šú‰»
/// </summary>
void Player::Init()
{
}


/// <summary>
/// XV
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

	// ‚R‚cƒ‚ƒfƒ‹‚ÌˆÊ’u‚ğŒˆ’è
	MV1SetPosition(m_handle, m_pos);
}


/// <summary>
/// •`‰æ
/// </summary>
void Player::Draw()
{
	// ‚R‚cƒ‚ƒfƒ‹‚Ì•`‰æ
	MV1DrawModel(m_handle);
}


/// <summary>
/// I—¹
/// </summary>
void Player::End()
{
}
