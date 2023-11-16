#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include <cassert>

// Playerで使用する定数
namespace
{
	// プレイヤーの移動速度
	constexpr float kSpeed = 3.0f;

	// プレイヤーのサイズ
	constexpr int kWidth = 64;
	constexpr int kHeight = 64;
}


Player::Player() :
	m_playerHandle(-1),
	m_pos(Game::kScreenWidth / 2, Game::kScreenHeight - kWidth)
{
	// グラフィックのロード
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);
}

Player::~Player()
{
}

void Player::Init()
{

}

void Player::Update()
{
	// パッドの十字キーを使用してプレイヤーを移動させる
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	Vec2 move{ 0.0f, 0.0f }; // 移動量を持つ

	if (pad & PAD_INPUT_LEFT)
	{
		move.x -= kSpeed;
	}
	if (pad & PAD_INPUT_RIGHT)
	{
		move.x += kSpeed;
	}

	m_pos += move; // 現在値の更新
}

void Player::Draw()
{
	DrawGraph(100, 100, m_playerHandle, FALSE);
}
