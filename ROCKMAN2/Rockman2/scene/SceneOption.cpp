#include "SceneOption.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// 文字間隔
	constexpr int kCharInterval = 50;

	// 文字表示位置
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 600;

	// 選択カーソルの初期位置
	constexpr int kInitSelectPosX = 950;
	constexpr int kInitSelectPosY = 340;
	// 選択カーソルの移動量
	constexpr int kSelectmoveY = 190;
	// 選択カーソルのサイズ
	constexpr int kSelectSizeX = 414;
	constexpr int kSelectSizeY = 700;
}


SceneOption::SceneOption():
	m_select(kBackTitle),
	m_isSceneTitle(false),
	m_fadeAlpha(255),
	m_charHandle(-1)
{
	m_selectHandle = LoadGraph("data/image/select.png");
}

SceneOption::~SceneOption()
{
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_charHandle);
}

void SceneOption::Init()
{
	m_isSceneTitle = false;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
}

void SceneOption::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ↓キーを押したら選択状態を1つ下げる
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		m_select = (m_select + 1) % kSelectNum;
		m_selectPos.y += kSelectmoveY; // 選択中の四角を下に移動

		// 選択中の四角が一番下にだったら四角を一番上に戻す
		if (m_selectPos.y > kInitSelectPosY + kSelectmoveY * (kSelectNum - 1))
		{
			m_selectPos.y = kInitSelectPosY;
		}
	}
	// ↑キーを押したら選択状態を1つ上げる
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;
		m_selectPos.y -= kSelectmoveY;	// 選択中の四角を上に移動

		if (m_selectPos.y < kInitSelectPosY)
		{
			m_selectPos.y = kInitSelectPosY + kSelectmoveY * (kSelectNum - 1);
		}
	}

	// Zキーを押したとき
	if (Pad::IsTrigger(PAD_INPUT_B))
	{
		// TODO:選択状態によって移動先を変える
		switch (m_select)
		{
		case kBackTitle:
			m_isSceneTitle = true;
			break;
		default:
			break;
		}
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

#ifdef _DEBUG
	DrawString(20, 20, "オプション画面", 0xffffff);
#endif

}

void SceneOption::End()
{
}
