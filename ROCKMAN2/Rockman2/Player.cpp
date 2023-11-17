#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include <cassert>

// Player�Ŏg�p����萔
namespace
{
	// �v���C���[�̈ړ����x
	constexpr float kSpeed = 3.0f;
	// �v���C���[�̗������x
	constexpr float kFallSpeed = 8.0f;
	// �v���C���[�̃W�����v���x
	constexpr float kJumpSpeed = 4.0f;

	// �v���C���[�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// ���̍���
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

	// �p�b�h�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	Vec2 move{ 0.0f, kFallSpeed }; // �ړ���


	if (pad & PAD_INPUT_4) // A�L�[���������獶�Ɉړ�
	{
		move.x -= kSpeed;
	}
	if (pad & PAD_INPUT_6) // D�L�[����������E�Ɉړ�
	{
		move.x += kSpeed;
	}
	if (pad & PAD_INPUT_10) // space�L�[����������W�����v����
	{
		// �W�����v���̓W�����v�ł��Ȃ��悤�ɂ���
		if (isJumpFlag == false)
		{
			move.y *= -kJumpSpeed; // �W�����v���ړ�����
			isJumpFlag = true;
		}
	}

	if (kFloorHeight < m_pos.y) // ����艺�Ɉړ������珰��ɖ߂�
	{
		m_pos.y = kFloorHeight;
		isJumpFlag = false;
	}
	else if(m_pos.y < 0) // ��ʊO�ɏo�����ʓ��ɖ߂�
	{
		m_pos.y = 0;
	}

	m_pos += move; // ���ݒl�̍X�V

}

void Player::Draw()
{
	DrawGraph(m_pos.x, m_pos.y, m_handle, false);

}
