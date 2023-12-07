#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

SceneTitle::SceneTitle():
	m_isSceneEnd(false)
{
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
	if (Pad::IsTrigger(PAD_INPUT_1)) // Zキーを押したとき
	{
		// ゲーム画面に移動する
		m_isSceneEnd = true;
	}
}

void SceneTitle::Draw()
{
	DrawString(Game::kScreenWidth / 2 - 30, Game::kScreenHeight / 2 - 30, "タイトル画面", 0xffffff);
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight / 2, "Press Z", 0xffffff);
}

void SceneTitle::End()
{
}
