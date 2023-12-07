#include "SceneGameOver.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

SceneGameOver::SceneGameOver():
	m_isSceneEnd(false)
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
	m_isSceneEnd = false;
}

void SceneGameOver::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_1)) // Zキーを押したとき
	{
		// タイトル画面に移動する
		m_isSceneEnd = true;
	}
}

void SceneGameOver::Draw()
{
	DrawString(Game::kScreenWidth / 2 - 30, Game::kScreenHeight / 2 - 30, "ゲームオーバー", 0xff0000);
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight / 2, "Press Z", 0xff0000);
}

void SceneGameOver::End()
{
}

