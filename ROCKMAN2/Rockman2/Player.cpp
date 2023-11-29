#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "SceneMain.h"
#include "ShotBuster.h"
#include "ShotMetal.h"
#include "ShotFire.h"
#include <cassert>

// Player�Ŏg�p����萔
namespace
{
	// �ړ����x
	constexpr float kSpeed = 3.0f;
	// �W�����v���x
	constexpr float kJumpSpeed = -10.0f;
	// �W�����v�̒���
	constexpr float kJumpTime = 10.0f;
	// �������x
	constexpr float kFallSpeed = 8.0f;

	// �v���C���[�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 64;

	// ���̍���
	constexpr int kFloorHeight = 300;
}


Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	m_pos(Game::kScreenWidth / 2, kFloorHeight),
	m_handle(-1),
	m_isRight(true),
	m_jumpFrame(0),
	m_isJumpFlag(false),
	m_hp(28),
	m_life(2),
	m_metalEnergy(28),
	m_fireEnergy(28),
	m_pressTime(0)
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

	// �����������獶�Ɉړ�
	if (pad & PAD_INPUT_LEFT)
	{
		//move.x -= kSpeed;
		m_isRight = false;

	}

	// ������������E�Ɉړ�
	if (pad & PAD_INPUT_RIGHT)
	{
		//move.x += kSpeed;
		m_isRight = true;
	}

	// Space�ŃW�����v
	if (Pad::IsTrigger(PAD_INPUT_10))
	{
		if (!m_isJumpFlag && m_jumpFrame <= 0)
		{
			m_isJumpFlag = true;
			m_jumpFrame = kJumpTime; // �W�����v�̒���
			move.y = kJumpSpeed * kJumpTime;
		}
		else
		{
			move.y += kFallSpeed;	// ������������
			m_jumpFrame--;
		}
	}

	// Z�L�[�Ńo�X�^�[����
	if(Pad::IsTrigger(PAD_INPUT_1))
	{
		ShotBuster* pShot = new ShotBuster;

		// �V�����e�𐶐�����
		pShot->Init();
		pShot->SetMain(m_pMain);
		pShot->SetPlayer(this);
		pShot->Start(GetPos());
		// �ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
		m_pMain->AddShot(pShot);
	}

	// X�L�[�Ń��^������
	if (Pad::IsTrigger(PAD_INPUT_2))
	{
		if (m_metalEnergy > 0)
		{
			// �e�G�l���M�[��0.25���炷
			m_metalEnergy -= 0.25f;

			ShotMetal* pShot = new ShotMetal;

			// �V�����e�𐶐�����
			pShot->Init();
			pShot->SetMain(m_pMain);
			pShot->SetPlayer(this);
			pShot->Start(GetPos());
			// �ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
			m_pMain->AddShot(pShot);
		}
		else
		{
			m_metalEnergy = 0;
		}
	}

	// C�L�[�Ńt�@�C���[����
	// C�L�[�������ꂽ�u�Ԃ��擾
	if (Pad::IsTrigger(PAD_INPUT_3))
	{
		m_pressTime = GetNowCount();
	}
	// c�L�[��������Ă��邩����
	if (Pad::IsPress(PAD_INPUT_3))
	{
		m_nowPressTime = GetNowCount() - m_pressTime; // �{�^���������ė����܂ł̎���
	}
	// c�L�[�������ꂽ�u�Ԃ𔻒�
	if (Pad::IsRelease(PAD_INPUT_3))
	{
		if (m_fireEnergy > 0) // �e�G�l���M�[��0�ȏ�
		{
			if (m_nowPressTime < 2000) // ���������Ԃ�2�b�ȉ�
			{
				m_fireEnergy--; // �e�G�l���M�[��1���炷
			}
			else if (m_nowPressTime < 5000) // ���������Ԃ�5�b�ȉ�
			{
				if (m_fireEnergy - 6 < 0) // �e�G�l���M�[������Ȃ��ꍇ
				{
					m_fireEnergy--; // �e�G�l���M�[��1���炷
				}
				else
				{
					m_fireEnergy -= 6; // �e�G�l���M�[��6���炷
				}
			}
			else // ���������Ԃ�5�b�ȏ�
			{
				if (m_fireEnergy - 10 < 0) // �e�G�l���M�[������Ȃ��ꍇ
				{
					m_fireEnergy--; // �e�G�l���M�[��1���炷
				}
				else
				{
					m_fireEnergy -= 10; // �e�G�l���M�[��10���炷
				}
			}

			// �V�����e�𐶐�����
			ShotFire* pShot = new ShotFire;
			pShot->Init();
			pShot->SetMain(m_pMain);
			pShot->SetPlayer(this);
			pShot->Start(GetPos());
			// �ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
			m_pMain->AddShot(pShot);
		}
		else // �e�G�l���M�[��0�ȉ�
		{
			m_fireEnergy = 0; // ���݂̒e�G�l���M�[��0�ɂ���
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
}

void Player::Draw()
{
	if (m_isRight) // �E�������Ă���ꍇ
	{
		DrawGraph(m_pos.x, m_pos.y, m_handle, false);
	}
	else // ���������Ă���ꍇ
	{
		DrawTurnGraph(m_pos.x, m_pos.y, m_handle, false);
	}

#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(0x0000ff, false);
	// ���������Ԃ̕\��
	DrawFormatString(8, 50, 0xffffff, "����������:%d", m_nowPressTime);
#endif
}
