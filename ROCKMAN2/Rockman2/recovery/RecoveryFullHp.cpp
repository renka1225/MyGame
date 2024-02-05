#include "RecoveryFullHp.h"
#include "EnemyBase.h"
#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �A�C�e���̃T�C�Y
	constexpr int kWidth = 26;
	constexpr int kHeight = 30;
	// �g�嗦
	constexpr float kScale = 1.2f;
}

RecoveryFullHp::RecoveryFullHp()
{
	m_handle = LoadGraph("data/image/Recovery/fullHp.png");
}

RecoveryFullHp::~RecoveryFullHp()
{
	DeleteGraph(m_handle);
}

void RecoveryFullHp::Init(Bg* pBg)
{
	m_pBg = pBg;
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

	DrawRotaGraph(x, y, kScale, 0.0, m_handle, true, false);
}

void RecoveryFullHp::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	m_pos = pos;
}
