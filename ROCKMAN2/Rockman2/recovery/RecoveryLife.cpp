#include "RecoveryLife.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �A�C�e���̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
}

RecoveryLife::RecoveryLife():
	m_lifeRecovery(1)
{
	m_lifeRecHandle = LoadGraph("data/image/Recovery/life");
}

RecoveryLife::~RecoveryLife()
{
}

void RecoveryLife::Init()
{
}

void RecoveryLife::Update()
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

	DrawGraph(m_pos.x, m_pos.y, m_lifeRecHandle, true);
}

void RecoveryLife::Draw()
{
#ifdef _DEBUG
	// �e�̓����蔻��f�o�b�O�\��
	m_colRect.Draw(0xff0000, false);
#endif
}
