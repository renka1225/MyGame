#include "EnemyCat.h"
#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �G�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 18;
	// �g�嗦
	constexpr float kEnlarge = 2.0f;

	// �ړ����x
	constexpr float kSpeed = 4.0f;
	// �ő�HP
	constexpr int kHp = 3;

	// �A�j���[�V����
	constexpr int kUseFrame[] = { 0, 1, 2, 3 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 8;
	// �A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}


EnemyCat::EnemyCat():
	m_walkAnimFrame(0)
{
	m_handle = LoadGraph("data/image/Enemy/cat.png");
}

EnemyCat::~EnemyCat()
{
	DeleteGraph(m_handle);
}

void EnemyCat::Init()
{
	m_hp = kHp;
	m_isDead = false;
}

void EnemyCat::Update()
{
	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	// TODO:�G�����E�Ɉړ�������
	if (m_pos.x < 300.0f)
	{
		m_vec.x *= -1; // �E�Ɉړ�
		m_dir = kDirRight;
	}
	else if (m_pos.x > 2000.0f)
	{
		m_vec.x *= -1; // ���Ɉړ�
		m_dir = kDirLeft;
	}

	// ���݈ʒu�̍X�V
	m_pos += m_vec;

	// �����蔻��𐶐�
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth * 3), static_cast<float>(kHeight));

	// �ړ��A�j���[�V����
	m_walkAnimFrame++;
	if (m_walkAnimFrame >= kAnimFrameCycle)
	{
		m_walkAnimFrame = 0;
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

	// �摜�̐؂�o�����W
	int animFrame = m_walkAnimFrame / kAnimFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;

	DrawRectRotaGraph(x, y, srcX, srcY, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);

#ifdef _DEBUG
	// �X�N���[�������f����Ȃ����߃R�����g�A�E�g
	// �����蔻��̕\��
	// m_colRect.Draw(0x00ff00, false);
#endif
}

void EnemyCat::Start(float posX, float posY)
{
	// �G�L�����N�^�[��o�ꂳ����
	m_isExist = true;

	m_pos = { posX, posY };
	m_vec.x -= kSpeed;
}

void EnemyCat::OnDamage()
{
	// �e������������HP�����炷
	m_hp--;

	// HP��0�ȉ��ɂȂ����瑶�݂�����
	if (m_hp <= 0)
	{
		m_isExist = false;
		m_isDead = true;
	}
}
