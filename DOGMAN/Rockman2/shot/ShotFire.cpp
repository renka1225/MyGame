#include "ShotFire.h"
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
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
	// �摜�̊g�嗦
	constexpr float kSmallScale = 0.5f;
	constexpr float kMiddleScale = 0.8f;
	constexpr float kBigScale = 1.2f;
}

ShotFire::ShotFire()
{
	// �摜�ǂݍ���
	m_fire1Handle = LoadGraph("data/image/Shot/shotFire.png");
	m_fire2Handle = LoadGraph("data/image/Shot/shotFire2.png");
	m_fire3Handle = LoadGraph("data/image/Shot/shotFire3.png");
}

ShotFire::~ShotFire()
{
	DeleteGraph(m_fire1Handle);
	DeleteGraph(m_fire2Handle);
	DeleteGraph(m_fire3Handle);
}

void ShotFire::Init()
{
}

void ShotFire::Update()
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
	if (m_pos.x < m_pPlayer->GetPos().x - Game::kScreenWidth * 0.5f) isOut = true; // ��ʍ��[
	if (m_pos.x > m_pPlayer->GetPos().x + Game::kScreenWidth * 0.5f) isOut = true; // ��ʉE�[

	// �`�F�b�N���̍��W����ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// �����ɗ����Ƃ������Ƃ͉�ʊO�ɂ���
	m_isExist = false;
}

void ShotFire::Draw()
{
	if (!m_isExist) return;

	// �������W��������W�ɕϊ�
	int x = static_cast<int>(m_pos.x - kWidth * 0.5);
	int y = static_cast<int>(m_pos.y - kHeight * 0.5);

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// �e�̕\��
	if (m_pPlayer->IsSmallFire()) // ���������Ԃ�2�b�ȉ�
	{
		DrawRectRotaGraph(x, y, 0, 0, kWidth, kHeight, kSmallScale, 0.0f, m_fire1Handle, true);
	}
	else if (m_pPlayer->IsMiddleFire()) // ���������Ԃ�5�b�ȉ�
	{
		
		DrawRectRotaGraph(x, y, 0, 0, kWidth, kHeight, kMiddleScale, 0.0f, m_fire2Handle, true);
		
	}
	else // ���������Ԃ�5�b�ȏ�
	{
		DrawRectRotaGraph(x, y, 0, 0, kWidth, kHeight, kBigScale, 0.0f, m_fire3Handle, true);
	}

#ifdef _DEBUG
	// MEMO:�X�N���[�������f����Ȃ����߃R�����g�A�E�g
	// �e�̓����蔻��f�o�b�O�\��
	//m_colRect.Draw(0xff0000, false);
#endif
}

void ShotFire::Start(Vec2 pos)
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
