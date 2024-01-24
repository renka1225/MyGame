#include "RecoveryGreatHp.h"
#include "EnemyBase.h"
#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �A�C�e���̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// �������x
	constexpr int kSpeed = 5;
}


RecoveryGreatHp::RecoveryGreatHp()
{
	m_handle = LoadGraph("data/image/Recovery/GreatHp.png");
}

RecoveryGreatHp::~RecoveryGreatHp()
{
}

void RecoveryGreatHp::Init()
{
	m_frame = 0;
}

void RecoveryGreatHp::Update()
{
	// ���݂��Ȃ��A�C�e���̏����͂��Ȃ�
	if (!m_isExist) return;

	// ���݈ʒu�̍X�V
	m_pos += m_vec;

	// TODO:�n�ʂ̏�ɒ��n����悤�ɂ���
	if (m_pos.y > 550)
	{
		m_vec.y = 0;
	}

	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);

	// 5�b�ȏソ������A�C�e��������
	m_frame++;
	if (m_frame > 300)
	{
		m_isExist = false;
		m_frame = 0;
	}

	// ��ʊO�ɏo������
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ����t���O
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // ��ʍ��[
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // ��ʉE�[

	// ��ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// ��ʊO�ɏo����A�C�e��������
	m_isExist = false;
}

void RecoveryGreatHp::Draw()
{
	// �������W��������W�ɕϊ�
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	DrawRotaGraph(x, y, 1.0, 0.0, m_handle, true, false);
}

void RecoveryGreatHp::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	// �|�����G�̌��ݒn���擾����
	m_pos = pos;

	// �A�C�e�������ɗ��Ƃ�
	m_vec.y += kSpeed;
}
