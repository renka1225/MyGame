#include "Bg.h"
#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

namespace
{
	// �}�b�v�`�b�v1�̃T�C�Y
	constexpr int kChipWidth = 18;
	constexpr int kChipHeight = 18;

	// �`�b�v��u����
	constexpr int kChipNumX = 120;
	constexpr int kChipNumY = 60;
	// �}�b�v�`�b�v�g�嗦
	constexpr float kChipScale = 3.0f;

	// �}�b�v�̍L��
	constexpr int kMapWidth = kChipWidth * kChipScale * kChipNumX;
	constexpr int kMapHeight = kChipHeight * kChipScale * kChipNumY;

	// �}�b�v�`�b�v�̔z����
	constexpr int kChipData[kChipNumY][kChipNumX] = { 0, 0 };
}

Bg::Bg() :
	m_pPlayer(nullptr),
	m_bgPos(0.0f, 0.0f),
	m_bgMove(0.0f),
	m_graphChipNumX(0),
	m_graphChipNumY(0),
	m_bgHandle(-1),
	m_bg2Handle(-1),
	m_bg3Handle(-1),
	m_bg4Handle(-1),
	m_mapHandle(-1)
{
}

Bg::~Bg()
{
}

void Bg::Init()
{
}

void Bg::Update()
{
}

void Bg::Draw()
{
}