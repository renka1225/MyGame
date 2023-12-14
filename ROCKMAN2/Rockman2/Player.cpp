#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "Bg.h"
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
	constexpr float kVelocity = -10.0f;

	// �v���C���[�̃T�C�Y
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 64;

	// �}�b�v�`�b�v�̃T�C�Y
	constexpr int kMapWidth = 32;
	constexpr int kMapHeight = 32;

	// �_���[�W���o�̃t���[����
	constexpr int kDamageFrame = 60;

	// �v���C���[�̏����ʒu
	constexpr float kPosX = 500;
	constexpr float kPosY = 500;

	// �v���C���[�̍ő�HP
	constexpr float kMaxHp = 1;
	// �ő�e�G�l���M�[
	constexpr float kMaxShot = 28;
	// �c�@
	constexpr int kLife = 2;

	// �A�C�e���̉񕜗�
	constexpr float kSmallRecovery = 2;		// ���A�C�e��
	constexpr float kGreatRecovery = 10;	// ��A�C�e��
}


Player::Player(SceneMain* pMain, Bg* pBg) :
	m_pMain(pMain),
	m_pBg(pBg),
	m_pos(kPosX, kPosY),
	m_colRect(),
	m_handle(-1),
	m_isRight(true),
	m_isGround(false),
	m_velocity(0),
	m_jumpFrame(0),
	m_hp(kMaxHp),
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

/*����������*/
void Player::Init()
{
	// ���݈ʒu
	m_pos.x = kPosX;
	m_pos.y = kPosY;
	// ����
	m_isRight = true;
	// �W�����v�t���O
	m_isGround = false;
	// HP
	m_hp = kMaxHp;
	// �c�@��
	m_life = kLife;
	// �_���[�W�̃t���[����
	m_damageFrame = 0;
}

/*�v���C���[�̍X�V*/
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
	if (Pad::IsTrigger(PAD_INPUT_10) && m_isGround)
	{
		m_isGround = false;
		m_velocity = kVelocity;
	}

	/*�W�����v��*/
	if (!m_isGround)
	{
		m_jumpFrame++;	// �W�����v�t���[���̍X�V

		// �{�^���𗣂����u�ԂɃW�����v����
		if (Pad::IsRelease(PAD_INPUT_10))
		{
			// �W�����v�̍��������߂�
			float jumpHeight;

			if (m_jumpFrame < 10) // ����������10�t���[���ȉ�
			{
				jumpHeight = 0.5f;
			}
			else if (m_jumpFrame < 30) // 30�t���[���ȉ�
			{
				jumpHeight = 0.8f;
			}
			else	// 30�t���[���ȏ�
			{
				jumpHeight = 1.0f;
			}

			m_velocity = kVelocity * jumpHeight;
		}

		m_velocity += kGravity; // �����x�ɏd�͂𑫂�
		m_pos.y += m_velocity;	// ���݈ʒu�̍X�V
	}

	// �v���C���[�̌��ݒn(�������W)�̃}�b�v�`�b�v�ԍ����擾����
	// �v���C���[�̌��ݒn / �}�b�v�`�b�v�̃T�C�Y
	int mapChipNo = m_pBg->GetChipData(m_pos.x / kMapWidth, (m_pos.y + kPlayerHeight) / kMapHeight);

	switch (mapChipNo)
	{
	case 0:		// �v���C���[�̌��ݒn��n�ʂ���ɂ���
		m_isGround = true;
		break;
	case 30:
		m_isGround = false;
		break;
	default:
		m_isGround = false;
		break;
	}

	/*�n�ʂɒ��n������W�����v���I������*/
	if (m_isGround)
	{
		m_jumpFrame = 0;	// �W�����v�t���[����������
		m_velocity = 0;		// �����x��������
	}

	/*�V�����ɏo�����ʓ��ɖ߂�*/
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
	}

	/*�v���C���[�����ɗ��������ꍇ*/
	if ((m_pos.y - kPlayerHeight) > Game::kScreenHeight)
	{
		// �c�@��1���炷
		m_life--;
		if (m_life >= 0)
		{
			// �c�@��0�ȏゾ������v���C���[�������ʒu�ɖ߂�
			m_pos.x = kPosX;
			m_pos.y = kPosY;
		}
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
	m_colRect.SetLT(m_pos.x, m_pos.y, kPlayerWidth, kPlayerHeight); // �����蔻��̍X�V
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


/*�v���C���[�̃_���[�W���o*/
void Player::OnDamage()
{
	// �_���[�W���o���͖��G��ԂɂȂ�
	if (m_damageFrame > 0) return;

	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;

	// HP�����炷
	m_hp--;

	if (m_hp <= 0)
	{
		m_life--;		// �c�@��1���炷
		m_hp = kMaxHp;	// HP�S��
	}
}

void Player::HpSmallRecovery()
{
	m_hp += kSmallRecovery;	// HP����
	if (m_hp > kMaxHp) // �ő�HP�𒴂����ꍇ
	{
		m_hp = kMaxHp;
	}
}

void Player::HpGreatRecovery()
{
	m_hp += kGreatRecovery;	// HP���
	if (m_hp > kMaxHp) // �ő�HP�𒴂����ꍇ
	{
		m_hp = kMaxHp;
	}
}

void Player::HpFullRecovery()
{
	m_hp += kMaxHp; // HP�S��
	if (m_hp > kMaxHp) // �ő�HP�𒴂����ꍇ
	{
		m_hp = kMaxHp;
	}
}

void Player::ShotSmallRecovery()
{
	m_metalEnergy += kSmallRecovery; // �e�G�l���M�[����
	if (m_metalEnergy > kMaxShot) // �ő�G�l���M�[�𒴂����ꍇ
	{
		m_hp = m_metalEnergy;
	}
}

void Player::ShotGreatRecovery()
{
	m_metalEnergy += kGreatRecovery; // �e�G�l���M�[���
	if (m_metalEnergy > kMaxShot) // �ő�G�l���M�[�𒴂����ꍇ
	{
		m_hp = m_metalEnergy;
	}
}

void Player::LifeRecovery()
{
	m_life += 1;	// �c�@��1���₷
	if (m_life > 99)
	{
		m_life = 99;
	}
}
