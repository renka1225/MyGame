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
	m_isSceneStageSelect(false)
{
}

SceneClear::~SceneClear()
{
}

void SceneClear::Init()
{
	m_isSceneStageSelect = false;
	m_select = kSelectStage;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
}

void SceneClear::End()
{
}

void SceneClear::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Pad::IsTrigger(pad & PAD_INPUT_3))
	{
		m_isSceneStageSelect = true; // �X�e�[�W�I���Ɉړ�
	}
}

void SceneClear::Draw()
{
	DrawString(8, 16, "�N���A���", 0xffffff, false);
	DrawString(Game::kScreenWidth * 0.5f, Game::kScreenHeight * 0.5f, "C�L�[�ŃX�e�[�W�I��", 0xffffff, false);
}
