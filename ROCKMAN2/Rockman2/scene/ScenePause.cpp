#include "ScenePause.h"
#include "DxLib.h"

namespace
{
	constexpr int kWidth = 240;
	constexpr int kHeight = 480;
}

ScenePause::ScenePause():
	m_pos(0, 0),
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
	if (pad & PAD_INPUT_4)
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
		DrawBox(m_pos.x, m_pos.y, m_pos.x + kWidth, m_pos.y + kHeight, 0x000000, true);
		DrawString(10,200, "ポーズ画面", 0xffffff);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);// 表示モードを元に戻す
	
}
