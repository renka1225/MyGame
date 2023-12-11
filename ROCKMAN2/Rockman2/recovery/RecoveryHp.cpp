#include "RecoveryHp.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �A�C�e���̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// �����ʒu
	constexpr float kPosX = 500;
	constexpr float kPosY = 500;
}

RecoveryHp::RecoveryHp()
{
	m_hpSmallRecHandle = LoadGraph("data/image/Recovery/hpSmall");
	m_hpGreatRecHandle = LoadGraph("data/image/Recovery/hpGreat");
	m_hpFullRecHandle = LoadGraph("data/image/Recovery/hpFull");
}

RecoveryHp::~RecoveryHp()
{
}

void RecoveryHp::Init()
{
}

void RecoveryHp::Update()
{
	// �����蔻��̍X�V
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight);

	// ��ʊO�ɏo������
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ����t���O
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // ��ʍ��[
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // ��ʉE�[

	// ��ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// ��ʊO�ɏo����I������
	m_isExist = false;

	if (!m_isExist) return;
}

void RecoveryHp::Draw()
{
	DrawGraph(m_pos.x, m_pos.y, m_hpSmallRecHandle, true);
	DrawGraph(m_pos.x, m_pos.y, m_hpGreatRecHandle, true);
	DrawGraph(m_pos.x, m_pos.y, m_hpFullRecHandle, true);

#ifdef _DEBUG
	// �e�̓����蔻��f�o�b�O�\��
	m_colRect.Draw(0xff0000, false);
#endif
}

// �񕜃A�C�e���̓o��
void RecoveryHp::Start()
{
	// �A�C�e����o�ꂳ����
	m_isExist = true;

	// �摜�T�C�Y
	int width = 0;
	int height = 0;
	GetGraphSize(m_hpSmallRecHandle, &width, &height);

	// ���݈ʒu
	m_pos.x = kPosX;
	m_pos.y = kPosY;
}
