#include "SceneClear.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// �����\���ʒu
	constexpr int kCharPosX = Game::kScreenWidth / 2 - 20;
	constexpr int kCharPosY = Game::kScreenHeight / 2 + 70;
	// �����Ԋu
	constexpr int kCharInterval = 50;

	// �I�𒆎l�p�̏����ʒu
	constexpr int kInitSelectPosX = kCharPosX - 15;
	constexpr int kInitSelectPosY = kCharPosY - 10;
	// �I�𒆎l�p�̈ړ���
	constexpr int kSelectmoveY = 50;
	// �l�p�̑傫��
	constexpr int kSelectSizeX = 80;
	constexpr int kSelectSizeY = 30;
}


SceneClear::SceneClear():
	m_select(kSelectStage),
	m_isSceneEnd(false)
{
}

SceneClear::~SceneClear()
{
}

void SceneClear::Init()
{
	m_isSceneEnd = false;
	m_select = kSelectStage;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
}

void SceneClear::End()
{
}

void SceneClear::Update()
{
}

void SceneClear::Draw()
{
	DrawString(8, 16, "�N���A���", 0xffffff, false);
}
