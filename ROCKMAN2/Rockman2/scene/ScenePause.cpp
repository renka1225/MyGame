#include "ScenePause.h"
#include "Player.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// ポーズ画面のサイズ
	constexpr int kWidth = 280;
	constexpr int kHeight = 480;

	// ポーズ画面の位置
	constexpr int kPosX = (Game::kScreenWidth - kWidth) / 2;
	constexpr int kPosY = Game::kScreenHeight / 6;
}

ScenePause::ScenePause():
	m_pPlayer(nullptr),
	m_isExist(false)
{
}

ScenePause::~ScenePause()
{
}

void ScenePause::Init()
{
	m_isExist = false;
}

void ScenePause::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/*Aキーを押したらメニューを表示、非表示*/
	if (Pad::IsTrigger(pad & PAD_INPUT_4))
	{
		if (!m_isExist)
		{
			m_isExist = true;
		}
		else
		{
			m_isExist = false;
		}
	}
}

void ScenePause::Draw()
{
	if (m_isExist)
	{
		// ポーズ画面の四角を表示
		SetDrawBlendMode(DX_BLENDMODE_MULA, 200);
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);// 表示モードを元に戻す
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0xffffff, false); // 枠を描画
		DrawString(kPosX ,150, "ポーズ画面", 0xffffff);
	}
}
