#include "EnemyCat.h"
#include "Bg.h"
#include "Player.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �G�̃T�C�Y
	constexpr int kWidth = 64;
	constexpr int kHeight = 38;

	// �G�t�F�N�g�̃T�C�Y
	constexpr int kEffectWidth = 32;
	constexpr int kEffectHeight = 32;

	// �g�嗦
	constexpr float kEnlarge = 1.3f;
	constexpr float kEffectScale = 7.0f;

	// �ړ����x
	constexpr float kSpeedX = 3.0f;
	constexpr float kSpeedY = 10.0f;
	// �ő�HP
	constexpr int kHp = 3;

	// �G�A�j���[�V����
	constexpr int kUseFrame[] = { 0, 1, 2, 3 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 8;
	// �A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	// �G�t�F�N�g
	constexpr int kdamageFrame[] = { 0, 1, 2, 3 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kEffectFrameNum = 8;
	// �_���[�W���o�t���[����
	constexpr int kDamageFrame = 60;
}


EnemyCat::EnemyCat() :
	m_walkAnimFrame(0)
{
	m_handle = LoadGraph("data/image/Enemy/cat.png");
}

EnemyCat::~EnemyCat()
{
	DeleteGraph(m_handle);
}

void EnemyCat::Init(Bg* pBg, Player* pPlayer)
{
	m_pBg = pBg;
	m_pPlayer = pPlayer;
	m_hp = kHp;
	m_isDead = false;
}

void EnemyCat::Update()
{
	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	// �}�b�v�`�b�v�Ƃ̓����蔻��
	Rect chipRect; // ���������}�b�v�`�b�v�̋�`
	HitCollision(chipRect);

	// �n�ʂ��痎���Ȃ��悤�ɂ���
	if (m_pos.x > m_startPos.x + m_moveRangeX)
	{
		m_vec.x *= -1;
		m_dir = kDirLeft;
	}
	else if (m_pos.x < m_startPos.x - m_moveRangeX)
	{
		m_vec.x *= -1;
		m_dir = kDirRight;
	}

	// �ړ��A�j���[�V����
	m_walkAnimFrame++;
	if (m_walkAnimFrame >= kAnimFrameCycle)
	{
		m_walkAnimFrame = 0;
	}

	// �_���[�W�G�t�F�N�g
	m_damageFrame--;
	if (m_damageFrame < 0)
	{
		m_damageFrame = 0;
	}
}

void EnemyCat::Draw()
{
	// �������W��������W�ɕϊ�
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// �_���[�W���o
	// 10�t���[���Ԋu�ŕ\����\����؂�ւ���
	if (m_damageFrame % 10 >= 7) return;

	// �L�\��
	// �摜�̐؂�o�����W
	int animFrame = m_walkAnimFrame / kAnimFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;
	DrawRectRotaGraph(x, y, srcX, srcY, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);

	// ���Ŏ��_���[�W�G�t�F�N�g�\��
	if (m_isDead)
	{
		// �摜�̐؂�o�����W
		int effectFrame = m_damageFrame / kEffectFrameNum;
		int effectSrcX = kUseFrame[effectFrame] * kEffectWidth;
		int effectSrcY = 0;
		if (m_damageFrame > 0)
		{
			DrawRectRotaGraph(x + 10, y, effectSrcX, effectSrcY, kEffectWidth, kEffectHeight, kEffectScale, 0.0f, m_damageEffect, true);
		}
	}

#ifdef _DEBUG
	// �X�N���[�������f����Ȃ����߃R�����g�A�E�g
	// �����蔻��̕\��
	// m_colRect.Draw(0x00ff00, false);
#endif
}

void EnemyCat::Start(float posX, float posY, float moveRangeX)
{
	// �G�L�����N�^�[��o�ꂳ����
	m_isExist = true;

	m_pos = { posX, posY };
	m_startPos = { posX, posY };
	m_vec.x = -kSpeedX;
	m_vec.y = kSpeedY;
	m_moveRangeX = moveRangeX;
}

void EnemyCat::HitCollision(Rect chipRect)
{
	// �����瓖���������`�F�b�N����
	m_pos.x += m_vec.x;	// ���݈ʒu�̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth * kEnlarge), static_cast<float>(kHeight * kEnlarge)); // �����蔻��𐶐�
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.x > 0.0f) // �E�Ɉړ���
		{
			m_pos.x = chipRect.GetLeft() - kWidth * kEnlarge * 0.5f - 1;
			m_vec.x *= -1;
			m_dir = kDirLeft;

		}
		else if (m_vec.x < 0.0f) // ���Ɉړ���
		{
			m_pos.x = chipRect.GetRight() + kWidth * kEnlarge * 0.5f + 1;
			m_vec.x *= -1;
			m_dir = kDirRight;
		}
	}

	// �c���瓖���������`�F�b�N����
	m_pos.y += m_vec.y; 	// ���݈ʒu�̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth * kEnlarge), static_cast<float>(kHeight * kEnlarge)); // �����蔻��𐶐�
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kHeight * kEnlarge * 0.5f - 1;
		}
	}
}

void EnemyCat::OnDamage()
{
	// �_���[�W���o���͍ēx�H���Ȃ�
	if (m_damageFrame > 0) return;
	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;

	// ���݂�HP�����炷
	if (m_pPlayer->IsMiddleFire())
	{
		m_hp -= 3;
	}
	else if (m_pPlayer->IsBigFire())
	{
		m_hp -= 5;
	}
	else
	{
		m_hp--;
	};

	// SE��炷
	PlaySoundMem(m_damageSE, DX_PLAYTYPE_BACK, true);

	// HP��0�ȉ��ɂȂ����瑶�݂�����
	if (m_hp <= 0)
	{
		m_isDead = true;
		m_isExist = false;
	}
}
