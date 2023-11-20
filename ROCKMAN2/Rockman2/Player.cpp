#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "SceneMain.h"
#include "ShotBuster.h"
#include <cassert>

// Player�Ŏg�p����萔
namespace
{
	// �ړ����x
	constexpr float kSpeed = 3.0f;
	// �W�����v���x
	constexpr float kJumpSpeed = -10.0f;
	// �W�����v�̒���
	constexpr float kJumpTime = 5.0f;
	// �d��
	constexpr float kGravity = 5.0f;

	// �T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// ���̍���
	constexpr int kFloorHeight = Game::kScreenHeight / 2;
}


Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	m_pos(Game::kScreenWidth / 2, kFloorHeight),
	m_handle(-1),
	m_jumpFrame(0),
	m_isJumpFlag(false),
	m_hp(28),
	m_life(2)
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

	Vec2 move{ 0.0f, kGravity }; // �ړ���


	if (pad & PAD_INPUT_LEFT) // �����������獶�Ɉړ�
	{
		move.x -= kSpeed;
	}
	if (pad & PAD_INPUT_RIGHT) // ������������E�Ɉړ�
	{
		move.x += kSpeed;
	}

	if (pad & PAD_INPUT_10)
	{
		if (!m_isJumpFlag && m_jumpFrame <= 0)
		{
			m_isJumpFlag = true;
			m_jumpFrame = kJumpTime; // �W�����v�̒���
			move.y = kJumpSpeed * kJumpTime;
		}
		else
		{
			move.y += kGravity;	// ������������
			m_jumpFrame--;
		}
	}
	
	if (kFloorHeight < m_pos.y) // ����艺�Ɉړ������珰��ɖ߂�
	{
		m_pos.y = kFloorHeight;
		m_jumpFrame = 0;
		m_isJumpFlag = false;
	}
	if(m_pos.y < 0) // ��ʊO�ɏo�����ʓ��ɖ߂�
	{
		m_pos.y = 0;
	}

	m_pos += move; // ���ݒl�̍X�V
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight); // �����蔻��̍X�V

	// ���b�N�o�X�^�[����
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// �������̊m��
		ShotBuster* pShot = new ShotBuster;

		pShot->Init();
		pShot->SetMain(m_pMain);
		pShot->SetPlayer(this);
		pShot->Start(GetPos());

		// �X�V�⃁�����̉����SceneMain���s��
		m_pMain->AddShot(pShot);
	}
}

void Player::Draw()
{
	DrawGraph(m_pos.x, m_pos.y, m_handle, false);

#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(0x0000ff, false);
#endif
}
