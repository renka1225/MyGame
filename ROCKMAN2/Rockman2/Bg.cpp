#include "Bg.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	// �w�i�̃X�N���[�����x
	constexpr int kSpeed = 10;

	// �w�i�摜�����[�v������ʒu
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

	if (pad & PAD_INPUT_LEFT) // ������������w�i�����Ɉړ�
	{
		m_pos.x -= kSpeed;
		if (m_pos.x < 0)
		{
			m_pos.x = kLoopPos;
		}

	}
	if (pad & PAD_INPUT_RIGHT) // ������������w�i���E�Ɉړ�
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
	// �w�i�̕`��
	DrawRectGraph(0, 0, m_pos.x, m_pos.y, Game::kScreenWidth, Game::kScreenHeight, m_handle, false);
}
