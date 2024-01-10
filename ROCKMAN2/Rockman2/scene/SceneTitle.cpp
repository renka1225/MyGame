#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

SceneTitle::SceneTitle():
	m_isSceneEnd(false),
	m_logoHandle(-1)
{
	m_logoHandle = LoadGraph("data/image/Logo/TitleLogo.png");
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_isSceneEnd = false;
}

void SceneTitle::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_1)) // Z�L�[���������Ƃ�
	{
		// �Q�[����ʂɈړ�����
		m_isSceneEnd = true;
	}
}

void SceneTitle::Draw()
{
	// ���S�\��
	DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 4, 0.8f, 0.0f, m_logoHandle, true);

	// ��قǍ폜
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight / 2 + 100, "Start", 0xffffff);
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight / 2 + 200, "Press Z", 0xffffff);
}

void SceneTitle::End()
{
}
