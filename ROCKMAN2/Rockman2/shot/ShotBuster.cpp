#include "ShotBuster.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include <cassert>

// �萔�̒�`
namespace
{
	// �e�̈ړ����x
	constexpr float kSpeed = 8.0f;
	// �V���b�g�̑傫��
	constexpr float kWidth = 16.0f;
	constexpr float kHeight = 16.0f;
}

ShotBuster::ShotBuster()
{
}

ShotBuster::~ShotBuster()
{
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



	// ��Q���ɓ��������������
	//if ()
	//{
	//	m_isExist = false;
	//	return;	// �I�����m�肵����ȍ~�̏����͍s��Ȃ�
	//}

	// ��ʊO�ɏo���������
	m_isExist = false;
}

void ShotBuster::Draw()
{
	if (!m_isExist) return;
	DrawCircle(m_pos.x - kWidth / 2, m_pos.y - kHeight / 2, 0x00ff00, true);
}

void ShotBuster::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	m_pos = pos;
}
