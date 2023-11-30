#include "ShotLineMove.h"
#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>


// �萔�̒�`
namespace
{
	// �e�̈ړ����x
	constexpr float kSpeed = 10.0f;
	// �V���b�g�̑傫��
	constexpr float kWidth = 32.0f;
	constexpr float kHeight = 32.0f;
}

ShotLineMove::ShotLineMove():
m_energy(28)
{
	m_handle = LoadGraph("data/image/shotLineMove.png");
}

ShotLineMove::~ShotLineMove()
{
}

void ShotLineMove::Init()
{
}

void ShotLineMove::Update()
{
	// �e�����݂��Ȃ���ΏI������
	if (!m_isExist) return;

	// �v���C���[�̃|�C���^���ݒ肳��Ă��Ȃ��Ƃ��~�܂�
	assert(m_pPlayer);

	// �e�G�l���M�[����1���炷
	m_energy--;

	// ���݈ʒu�̍X�V
	m_pos += m_vec;

	// �����蔻��̍X�V
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight);

	// ��Q���ɓ��������������
	//if ()
	//{
	//	m_isExist = false;
	//	return;	// �I�����m�肵����ȍ~�̏����͍s��Ȃ�
	//}

	// ��ʊO�ɏo������
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ���		true:��ʊO�Afalse:��ʓ�
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true;					// ��ʍ��[
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true;	// ��ʉE�[

	// �`�F�b�N���̍��W����ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// �����ɗ����Ƃ������Ƃ͉�ʊO�ɂ���
	m_isExist = false;
}

void ShotLineMove::Draw()
{
	if (!m_isExist) return;

	DrawGraph(m_pos.x, m_pos.y, m_handle, true);

#ifdef _DEBUG
	// �e�̓����蔻��f�o�b�O�\��
	m_colRect.Draw(0xff0000, false);
#endif
}

void ShotLineMove::Start(Vec2 pos)
{
	m_isExist = true;

	if (m_pPlayer->GetDir()) // �v���C���[���E�������Ă���ꍇ
	{
		// �����ʒu�̐ݒ�
		m_pos.x = pos.x + 20;
		// 1�t���[��������̈ړ��x�N�g�������肷��
		m_vec.x = kSpeed;
	}
	else // �v���C���[�����������Ă���ꍇ
	{
		// �����ʒu�̐ݒ�
		m_pos.x = pos.x - 20;
		// 1�t���[��������̈ړ��x�N�g�������肷��
		m_vec.x = -kSpeed;
	}
	m_pos.y = (pos.y + kHeight / 2);
}
