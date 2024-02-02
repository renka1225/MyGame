#include "SceneClear.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// クリア文字表示位置
	constexpr int kClearPosX = 960;
	constexpr int kClearPosY = 300;

	// クリア文字のサイズ
	constexpr int kClearSizeX = 1035;
	constexpr int kClearSizeY = 171;

	// 文字表示位置
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 700;

	// 選択カーソルの初期位置
	constexpr int kInitSelectPosX = 910;
	constexpr int kInitSelectPosY = 610;
	// 選択カーソルの移動量
	constexpr int kSelectmoveY = 190;
	// 選択カーソルのサイズ
	constexpr int kSelectSizeX = 500;
	constexpr int kSelectSizeY = 700;
}


SceneClear::SceneClear():
	m_select(kSelectStage),
	m_isSceneSelectStage(false),
	m_isSceneTitle(false),
	m_fadeAlpha(255)
{
	// 画像読み込み
	m_bgHandle = LoadGraph("data/image/BackGround/clear.png");
	m_clearHandle = LoadGraph("data/image/UI/clear.png");
	m_charHandle = LoadGraph("data/image/UI/clearSelect.png");
	m_selectHandle = LoadGraph("data/image/UI/select.png");

	// 音読み込み
	m_bgm = LoadSoundMem("data/sound/BGM/clear.mp3");
	m_selectSE = LoadSoundMem("data/sound/SE/select.wav");
	m_cursorSE = LoadSoundMem("data/sound/SE/cursor.mp3");
}

SceneClear::~SceneClear()
{
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_clearHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_selectHandle);
	DeleteSoundMem(m_bgm);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_cursorSE);
}

void SceneClear::Init()
{
	m_isSceneSelectStage = false;
	m_isSceneTitle = false;
	m_select = kSelectStage;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
	m_fadeAlpha = 255;

	// BGMを鳴らす
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
}

void SceneClear::End()
{
}

void SceneClear::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ↓キーを押したら選択状態を1つ下げる
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		// SEを鳴らす
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

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
		// SEを鳴らす
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;
		m_selectPos.y -= kSelectmoveY;	// 選択カーソルを上に移動

		if (m_selectPos.y < kInitSelectPosY)
		{
			m_selectPos.y = kInitSelectPosY + kSelectmoveY * (kSelectNum - 1);
		}
	}

	// ZキーorAボタンを押したとき
	if (Pad::IsTrigger(PAD_INPUT_A))
	{
		// SEを鳴らす
		PlaySoundMem(m_selectSE, DX_PLAYTYPE_NORMAL, true);

		// 移動先を決定
		switch (m_select)
		{
		case kSelectStage:
			m_isSceneSelectStage = true;
			StopSoundMem(m_bgm);
			break;
		case kTitle:
			m_isSceneTitle = true;
			StopSoundMem(m_bgm);
			break;
		default:
			break;
		}
	}

	// フェードインアウト
	if (m_isSceneSelectStage || m_isSceneTitle)
	{
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else
	{
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
}

void SceneClear::Draw()
{
	// 背景表示
	DrawGraph(0, 0, m_bgHandle, false);
	// クリア表示
	DrawRectRotaGraph(kClearPosX, kClearPosY, 0, 0, kClearSizeX, kClearSizeY, 0.8f, 0.0f, m_clearHandle, true, false);
	// 文字表示
	DrawRectRotaGraph(kCharPosX, kCharPosY, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_charHandle, true, false);
	// 選択カーソルの表示
	DrawRectRotaGraph(m_selectPos.x, m_selectPos.y, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_selectHandle, true, false);

#ifdef _DEBUG
	DrawString(8, 16, "クリア画面", 0xffffff, false);
#endif
}
