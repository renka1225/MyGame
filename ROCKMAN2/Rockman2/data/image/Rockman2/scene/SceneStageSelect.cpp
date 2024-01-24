#include "SceneStageSelect.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// 文字間隔
	constexpr int kCharInterval = 50;

	// 文字表示位置
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 700;

	// 選択カーソルの初期位置
	constexpr int kInitSelectPosX = 920;
	constexpr int kInitSelectPosY = 500;
	// 選択カーソルの移動量
	constexpr int kSelectmoveY = 135;
	// 選択カーソルのサイズ
	constexpr int kSelectSizeX = 500;
	constexpr int kSelectSizeY = 700;
}

SceneStageSelect::SceneStageSelect() :
	m_select(kStage1),
	m_isSceneStage1(false),
	m_isSceneStage2(false),
	m_isSceneStage3(false),
	m_isSceneTitle(false),
	m_fadeAlpha(255),
	m_selectPos(kInitSelectPosX, kInitSelectPosY)
{
	m_selectHandle = LoadGraph("data/image/UI/select.png");
	m_selectCharHandle = LoadGraph("data/image/UI/selectRogo.png");
	m_charHandle = LoadGraph("data/image/UI/stageSelect.png");
	m_bgHandle = LoadGraph("data/image/BackGround/stageSelect.png");
}

SceneStageSelect::~SceneStageSelect()
{
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_selectCharHandle);
	DeleteGraph(m_bgHandle);
}

void SceneStageSelect::Init()
{
	m_isSceneStage1 = false;
	m_isSceneStage2 = false;
	m_isSceneStage3 = false;
	m_isSceneTitle = false;
	m_select = kStage1;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
}

void SceneStageSelect::Update()
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
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// TODO:選択状態によって移動先を変える
		switch (m_select)
		{
		case kStage1:
			m_isSceneStage1 = true;
			break;
		case kStage2:
			m_isSceneStage2 = true;
			break;
		case kStage3:
			m_isSceneStage3 = true;
			break;
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

void SceneStageSelect::Draw()
{
	// フェード描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xe6e6fa, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 不透明に戻す

	// 背景表示 TODO:背景動かす
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawGraph(0, 0, m_bgHandle, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 表示モードを元に戻す

	// 文字表示
	DrawGraph(300, 150, m_selectCharHandle, true);
	DrawRectRotaGraph(kCharPosX, kCharPosY, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_charHandle, true, false);
	// 選択カーソルの表示
	DrawRectRotaGraph(m_selectPos.x, m_selectPos.y, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_selectHandle, true, false);
}

void SceneStageSelect::End()
{
}
