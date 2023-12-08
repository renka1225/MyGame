#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "SceneMain.h"
#include "ShotBuster.h"
#include "ShotMetal.h"
#include "ShotFire.h"
#include "ShotLineMove.h"
#include <cassert>

// Player�Ŏg�p����萔
namespace
{
	// �ړ����x
	constexpr float kSpeed = 1.0f;
	// �d��
	constexpr float kGravity = 0.5f;
	// �����x
	constexpr float kVelocity = -16.0f;

	// �v���C���[�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 64;

	// �_���[�W���o�̃t���[����
	constexpr int kDamageFrame = 60;

	// ���̍���
	constexpr int kFloorHeight = 500;

	// �v���C���[�̌��݈ʒu
	constexpr float kPosX = 500;
	constexpr float kPosY = 500;

	// �v���C���[��HP
	constexpr float kHp = 1;

	// �c�@
	constexpr int kLife = 2;
}


Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	m_pos(kPosX, kPosY),
	m_handle(-1),
	m_isRight(true),
	m_isJumpFlag(false),
	m_velocity(0),
	m_jumpFrame(0),
	m_hp(kHp),
	m_life(kLife),
	m_damageFrame(0),
	m_metalEnergy(28),
	m_fireEnergy(28),
	m_lineEnergy(28),
	m_keyState(0),
	m_pressTime(0),
	m_nowPressTime(0)
{
}

Player::~Player()
{
}

// ����������
void Player::Init()
{
	// ���݈ʒu
	m_pos.x = kPosX;
	m_pos.y = kPosY;
	// ����
	m_isRight = true;
	// �W�����v�t���O
	m_isJumpFlag = false;
	// HP
	m_hp = kHp;
	// �_���[�W�̃t���[����
	m_damageFrame = 0;
}

void Player::Update()
{
	// �_���[�W���o
	m_damageFrame--;
	if (m_damageFrame < 0)
	{
		m_damageFrame = 0;
	}

	// �p�b�h���g�p����
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �ړ���
	Vec2 move{ 0.0f, 0.0f };

	/*�����������獶�Ɉړ�*/
	if (pad & PAD_INPUT_LEFT)
	{
		move.x -= kSpeed;
		m_isRight = false;
	}

	/*������������E�Ɉړ�*/
	if (pad & PAD_INPUT_RIGHT)
	{
		move.x += kSpeed;
		m_isRight = true;
	}

	/*Space�ŃW�����v*/
   	if (Pad::IsTrigger(PAD_INPUT_10) && !m_isJumpFlag)
	{
		m_isJumpFlag = true;
		m_velocity = kVelocity; // �����x��ݒ�
	}

	// �W�����v��
	if (m_isJumpFlag)
	{		
		m_jumpFrame++;	// �W�����v�t���[���̍X�V
		
		// �{�^���𗣂����u�ԂɃW�����v����
		if (Pad::IsRelease(PAD_INPUT_10))
		{
			// �����x�̍X�V
			if (m_jumpFrame < 10) // ����������10�t���[���ȉ�
			{
				m_velocity = kVelocity * 0.5f; 
			}
			else if (m_jumpFrame < 30) // ����������30�t���[���ȉ�
			{
				m_velocity = kVelocity * 0.8f;  // �����x��ݒ肷��
			}
			else
			{
				m_velocity = kVelocity;  // �����x��ݒ肷��
			}
		}

		m_velocity += kGravity; // �����x�ɏd�͂𑫂�
		m_pos.y += m_velocity;	// ���݈ʒu�̍X�V

		// �n�ʂɒ��n������W�����v���I������
		if (m_pos.y >= kFloorHeight)
		{
			m_pos.y = kFloorHeight;
			m_isJumpFlag = false;	// �W�����v�t���O��������
			m_jumpFrame = 0;		// �W�����v�t���[����������
		}
	}

	// ��ʊO�ɏo�����ʓ��ɖ߂�
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
	}

	/*Z�L�[�Ńo�X�^�[����*/
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

	/*X�L�[�Ń��^������*/
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

	/*C�L�[�Ńt�@�C���[����*/
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

	/*A�L�[�ŃA�C�e��2������*/
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		if (m_lineEnergy > 0)
		{

			ShotLineMove* pShot = new ShotLineMove;

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
			m_lineEnergy = 0;
		}
	}

	m_pos += move; // ���ݒl�̍X�V
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight); // �����蔻��̍X�V
}

void Player::Draw()
{
	if (m_isRight) // �E�������Ă���ꍇ
	{
		DrawGraph(static_cast<float>(m_pos.x), static_cast<float>(m_pos.y), m_handle, false);
	}
	else // ���������Ă���ꍇ
	{
		DrawTurnGraph(static_cast<float>(m_pos.x), static_cast<float>(m_pos.y), m_handle, false);
	}

	// �_���[�W���o
	// 2�t���[���Ԋu�ŕ\����\����؂�ւ���
	if (m_damageFrame % 4 >= 2) return;

#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(0x0000ff, false);
#endif
}

void Player::OnDamage()
{
	// �_���[�W���o���͖��G��ԂɂȂ�
	if (m_damageFrame > 0) return;

	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;

	// HP�����炷
	m_hp--;
}
