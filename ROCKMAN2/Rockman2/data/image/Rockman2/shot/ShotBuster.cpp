#include "ShotBuster.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include "Bg.h"
#include "Game.h"
#include <cassert>

// �萔�̒�`
namespace
{
	// �e�̈ړ����x
	constexpr float kSpeed = 15.0f;
	// �V���b�g�̑傫��
	constexpr float kWidth = 32.0f;
	constexpr float kHeight = 32.0f;
}

ShotBuster::ShotBuster()
{
	// �e�̃O���t�B�b�N���[�h
	m_handle = LoadGraph("data/image/Shot/shotBuster.png");
}

ShotBuster::~ShotBuster()
{
	DeleteGraph(m_handle);
}

void ShotBuster::Init()
{
}

void ShotBuster::Update()
{
	// �e�����݂��Ȃ���ΏI������
	if (!m_isExist) return;

	// �v���C���[�̃|�C���^���ݒ肳��Ă��Ȃ��Ƃ��~�܂�
	assert(m_pPlayer);

	// ���݈ʒu�̍X�V
	m_pos += m_vec;

	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);

	// ��ʊO�ɏo������
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ����t���O
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // ��ʍ��[
	if (m_pos.x > Stage::kMapWidth) isOut = true; // ��ʉE�[

	// ��ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// ��ʊO�ɏo��
	m_isExist = false;

}

void ShotBuster::Draw()
{
	if (!m_isExist) return;

	// �������W��������W�ɕϊ�
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	DrawGraph(x, y, m_handle, true);

#ifdef _DEBUG
	// MEMO:�X�N���[�������f����Ȃ����߃R�����g�A�E�g
	// �e�̓����蔻��f�o�b�O�\��
	//m_colRect.Draw(0xff0000, false);
#endif
}

void ShotBuster::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	m_pos = pos;

	// 1�t���[��������̈ړ��x�N�g�������肷��
	if (m_pPlayer->GetDir()) // �v���C���[���E�������Ă���ꍇ
	{
		m_vec.x = kSpeed;
	}
	else // �v���C���[�����������Ă���ꍇ
	{
		m_vec.x = -kSpeed;
	}
}
