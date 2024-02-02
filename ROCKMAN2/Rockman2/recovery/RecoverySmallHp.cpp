#include "RecoverySmallHp.h"
#include "EnemyBase.h"
#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �A�C�e���̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 28;

	// �������x
	constexpr int kSpeed = 5;
}

RecoverySmallHp::RecoverySmallHp()
{
	m_handle = LoadGraph("data/image/Recovery/hp.png");
}

RecoverySmallHp::~RecoverySmallHp()
{
	DeleteGraph(m_handle);
}

void RecoverySmallHp::Init(Bg* pBg)
{
	m_pBg = pBg;
	m_frame = 0;
	m_isExist = false;
}

void RecoverySmallHp::Update()
{
	// ���݂��Ȃ��A�C�e���̏����͂��Ȃ�
	if (!m_isExist) return;

	// ���݈ʒu�̍X�V
	m_pos += m_vec;

	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
	Rect chipRect; // ���������}�b�v�`�b�v�̋�`
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.y > 0.0f)
		{
			// �n�ʂɗ�����悤�ɂ���
			m_pos.y = chipRect.GetTop() - kHeight * 0.5f - 1;
		}
	}

	// 5�b�ȏソ������A�C�e��������
	m_frame++;
	if (m_frame > 300)
	{
		m_isExist = false;
		m_frame = 0;
	}

	// ��ʊO�ɏo������
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ���
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // ��ʍ��[
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // ��ʉE�[

	// ��ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// ��ʊO�ɏo����A�C�e��������
	m_isExist = false;
}

void RecoverySmallHp::Draw()
{
	// �������W��������W�ɕϊ�
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	DrawRotaGraph(x, y, 0.5f, 0.0f, m_handle, true, false);
}

void RecoverySmallHp::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	// �|�����G�̌��ݒn���擾����
	m_pos = pos;

	// �A�C�e�������ɗ��Ƃ�
	m_vec.y = kSpeed;
}
