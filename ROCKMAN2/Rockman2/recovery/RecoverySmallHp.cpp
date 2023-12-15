#include "RecoverySmallHp.h"
#include "Player.h"
#include "EnemyBase.h"
#include "Game.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	// �A�C�e���̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// �����ʒu
	constexpr float kPosX = 500;
	constexpr float kPosY = 500;
}

RecoverySmallHp::RecoverySmallHp():
	m_pPlayer(nullptr),
	m_pEnemy(nullptr),
	m_isExist(false)
{
	m_hpSmallRecHandle = LoadGraph("data/image/Recovery/smallHp.png");
}

RecoverySmallHp::~RecoverySmallHp()
{
}

void RecoverySmallHp::Init()
{
	m_isExist = false;
}

void RecoverySmallHp::Update()
{
	// ���݂��Ȃ��A�C�e���̏����͂��Ȃ�
	if (!m_isExist) return;

	// �����蔻��̍X�V
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight);

	//Rect playerRect = m_pPlayer->GetColRect();	// �v���C���[�̓����蔻��

	//// �v���C���[�Ɖ񕜃A�C�e���̓����蔻��
	//if (playerRect.IsCollision(m_colRect))
	//{
	//	m_pPlayer->HpSmallRecovery();

	//	// �擾������A�C�e��������
	//	m_isExist = false;
	//}

	// ��ʊO�ɏo������
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ����t���O
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // ��ʍ��[
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // ��ʉE�[

	// ��ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// ��ʊO�ɏo����I������
	m_isExist = false;
}

void RecoverySmallHp::Draw()
{
	DrawGraph(m_pos.x, m_pos.y, m_hpSmallRecHandle, true);

#ifdef _DEBUG
	// �A�C�e���̓����蔻��f�o�b�O�\��
	m_colRect.Draw(0xff0000, false);
#endif
}

void RecoverySmallHp::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	// �|�����G�̌��ݒn���擾����
	m_pos = pos;
}
