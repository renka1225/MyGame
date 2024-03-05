#include "SceneTitle.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

/// <summary>
/// 定数
/// </summary>
namespace
{
	// OP動画再生時間
	constexpr int kMoveFrame = 1150;
	// OPを流すまでの時間
	constexpr int kStandFrame = 2000;

	// タイトルロゴ表示位置
	constexpr int kTitleLogoPosX = 970;
	constexpr int kTitleLogoPosY = 230;

	// 文字表示位置
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 720;

	// 選択カーソルの初期位置
	constexpr int kInitSelectPosX = 950;
	constexpr int kInitSelectPosY = 540;
	// 選択カーソルの移動量
	constexpr int kSelectmoveY = 185;
	// 選択カーソルのサイズ
	constexpr int kSelectSizeX = 450;
	constexpr int kSelectSizeY = 700;

	// 背景拡大率
	constexpr float kBgScale = 2.0f;
	// 背景画像の移動量
	constexpr float kBgMove = -3.0f;

	// フェードインアウトの時間
	constexpr int kFadeFrame = 8;
	// 初期フェード量
	constexpr int kStartFade = 180;
	// 最大フェード量
	constexpr int kFadeMax = 255;
}


SceneTitle::SceneTitle():
	m_select(kStart),
	m_isSceneStart(false),
	m_isSceneOption(false),
	m_bgMove(0.0f),
	m_moveFrame(kMoveFrame),
	m_standFrame(0),
	m_fadeAlpha(kStartFade)
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


/// <summary>
/// 初期化
/// </summary>
void SceneTitle::Init()
{
	m_isSceneStart = false;
	m_isSceneOption = false;
	m_moveFrame = kMoveFrame;
	m_fadeAlpha = kStartFade;
	m_select = kStart;
	m_selectPos = { kInitSelectPosX,  kInitSelectPosY };
	m_bgMove = kBgMove;

	// BGMを鳴らす
	if (CheckSoundMem(m_bgm) == 0)
	{
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
	}
}


/// <summary>
/// 更新
/// </summary>
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
		return;
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
		return;
	}

	// ZキーorAボタンを押したら遷移
	if (Pad::IsTrigger(PAD_INPUT_A))
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
		case kOption:
			m_isSceneOption = true;
			break;
		case kExit:
			DxLib_End();
			StopSoundMem(m_bgm);
			break;
		default:
			break;
		}
		return;
	}

	// しばらく放置したら動画を再生する
	m_standFrame++;
	if (m_standFrame > kStandFrame)
	{
		// OP再生
		StopSoundMem(m_bgm);
		PlayMovie("data/OP.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		m_standFrame = 0;

		Init();
	}

	// フェードインアウト
	if (m_isSceneStart)
	{
		m_fadeAlpha += kFadeFrame;
		if (m_fadeAlpha > kFadeMax) m_fadeAlpha = kFadeMax;
	}
	else
	{
		m_fadeAlpha -= kFadeFrame;
		if (m_fadeAlpha < 0) m_fadeAlpha = 0;
	}

	// 背景の表示位置の更新
	m_bgMove += kBgMove;
}


/// <summary>
/// 描画
/// </summary>
void SceneTitle::Draw()
{
	// 背景表示
	DrawBg();
	
	// ロゴ表示
	DrawRotaGraph(kTitleLogoPosX, kTitleLogoPosY,
		1.0f, 0.0f,
		m_logoHandle, true);

	// 文字表示
	DrawRectRotaGraph(kCharPosX, kCharPosY, 
		0, 0,
		kSelectSizeX, kSelectSizeY,
		1.0f, 0.0f, 
		m_charHandle, true, false);

	// 選択カーソルの表示
	DrawRectRotaGraph(static_cast<int>(m_selectPos.x), static_cast<int>(m_selectPos.y), 
		0, 0, 
		kSelectSizeX, kSelectSizeY, 
		1.0f, 0.0f, 
		m_selectHandle, true);

	// フェード描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x808080, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 不透明に戻す
}


/// <summary>
/// 背景描画
/// </summary>
void SceneTitle::DrawBg()
{
	// 画像サイズを取得
	Size bg2Size = { 0, 0 };
	Size bg3Size = { 0, 0 };
	Size bg4Size = { 0, 0 };
	GetGraphSize(m_bg2Handle, &bg2Size.width, &bg2Size.height);
	GetGraphSize(m_bg3Handle, &bg3Size.width, &bg3Size.height);
	GetGraphSize(m_bg4Handle, &bg4Size.width, &bg4Size.height);

	// スクロール量を計算する
	int scrollBg2 = static_cast<int>(m_bgMove * 0.25f) % static_cast<int>(bg2Size.width * kBgScale);
	int scrollBg3 = static_cast<int>(m_bgMove * 0.4f) % static_cast<int>(bg3Size.width * kBgScale);
	int scrollBg4 = static_cast<int>(m_bgMove) % static_cast<int>(bg4Size.width * kBgScale);

	// 描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(0, 0, m_bgHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			static_cast<int>(scrollBg2 + index * bg2Size.width * kBgScale),
			static_cast<int>(Game::kScreenHeight - bg2Size.height * kBgScale),
			0, 0,
			kBgScale, 0.0f,
			m_bg2Handle, true);
	}

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			static_cast<int>(scrollBg3 + index * bg3Size.width * kBgScale),
			static_cast<int>(Game::kScreenHeight - bg3Size.height * kBgScale),
			0, 0,
			kBgScale, 0.0f,
			m_bg3Handle, true);
	}

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			static_cast<int>(scrollBg4 + index * bg4Size.width * kBgScale),
			static_cast<int>(Game::kScreenHeight - bg4Size.height * kBgScale),
			0, 0,
			kBgScale, 0.0f,
			m_bg4Handle, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x00004d, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
