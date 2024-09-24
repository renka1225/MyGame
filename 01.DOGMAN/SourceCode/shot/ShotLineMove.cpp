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
	constexpr float kSpeed = 10.0f;
	// �V���b�g�̑傫��
	constexpr float kWidth = 52.0f;
	constexpr float kHeight = 16.0f;

	// �A�C�e��2���̓����蔻��̕�
	constexpr float kLineMoveWidth = 150.0f;
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
	m_isExist = false;
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
	m_lineMoveColRect.SetCenter(m_pos.x, m_pos.y, kLineMoveWidth, kHeight);

	// �}�b�v�`�b�v�ɓ������������
	Rect chipRect;	// �}�b�v�`�b�v�̓����蔻��
	if (m_pBg->IsCollision(m_lineMoveColRect, chipRect))
	{
		m_isExist = false;
	}

	// ����Ă���Œ��ɃG�l���M�[���Ȃ��Ȃ�����A�C�e��2��������
	if (m_pPlayer->GetLineEnergy() < 0)
	{
		m_isExist = false;
	}

	// ��ʊO�ɏo������
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ����t���O
	if (m_pos.x < m_pPlayer->GetPos().x - Game::kScreenWidth * 0.5f) isOut = true; // ��ʍ��[
	if (m_pos.x > m_pPlayer->GetPos().x + Game::kScreenWidth * 0.5f) isOut = true; // ��ʉE�[

	// �`�F�b�N���̍��W����ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// �����ɗ����Ƃ������Ƃ͉�ʊO�ɂ���
	m_isExist = false;
}

void ShotLineMove::Draw()
{
	if (!m_isExist) return;

	// �������W��������W�ɕϊ�
	int x = static_cast<int>(m_pos.x - kWidth * 0.5);
	int y = static_cast<int>(m_pos.y - kHeight * 0.5);

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	if (m_vec.x > 0)
	{
		DrawGraph(x, y, m_handle, true);
	}
	else
	{
		DrawTurnGraph(x, y, m_handle, true);
	}

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
		m_pos.x = pos.x + 20;
		// 1�t���[��������̈ړ��x�N�g�������肷��
		m_vec.x = kSpeed;
	}
	else // �v���C���[�����������Ă���ꍇ
	{
		m_pos.x = pos.x - 20;
		// 1�t���[��������̈ړ��x�N�g�������肷��
		m_vec.x = -kSpeed;
	}
	m_pos.y = (pos.y + kHeight / 2);

	// �A�C�e��2����Î~���鎞��
	m_stopFrame = 150;
}
