#include "SceneOption.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

SceneOption::SceneOption():
	m_isSceneTitle(false),
	m_fadeAlpha(255)
{
	m_exHandle = LoadGraph("data/image/ex.png");
}

SceneOption::~SceneOption()
{
	DeleteGraph(m_exHandle);
}

void SceneOption::Init()
{
	m_isSceneTitle = false;
}

void SceneOption::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// XキーorBボタンを押したらタイトル画面に戻る
	if (Pad::IsTrigger(PAD_INPUT_B))
	{
		m_isSceneTitle = true;
	}

	// フェードイン
	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}
}

void SceneOption::Draw()
{
	DrawGraph(0, 0, m_exHandle, true);
#ifdef _DEBUG
	DrawString(20, 20, "オプション画面", 0xffffff);
#endif
}