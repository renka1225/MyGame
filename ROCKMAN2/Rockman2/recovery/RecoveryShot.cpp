#include "RecoveryShot.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �A�C�e���̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
}

RecoveryShot::RecoveryShot():
	m_shotSmallRecovery(2),
	m_shotGreatRecovery(10)
{
	m_shotSmallRecHandle = LoadGraph("data/image/Recovery/shotSmall");
	m_shotGreatRecHandle = LoadGraph("data/image/Recovery/shotGreat");
}

RecoveryShot::~RecoveryShot()
{
}

void RecoveryShot::Init()
{
}

void RecoveryShot::Update()
{
	// ��ʓ��ɑ��݂��Ȃ���ΏI������
	if (!m_isExist) return;

	// �����蔻��̍X�V
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight);

	// ��ʊO�ɏo������
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ����t���O
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // ��ʍ��[
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // ��ʉE�[

	// ��ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// ��ʊO�ɏo��
	m_isExist = false;

	DrawGraph(m_pos.x, m_pos.y, m_shotSmallRecHandle, true);
	DrawGraph(m_pos.x, m_pos.y, m_shotGreatRecHandle, true);
}

void RecoveryShot::Draw()
{
#ifdef _DEBUG
	// �e�̓����蔻��f�o�b�O�\��
	m_colRect.Draw(0xff0000, false);
#endif
}
