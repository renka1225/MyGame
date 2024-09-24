#include "RecoveryGreatShot.h"
#include "EnemyBase.h"
#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �A�C�e���̃T�C�Y
	constexpr int kWidth = 70;
	constexpr int kHeight = 64;
	constexpr float kScale = 1.5f;

	// �������x
	constexpr int kSpeed = 5;
}

RecoveryGreatShot::RecoveryGreatShot()
{
	m_handle = LoadGraph("data/image/Recovery/shot.png");
}

RecoveryGreatShot::~RecoveryGreatShot()
{
	DeleteGraph(m_handle);
}

void RecoveryGreatShot::Init(Bg* pBg)
{
	m_pBg = pBg;
	m_frame = 0;
	m_isExist = false;
}

void RecoveryGreatShot::Update()
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
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ����t���O
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // ��ʍ��[
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // ��ʉE�[

	// ��ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// ��ʊO�ɏo����A�C�e��������
	m_isExist = false;
}

void RecoveryGreatShot::Draw()
{
	// 7�b��������10�t���[���Ԋu�ŕ\����\����؂�ւ���
	if (m_frame > 420)
	{
		if (m_frame % 10 >= 7) return;
	}

	// �������W��������W�ɕϊ�
	int x = static_cast<int>(m_pos.x - kWidth * 0.5);
	int y = static_cast<int>(m_pos.y - kHeight * 0.5);

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	DrawRotaGraph(x, y, kScale, 0.0f, m_handle, true);
}

void RecoveryGreatShot::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	// �|�����G�̌��ݒn���擾����
	m_pos = pos;

	// �A�C�e�������ɗ��Ƃ�
	m_vec.y = kSpeed;
}