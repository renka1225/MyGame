#include "ShotLineMove.h"
#include "Player.h"
#include "Bg.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>


// �萔�̒�`
namespace
{
	// �e�̈ړ����x
	constexpr float kSpeed = 12.0f;
	// �V���b�g�̑傫��
	constexpr float kWidth = 32.0f;
	constexpr float kHeight = 32.0f;
}

ShotLineMove::ShotLineMove():
	m_stopFrame(0),
	m_energy(28)
{
	m_handle = LoadGraph("data/image/Shot/shotLineMove.png");
}

ShotLineMove::~ShotLineMove()
{
}

void ShotLineMove::Init()
{
	m_stopFrame = 60;
}

void ShotLineMove::Update()
{
	// �e�����݂��Ȃ���ΏI������
	if (!m_isExist) return;

	// �v���C���[�̃|�C���^���ݒ肳��Ă��Ȃ��Ƃ��~�܂�
	assert(m_pPlayer);

	// �Î~���Ԃ����炷
	m_stopFrame--;

	// �Î~���Ԃ�0�ɂȂ����瓮����
	if (m_stopFrame < 0)
	{
		m_pos += m_vec;		// ���݈ʒu���X�V
	}

	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x , m_pos.y, kWidth, kHeight);

	// TODO:��Q���ɓ��������������
	//if ()
	//{
	//	m_isExist = false;
	//	return;	// �I�����m�肵����ȍ~�̏����͍s��Ȃ�
	//}

	// ��ʊO�ɏo������
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ���		true:��ʊO�Afalse:��ʓ�
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true;					// ��ʍ��[
	if (m_pos.x > Stage::kMapWidth) isOut = true;	// ��ʉE�[

	// �`�F�b�N���̍��W����ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// �����ɗ����Ƃ������Ƃ͉�ʊO�ɂ���
	m_isExist = false;
}

void ShotLineMove::Draw()
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

void ShotLineMove::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	if (m_pPlayer->GetDir()) // �v���C���[���E�������Ă���ꍇ
	{
		m_pos.x = pos.x + 40;
		// 1�t���[��������̈ړ��x�N�g�������肷��
		m_vec.x = kSpeed;
	}
	else // �v���C���[�����������Ă���ꍇ
	{
		m_pos.x = pos.x - 40;
		// 1�t���[��������̈ړ��x�N�g�������肷��
		m_vec.x = -kSpeed;
	}
	m_pos.y = (pos.y + kHeight / 2);

	// �A�C�e��2����Î~���鎞��
	m_stopFrame = 60;
}
