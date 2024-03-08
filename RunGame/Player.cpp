#include "Player.h"

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
void Player::Update()
{
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
