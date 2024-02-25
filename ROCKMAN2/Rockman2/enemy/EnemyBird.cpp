#include "EnemyBird.h"
#include "Bg.h"
#include "Player.h"
#include "Game.h"
#include "DxLib.h"
#include <cmath>

/// <summary>
/// �萔
/// </summary>
namespace
{
	/*���̏��*/
	// �ړ����x
	constexpr float kSpeedX = 1.0f;
	constexpr float kSpeedY = 10.0f;
	constexpr float kSinSpeed = 0.05f;
	constexpr float kAnimationSize = 3.0f;

	// �ő�HP
	constexpr float kHp = 1.0f;

	// �T�C�Y
	constexpr int kWidth = 16;
	constexpr int kHeight = 16;
	// �g�嗦
	constexpr float kEnlarge = 3.4f;

	// �ʒu����
	constexpr float kColSizeAdjustment = 0.5f;
	constexpr float kPosAdjustment = 1.0f;

	/*�A�j���[�V����*/
	constexpr int kUseFrame[] = { 0, 1, 2, 3 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 8;
	// �A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
	// �_���[�W
	constexpr int kdamageFrame[] = { 0, 1, 2, 3 };
	// �_���[�W���o�t���[����
	constexpr int kDamageFrame = 60;

	/*�G�t�F�N�g*/
	// �G�t�F�N�g�̃T�C�Y
	constexpr int kEffectWidth = 32;
	constexpr int kEffectHeight = 32;
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kEffectFrameNum = 40;
	//�g�嗦
	constexpr float kEffectScale = 5.0f;
}


EnemyBird::EnemyBird():
	m_flyAnimFrame(0),
	m_sinCount(0.0f)
{
	m_handle = LoadGraph("data/image/Enemy/bird.png");
}


EnemyBird::~EnemyBird()
{
	DeleteGraph(m_handle);
}


/// <summary>
/// ������
/// </summary>
/// <param name="pBg">�w�i�N���X�̃|�C���^</param>
/// <param name="pPlayer">�v���C���[�N���X�̃|�C���^</param>
void EnemyBird::Init(Bg* pBg, Player* pPlayer)
{
	m_pBg = pBg;
	m_pPlayer = pPlayer;
	m_hp = kHp;
	m_sinCount = 0;
	m_isDead = false;
}


/// <summary>
/// �X�V
/// </summary>
void EnemyBird::Update()
{
	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	// �}�b�v�`�b�v�Ƃ̓����蔻��
	Rect chipRect; // ���������}�b�v�`�b�v�̋�`
	HitCollision(chipRect);

	// �ړ�
	m_sinCount += kSinSpeed;
	m_vec.y = sinf(m_sinCount) * kAnimationSize;

	// ���E�ړ�����悤�ɂ���
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
	m_flyAnimFrame++;
	if (m_flyAnimFrame >= kAnimFrameCycle) m_flyAnimFrame = 0;

	// �_���[�W�G�t�F�N�g
	m_damageFrame--;
	if (m_damageFrame < 0) m_damageFrame = 0;
}


/// <summary>
/// �`��
/// </summary>
void EnemyBird::Draw()
{
	// �������W��������W�ɕϊ�
	int x = static_cast<int>(m_pos.x - kWidth * 0.5);
	int y = static_cast<int>(m_pos.y - kHeight * 0.5);

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// ���\��
	// �摜�̐؂�o�����W
	int animFrame = m_flyAnimFrame / kAnimFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;

	DrawRectRotaGraph(x, y,
		srcX, srcY,
		kWidth, kHeight, 
		kEnlarge, 0.0f,
		m_handle, true);

	// ���Ŏ��_���[�W�G�t�F�N�g�\��
	if (m_isDead)
	{
		// �摜�̐؂�o�����W
		int effectFrame = m_damageFrame / kEffectFrameNum;
		int effectSrcX = kUseFrame[effectFrame] * kEffectWidth;
		int effectSrcY = 0;
		if (m_damageFrame > 0)
		{
			DrawRectRotaGraph(x , y,
				effectSrcX, effectSrcY,
				kEffectWidth, kEffectHeight, 
				kEffectScale, 0.0f, 
				m_damageEffect, true);
		}
	}

#ifdef _DEBUG
	// �X�N���[�������f����Ȃ����߃R�����g�A�E�g
	// �����蔻��̕\��
	//m_colRect.Draw(0x00ff00, false);
#endif
}


/// <summary>
/// �������̏���
/// </summary>
/// <param name="posX">�����ʒu��X���W</param>
/// <param name="posY">�����ʒu��Y���W</param>
/// <param name="moveRangeX">�ړ���</param>
void EnemyBird::Start(float posX, float posY, float moveRangeX)
{
	m_isExist = true;

	m_pos = { posX, posY };
	m_startPos = { posX, posY };
	m_vec.x = -kSpeedX;
	m_vec.y = 0.0f;
	m_moveRangeX = moveRangeX;
}


/// <summary>
/// �}�b�v�`�b�v�Ƃ̓����蔻��
/// </summary>
/// <param name="chipRect">�}�b�v�`�b�v�̓����蔻��</param>
void EnemyBird::HitCollision(Rect chipRect)
{
	// �����瓖���������`�F�b�N����
	m_pos.x += m_vec.x;
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth), static_cast<float>(kHeight)); // �����蔻��𐶐�

	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.x > 0.0f) // �E�Ɉړ���
		{
			m_pos.x = chipRect.GetLeft() - kWidth * kEnlarge * kColSizeAdjustment - kPosAdjustment;
			m_vec.x *= -1;
			m_dir = kDirLeft;
		}
		else if (m_vec.x < 0.0f) // ���Ɉړ���
		{
			m_pos.x = chipRect.GetRight() + kWidth * kEnlarge * kColSizeAdjustment + kPosAdjustment;
			m_vec.x *= -1;
			m_dir = kDirRight;
		}
	}

	// �c���瓖���������`�F�b�N����
	m_pos.y += m_vec.y;
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth * kEnlarge), static_cast<float>(kHeight * kEnlarge)); // �����蔻��𐶐�

	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.y > 0.0f && m_vec.x == 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kHeight * kEnlarge * kColSizeAdjustment - kPosAdjustment;
			m_vec.y *= -1;
		}
		else if (m_vec.y < 0.0f && m_vec.x == 0.0f)
		{
			m_pos.y = chipRect.GetBottom() + kHeight * kEnlarge * kColSizeAdjustment + kPosAdjustment;
			m_vec.y *= -1;
		}
	}
}

/// <summary>
/// �_���[�W���̏���
/// </summary>
void EnemyBird::OnDamage()
{
	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;

	// �e������������HP�����炷
	m_hp--;

	// SE��炷
	PlaySoundMem(m_damageSE, DX_PLAYTYPE_BACK, true);

	// HP��0�ȉ��ɂȂ����瑶�݂�����
	if (m_hp <= 0)
	{
		m_isExist = false;
		m_isDead = true;
	}
}
