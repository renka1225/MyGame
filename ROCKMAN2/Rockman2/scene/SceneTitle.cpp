#include "SceneTitle.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// 文字表示位置
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 700;

	// 選択カーソルの初期位置
	constexpr int kInitSelectPosX = 950;
	constexpr int kInitSelectPosY = 580;
	// 選択カーソルの移動量
	constexpr int kSelectmoveY = 120;
	// 選択カーソルのサイズ
	constexpr int kSelectSizeX = 414;
	constexpr int kSelectSizeY = 700;

	// 背景画像の移動量
	constexpr int kBgMove = -4;
}

SceneTitle::SceneTitle():
	m_select(kStart),
	m_isSceneStart(false),
	m_isSceneOption(false),
	m_fadeAlpha(80)
{
	m_logoHandle = LoadGraph("data/image/Title/TitleLogo.png");
	m_selectHandle = LoadGraph("data/image/select.png");
	m_charHandle = LoadGraph("data/image/Title/titleChar.png");
	m_bg = LoadGraph("data/image/Title/bg.jpg");
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_logoHandle);
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_charHandle);
}

void SceneTitle::Init()
{
	m_isSceneStart = false;
	m_isSceneOption = false;
	m_select = kStart;
	m_selectPos = { kInitSelectPosX,  kInitSelectPosY };
	m_bgMove = { kBgMove, 0 };
}

void SceneTitle::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ↓キーを押したら選択状態を1つ下げる
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		m_select = (m_select + 1) % kSelectNum;
		m_selectPos.y += kSelectmoveY; // 選択カーソルを下に移動

		// 選択カーソルが一番下にだったら四角を一番上に戻す
		if (m_selectPos.y > kInitSelectPosY + kSelectmoveY * (kSelectNum - 1))
		{
			m_selectPos.y = kInitSelectPosY;
		}
	}
	// ↑キーを押したら選択状態を1つ上げる
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;
		m_selectPos.y -= kSelectmoveY;	// 選択カーソルを上に移動

		if (m_selectPos.y < kInitSelectPosY)
		{
			m_selectPos.y = kInitSelectPosY + kSelectmoveY * (kSelectNum - 1);
		}
	}

	// Zキーを押したとき
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// TODO:選択状態によって移動先を変える
		switch (m_select)
		{
		case kStart:
			m_isSceneStart = true;
			break;
		case kOption:
			m_isSceneOption = true;
			break;
		case kExit:
			DxLib_End();
			break;
		default:
			break;
		}
	}

	if (m_isSceneStart)
	{
		m_fadeAlpha += 3;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else
	{
		m_fadeAlpha -= 3;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}

	// 背景の表示位置の更新
	m_bgPos += m_bgMove;
}

void SceneTitle::Draw()
{
	// フェード描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xe6e6fa, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 不透明に戻す

	// 背景表示 TODO:背景画像変更、背景動くように
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
	DrawGraph(m_bgPos.x, 0, m_bg, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 表示モードを元に戻す
	
	// ロゴ表示
	DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 4, 1.0f, 0.0f, m_logoHandle, true);
	// 文字表示
	DrawRectRotaGraph(kCharPosX, kCharPosY, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_charHandle, true, false);
	// 選択カーソルの表示
	DrawRectRotaGraph(m_selectPos.x, m_selectPos.y, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_selectHandle, true, false);

}

void SceneTitle::End()
{
}
