#include "RecoverySmallShot.h"
#include "EnemyBase.h"
#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �A�C�e���̃T�C�Y
	constexpr int kWidth = 35;
	constexpr int kHeight = 32;

	// �������x
	constexpr int kSpeed = 5;
}

RecoverySmallShot::RecoverySmallShot()
{
	m_handle = LoadGraph("data/image/Recovery/shot.png");
}

RecoverySmallShot::~RecoverySmallShot()
{
	DeleteGraph(m_handle);
}

void RecoverySmallShot::Init(Bg* pBg)
{
	m_pBg = pBg;
	m_frame = 0;
	m_isExist = false;
}

void RecoverySmallShot::Update()
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

	// 10�b�ȏソ������A�C�e��������
	m_frame++;
	if (m_frame > 600)
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

void RecoverySmallShot::Draw()
{
	// 6�b��������10�t���[���Ԋu�ŕ\����\����؂�ւ���
	if (m_frame > 420)
	{
		if (m_frame % 10 >= 7) return;
	}

	// �������W��������W�ɕϊ�
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	DrawRotaGraph(x, y, 1.0f, 0.0f, m_handle, true);
}

void RecoverySmallShot::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	// �|�����G�̌��ݒn���擾����
	m_pos = pos;

	// �A�C�e�������ɗ��Ƃ�
	m_vec.y = kSpeed;
}

