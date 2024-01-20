#include "RecoveryFullHp.h"
#include "EnemyBase.h"
#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �A�C�e���̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
}

RecoveryFullHp::RecoveryFullHp()
{
	m_handle = LoadGraph("data/image/Recovery/fullHp.png");
}

RecoveryFullHp::~RecoveryFullHp()
{
}

void RecoveryFullHp::Init()
{
}

void RecoveryFullHp::Update()
{
	// ���݂��Ȃ��A�C�e���̏����͂��Ȃ�
	if (!m_isExist) return;

	// �����蔻��
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
}

void RecoveryFullHp::Draw()
{
	// �������W��������W�ɕϊ�
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	DrawRotaGraph(x, y, 1.0, 0.0, m_handle, true, false);
}

void RecoveryFullHp::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	m_pos = pos;
}
