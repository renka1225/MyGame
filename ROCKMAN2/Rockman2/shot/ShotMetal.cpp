#include "ShotMetal.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include "Bg.h"
#include "Game.h"
#include "Pad.h"
#include <cassert>

// �萔�̒�`
namespace
{
	// �e�̈ړ����x
	constexpr float kSpeed = 15.0f;
	// �V���b�g�̑傫��
	constexpr int kWidth = 32.0f;
	constexpr int kHeight = 32.0f;
	// �摜�̊g�嗦
	constexpr float kScale = 1.0f;
}

ShotMetal::ShotMetal() :
	m_energy(0)
{
	// �e�̃O���t�B�b�N���[�h
	m_handle = LoadGraph("data/image/Shot/shotMetal.png");
}

ShotMetal::~ShotMetal()
{
	DeleteGraph(m_handle);
}

void ShotMetal::Init()
{
}

void ShotMetal::Update()
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
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);

	// ��ʊO�ɏo������
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ���		true:��ʊO�Afalse:��ʓ�
	if (m_pos.x < m_pPlayer->GetPos().x - Game::kScreenWidth * 0.5f) isOut = true; // ��ʍ��[
	if (m_pos.x > m_pPlayer->GetPos().x + Game::kScreenWidth * 0.5f) isOut = true; // ��ʉE�[
	if (m_pos.y < 0.0f - kWidth) isOut = true;			// ��ʏ�
	if (m_pos.y > Stage1::kMapHeight) isOut = true;		// ��ʉ�

	// �`�F�b�N���̍��W����ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// �����ɗ����Ƃ������Ƃ͉�ʊO�ɂ���
	m_isExist = false;
}

void ShotMetal::Draw()
{
	if (!m_isExist) return;

	// �������W��������W�ɕϊ�
	int x = static_cast<int>(m_pos.x - kWidth * 0.5f);
	int y = static_cast<int>(m_pos.y - kHeight * 0.5f);

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	DrawRectRotaGraph(x, y, 0, 0, kWidth, kHeight, kScale, 0.0f, m_handle, true);

#ifdef _DEBUG
	// MEMO:�X�N���[�������f����Ȃ����߃R�����g�A�E�g
	// �e�̓����蔻��f�o�b�O�\��
	//m_colRect.Draw(0xff0000, false);
#endif
}

void ShotMetal::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	m_pos = pos;

	// 1�t���[��������̈ړ��x�N�g�������肷��
	if (Pad::IsPress(PAD_INPUT_RIGHT)) // ��������
	{
		m_vec.x = kSpeed;
		m_vec.y = 0.0f;
	}
	if (Pad::IsPress(PAD_INPUT_LEFT)) // ��������
	{
		m_vec.x = -kSpeed;
		m_vec.y = 0.0f;
	}
	if (Pad::IsPress(PAD_INPUT_UP))	// ��������
	{
		m_vec.x = 0.0f;
		m_vec.y = -kSpeed;
	}
	if (Pad::IsPress(PAD_INPUT_DOWN)) // ��������
	{
		m_vec.x = 0.0f;
		m_vec.y = kSpeed;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT) && Pad::IsPress(PAD_INPUT_UP)) // ��+������������
	{
		m_vec.x = kSpeed;
		m_vec.y = -kSpeed;
		m_vec.normalize();
		m_vec *= kSpeed;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT) && Pad::IsPress(PAD_INPUT_DOWN)) // ��+������������
	{
		m_vec.x = kSpeed;
		m_vec.y = kSpeed;
		m_vec.normalize();
		m_vec *= kSpeed;
	}
	if (Pad::IsPress(PAD_INPUT_LEFT) && Pad::IsPress(PAD_INPUT_UP)) // ��+������������
	{
		m_vec.x = -kSpeed;
		m_vec.y = -kSpeed;
		m_vec.normalize();
		m_vec *= kSpeed;
	}
	if (Pad::IsPress(PAD_INPUT_LEFT) && Pad::IsPress(PAD_INPUT_DOWN)) // ��+������������
	{
		m_vec.x = -kSpeed;
		m_vec.y = kSpeed;
		m_vec.normalize();
		m_vec *= kSpeed;
	}
	if (!Pad::IsPress(PAD_INPUT_RIGHT) && !Pad::IsPress(PAD_INPUT_LEFT) &&
		!Pad::IsPress(PAD_INPUT_UP) && !Pad::IsPress(PAD_INPUT_DOWN)) // ���L�[��������Ă��Ȃ�
	{
		if(m_pPlayer->GetDir()) // �v���C���[���E�������Ă���ꍇ
		{
			m_vec.x = kSpeed;
		}
		if (!m_pPlayer->GetDir()) // �v���C���[�����������Ă���ꍇ
		{
			m_vec.x = -kSpeed;
		}
	}
}
