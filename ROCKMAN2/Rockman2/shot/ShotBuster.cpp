#include "ShotBuster.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include <cassert>

// �萔�̒�`
namespace
{
	// �e�̈ړ����x
	constexpr float kSpeed = 8.0f;
	// �V���b�g�̑傫��
	constexpr float kWidth = 8.0f;
	constexpr float kHeight = 8.0f;
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
	if (!m_isExist) return;

	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
}

void ShotBuster::Draw()
{
}
