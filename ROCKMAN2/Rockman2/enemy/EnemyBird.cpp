#include "EnemyBird.h"
#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �G�̃T�C�Y
	constexpr int kWidth = 16;
	constexpr int kHeight = 16;

	// �G�t�F�N�g�̃T�C�Y
	constexpr int kEffectWidth = 32;
	constexpr int kEffectHeight = 32;

	// �g�嗦
	constexpr float kEnlarge = 3.0f;
	constexpr float kEffectScale = 7.0f;

	// �ړ����x
	constexpr float kSpeed = 3.0f;
	// �ő�HP
	constexpr int kHp = 1;

	// �A�j���[�V����
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


EnemyBird::EnemyBird():
	m_flyAnimFrame(0)
{
	m_handle = LoadGraph("data/image/Enemy/bird.png");
}

EnemyBird::~EnemyBird()
{
	DeleteGraph(m_handle);
}

void EnemyBird::Init()
{
	m_hp = kHp;
	m_isDead = false;
}

void EnemyBird::Update()
{
	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	// �}�b�v�`�b�v�Ƃ̓����蔻��
	Rect chipRect; // ���������}�b�v�`�b�v�̋�`
	HitCollision(chipRect);

	// �ړ��A�j���[�V����
	m_flyAnimFrame++;
	if (m_flyAnimFrame >= kAnimFrameCycle)
	{
		m_flyAnimFrame = 0;
	}

	// �_���[�W�G�t�F�N�g
	m_damageFrame--;
	if (m_damageFrame < 0)
	{
		m_damageFrame = 0;
	}
}

void EnemyBird::Draw()
{
	// �������W��������W�ɕϊ�
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// ���\��
	// �摜�̐؂�o�����W
	int animFrame = m_flyAnimFrame / kAnimFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;

	DrawRectRotaGraph(x, y, srcX, srcY, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);

	// �_���[�W�G�t�F�N�g�\��
	// �摜�̐؂�o�����W
	int effectFrame = m_damageFrame / kEffectFrameNum;
	int effectSrcX = kUseFrame[animFrame] * kEffectWidth;
	int effectSrcY = kHeight;
	if (m_damageFrame > 0)
	{
		DrawRectRotaGraph(x, y, effectSrcX, effectSrcY, kEffectWidth, kEffectHeight, kEnlarge, 0.0f, m_damageEffect, true);
	}

	// ���Ŏ��_���[�W�G�t�F�N�g�\��
	if (m_isDead)
	{
		// �摜�̐؂�o�����W
		int effectFrame = m_damageFrame / kEffectFrameNum;
		int effectSrcX = kUseFrame[effectFrame] * kEffectWidth;
		int effectSrcY = 0;
		if (m_damageFrame > 0)
		{
			DrawRectRotaGraph(x , y, effectSrcX, effectSrcY, kEffectWidth, kEffectHeight, kEffectScale, 0.0f, m_damageEffect, true);
		}
	}

#ifdef _DEBUG
	// �X�N���[�������f����Ȃ����߃R�����g�A�E�g
	// �����蔻��̕\��
	//m_colRect.Draw(0x00ff00, false);
#endif
}

void EnemyBird::Start(float posX, float posY)
{
	// �G�L�����N�^�[��o�ꂳ����
	m_isExist = true;

	m_pos = { posX, posY };
	m_vec.x -= kSpeed;
}

void EnemyBird::HitCollision(Rect chipRect)
{
	// �����瓖���������`�F�b�N����
	m_pos.x += m_vec.x;	// ���݈ʒu�̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth), static_cast<float>(kHeight)); // �����蔻��𐶐�
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.x > 0.0f) // �E�Ɉړ���
		{
			m_pos.x = chipRect.GetLeft() - kWidth * 0.5f - 1;
			m_vec.x *= -1;
			m_dir = kDirLeft;

		}
		else if (m_vec.x < 0.0f) // ���Ɉړ���
		{
			m_pos.x = chipRect.GetRight() + kWidth * 0.5f + 1;
			m_vec.x *= -1;
			m_dir = kDirRight;
		}
	}

	// �c���瓖���������`�F�b�N����
	m_pos.y += m_vec.y; 	// ���݈ʒu�̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth), static_cast<float>(kHeight)); // �����蔻��𐶐�
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kHeight * 0.5f - 1;
		}
	}
}

void EnemyBird::OnDamage()
{
	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;

	// �e������������HP�����炷
	m_hp--;

	// HP��0�ȉ��ɂȂ����瑶�݂�����
	if (m_hp <= 0)
	{
		m_isExist = false;
		m_isDead = true;
	}
}
