#include "SceneClear.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// 文字表示位置
	constexpr int kCharPosX = Game::kScreenWidth / 2 - 20;
	constexpr int kCharPosY = Game::kScreenHeight / 2 + 70;
	// 文字間隔
	constexpr int kCharInterval = 50;

	// 選択中四角の初期位置
	constexpr int kInitSelectPosX = kCharPosX - 15;
	constexpr int kInitSelectPosY = kCharPosY - 10;
	// 選択中四角の移動量
	constexpr int kSelectmoveY = 50;
	// 四角の大きさ
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
		m_isSceneStageSelect = true; // ステージ選択に移動
	}
}

void SceneClear::Draw()
{
	DrawString(8, 16, "クリア画面", 0xffffff, false);
	DrawString(Game::kScreenWidth * 0.5f, Game::kScreenHeight * 0.5f, "Cキーでステージ選択", 0xffffff, false);
}
