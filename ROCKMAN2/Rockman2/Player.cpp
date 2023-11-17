#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include <cassert>

// Playerで使用する定数
namespace
{
	// プレイヤーの移動速度
	constexpr float kSpeed = 3.0f;
	// プレイヤーの落下速度
	constexpr float kFallSpeed = 8.0f;
	// プレイヤーのジャンプ速度
	constexpr float kJumpSpeed = 4.0f;

	// プレイヤーのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// 床の高さ
	constexpr int kFloorHeight = Game::kScreenHeight / 2;
}


Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	m_handle(-1),
	m_pos(Game::kScreenWidth / 2, kFloorHeight),
	isJumpFlag(false)
{
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

	Vec2 move{ 0.0f, kFallSpeed }; // 移動量


	if (pad & PAD_INPUT_4) // Aキーを押したら左に移動
	{
		move.x -= kSpeed;
	}
	if (pad & PAD_INPUT_6) // Dキーを押したら右に移動
	{
		move.x += kSpeed;
	}
	if (pad & PAD_INPUT_10) // spaceキーを押したらジャンプする
	{
		// ジャンプ中はジャンプできないようにする
		if (isJumpFlag == false)
		{
			move.y *= -kJumpSpeed; // ジャンプ分移動する
			isJumpFlag = true;
		}
	}

	if (kFloorHeight < m_pos.y) // 床より下に移動したら床上に戻す
	{
		m_pos.y = kFloorHeight;
		isJumpFlag = false;
	}
	else if(m_pos.y < 0) // 画面外に出たら画面内に戻す
	{
		m_pos.y = 0;
	}

	m_pos += move; // 現在値の更新

}

void Player::Draw()
{
	DrawGraph(m_pos.x, m_pos.y, m_handle, false);

}
