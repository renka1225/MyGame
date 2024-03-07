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
/// 初期化
/// </summary>
void Player::Init()
{
}


/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
	// ３Ｄモデルの位置を決定
	MV1SetPosition(m_handle, m_pos);
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(m_handle);
}


/// <summary>
/// 終了
/// </summary>
void Player::End()
{
}
