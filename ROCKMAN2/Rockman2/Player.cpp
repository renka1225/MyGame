#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include <cassert>

// Player�Ŏg�p����萔
namespace
{
	// �v���C���[�̈ړ����x
	constexpr float kSpeed = 3.0f;

	// �v���C���[�̃T�C�Y
	constexpr int kWidth = 64;
	constexpr int kHeight = 64;
}


Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	m_handle(-1),
	m_pos(Game::kScreenWidth / 2, Game::kScreenHeight - kWidth * 2)
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
	// �p�b�h�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	Vec2 move{ 0.0f, 0.0f }; // �ړ��ʂ�����

	if (pad & PAD_INPUT_LEFT)
	{
		move.x -= kSpeed;
	}
	if (pad & PAD_INPUT_RIGHT)
	{
		move.x += kSpeed;
	}

	m_pos += move; // ���ݒl�̍X�V
}

void Player::Draw()
{
}
