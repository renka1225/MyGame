#include "Bg.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	// ”wŒi‚ÌƒXƒNƒ[ƒ‹‘¬“x
	constexpr int kSpeed = 10;

	// ”wŒi‰æ‘œ‚ğƒ‹[ƒv‚³‚¹‚éˆÊ’u
	constexpr float kLoopPos = 500;
}

Bg::Bg():
	m_pos(0, 0),
	m_handle(-1)
{
}

Bg::~Bg()
{
}

void Bg::Init()
{

}

void Bg::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (pad & PAD_INPUT_LEFT) // ©‚ğ‰Ÿ‚µ‚½‚ç”wŒi‚ª¶‚ÉˆÚ“®
	{
		m_pos.x -= kSpeed;
		if (m_pos.x < 0)
		{
			m_pos.x = kLoopPos;
		}

	}
	if (pad & PAD_INPUT_RIGHT) // ¨‚ğ‰Ÿ‚µ‚½‚ç”wŒi‚ª‰E‚ÉˆÚ“®
	{
		m_pos.x += kSpeed;
		if (m_pos.x > kLoopPos)
		{
			m_pos.x = 0;
		}
	}
}

void Bg::Draw()
{
	// ”wŒi‚Ì•`‰æ
	DrawRectGraph(0, 0, m_pos.x, m_pos.y, Game::kScreenWidth, Game::kScreenHeight, m_handle, false);
}
