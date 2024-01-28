#include "SceneTitle.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// 文字表示位置
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 700;

	// 背景拡大率
	constexpr float kBgScale = 2.0f;

	// 選択カーソルの初期位置
	constexpr int kInitSelectPosX = 960;
	constexpr int kInitSelectPosY = 580;
	// 選択カーソルの移動量
	constexpr int kSelectmoveY = 120;
	// 選択カーソルのサイズ
	constexpr int kSelectSizeX = 450;
	constexpr int kSelectSizeY = 700;

	// 背景画像の移動量
	constexpr int kBgMove = -3;
}

SceneTitle::SceneTitle():
	m_select(kStart),
	m_isSceneStart(false),
	m_isSceneOption(false),
	m_fadeAlpha(80),
	m_bgMove(0.0f)
{
	// 画像読み込み
	m_logoHandle = LoadGraph("data/image/TitleLogo.png");
	m_charHandle = LoadGraph("data/image/UI/titleChar.png");
	m_selectHandle = LoadGraph("data/image/UI/select.png");
	m_bgHandle = LoadGraph("data/image/BackGround/Title/bg1.png");
	m_bg2Handle = LoadGraph("data/image/BackGround/Title/bg2.png");
	m_bg3Handle = LoadGraph("data/image/BackGround/Title/bg3.png");
	m_bg4Handle = LoadGraph("data/image/BackGround/Title/bg4.png");

	// 音読み込み
	m_bgm = LoadSoundMem("data/sound/BGM/title.mp3");
	m_selectSE = LoadSoundMem("data/sound/SE/select.wav");
	m_cursorSE = LoadSoundMem("data/sound/SE/cursor.mp3");
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_logoHandle);
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_bg2Handle);
	DeleteGraph(m_bg3Handle);
	DeleteGraph(m_bg4Handle);
	DeleteSoundMem(m_bgm);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_cursorSE);
}

void SceneTitle::Init()
{
	m_isSceneStart = false;
	m_isSceneOption = false;
	m_select = kStart;
	m_selectPos = { kInitSelectPosX,  kInitSelectPosY };
	m_bgPos = { 0, 0 };
	m_bgMove = kBgMove;

	// BGMを鳴らす
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
}

void SceneTitle::Update()
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

	// Zキーを押したら遷移
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// SEを鳴らす
		PlaySoundMem(m_selectSE, DX_PLAYTYPE_BACK, true);

		// 画面遷移
		switch (m_select)
		{
		case kStart:
			m_isSceneStart = true;
			StopSoundMem(m_bgm);
			break;
		case kExit:
			DxLib_End();
			StopSoundMem(m_bgm);
			break;
		default:
			break;
		}
	}

	// フェードインアウト
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
	m_bgMove += kBgMove;
	
}

void SceneTitle::Draw()
{
	// フェード描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xe6e6fa, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 不透明に戻す

	// 背景表示
	BgDraw();
	
	// ロゴ表示
	DrawRotaGraph(Game::kScreenWidth * 0.5f, Game::kScreenHeight * 0.25f, 1.0f, 0.0f, m_logoHandle, true);
	// 文字表示
	DrawRectRotaGraph(kCharPosX, kCharPosY, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_charHandle, true, false);
	// 選択カーソルの表示
	DrawRectRotaGraph(m_selectPos.x, m_selectPos.y, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_selectHandle, true, false);
}

void SceneTitle::End()
{
}

// 背景描画
void SceneTitle::BgDraw()
{
	// 画像サイズを取得
	Size bg2Size;
	Size bg3Size;
	Size bg4Size;
	GetGraphSize(m_bg2Handle, &bg2Size.width, &bg2Size.height);
	GetGraphSize(m_bg3Handle, &bg3Size.width, &bg3Size.height);
	GetGraphSize(m_bg4Handle, &bg4Size.width, &bg4Size.height);

	// スクロール量を計算する
	int scrollBg2 = static_cast<int>(m_bgMove * 0.25f) % static_cast<int>(bg2Size.width * kBgScale);
	int scrollBg3 = static_cast<int>(m_bgMove * 0.5f) % static_cast<int>(bg3Size.width * kBgScale);
	int scrollBg4 = static_cast<int>(m_bgMove) % static_cast<int>(bg4Size.width * kBgScale);

	// 描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 240);
	DrawGraph(0, 0, m_bgHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			scrollBg2 + index * bg2Size.width * kBgScale,
			Game::kScreenHeight - bg2Size.height * kBgScale,
			0, 0,
			kBgScale, 0.0f,
			m_bg2Handle, true);
	}

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			scrollBg3 + index * bg3Size.width * kBgScale,
			Game::kScreenHeight - bg3Size.height * kBgScale,
			0, 0,
			kBgScale, 0.0f,
			m_bg3Handle, true);
	}

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			scrollBg4 + index * bg4Size.width * kBgScale,
			Game::kScreenHeight - bg4Size.height * kBgScale,
			0, 0,
			kBgScale, 0.0f,
			m_bg4Handle, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
