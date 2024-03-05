#include "SceneStageSelect.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

/// <summary>
/// 定数
/// </summary>
namespace
{
	// SelectStageの文字表示位置
	constexpr int kSelectCharPosX = 300;
	constexpr int kSelectCharPosY = 150;

	// 文字間隔
	constexpr int kCharInterval = 50;
	// 文字表示位置
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 700;

	// 選択カーソルの初期位置
	constexpr int kInitSelectPosX = 930;
	constexpr int kInitSelectPosY = 520;
	// 選択カーソルの移動量
	constexpr int kSelectmoveY = 185;
	// 選択カーソルのサイズ
	constexpr int kSelectSizeX = 500;
	constexpr int kSelectSizeY = 700;

	// 背景拡大率
	constexpr float kBgScale = 2.0f;
	// 背景画像の移動量
	constexpr int kBgMove = -3;

	// フェード
	constexpr int kFadeFrame = 8;
	// 初期フェード量
	constexpr int kStartFade = 180;
	// 最大フェード量
	constexpr int kFadeMax = 255;
}


SceneStageSelect::SceneStageSelect() :
	m_select(kStage1),
	m_isSceneTutorial(false),
	m_isSceneStage1(false),
	m_isSceneTitle(false),
	m_bgMove(0.0f),
	m_fadeAlpha(kFadeMax),
	m_selectPos(kInitSelectPosX, kInitSelectPosY)
{
	// 画像読み込み
	m_selectHandle = LoadGraph("data/image/UI/select.png");
	m_selectCharHandle = LoadGraph("data/image/UI/selectRogo.png");
	m_charHandle = LoadGraph("data/image/UI/stageSelect.png");
	m_bgHandle = LoadGraph("data/image/BackGround/Title/bg1.png");
	m_bg2Handle = LoadGraph("data/image/BackGround/Title/bg2.png");
	m_bg3Handle = LoadGraph("data/image/BackGround/Title/bg3.png");
	m_bg4Handle = LoadGraph("data/image/BackGround/Title/bg4.png");
	
	// 音読み込み
	m_bgm = LoadSoundMem("data/sound/BGM/stageSelect.mp3");
	m_selectSE = LoadSoundMem("data/sound/SE/select.wav");
	m_cursorSE = LoadSoundMem("data/sound/SE/cursor.mp3");
}


SceneStageSelect::~SceneStageSelect()
{
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_selectCharHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_bg2Handle);
	DeleteGraph(m_bg3Handle);
	DeleteGraph(m_bg4Handle);
	DeleteGraph(m_bgm);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_cursorSE);
}


/// <summary>
/// 初期化
/// </summary>
void SceneStageSelect::Init()
{
	m_isSceneTutorial = false;
	m_isSceneStage1 = false;
	m_isSceneTitle = false;
	m_fadeAlpha = kStartFade;
	m_select = kStageTutorial;
	m_bgPos = { 0, 0 };
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
	
	// BGMを鳴らす
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
}


/// <summary>
/// 更新
/// </summary>
void SceneStageSelect::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ↓キーを押したら選択状態を1つ下げる
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		// SEを鳴らす
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

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
		// SEを鳴らす
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;
		m_selectPos.y -= kSelectmoveY;	// 選択中の四角を上に移動

		if (m_selectPos.y < kInitSelectPosY)
		{
			m_selectPos.y = kInitSelectPosY + kSelectmoveY * (kSelectNum - 1);
		}
	}

	// ZキーorAボタンを押したとき
	if (Pad::IsTrigger(pad & PAD_INPUT_A))
	{
		// SEを鳴らす
		PlaySoundMem(m_selectSE, DX_PLAYTYPE_NORMAL, true);

		switch (m_select)
		{
		case kStageTutorial:
			m_isSceneTutorial = true;
			StopSoundMem(m_bgm);
			break;
		case kStage1:
			m_isSceneStage1 = true;
			StopSoundMem(m_bgm);
			break;
		case kBackTitle:
			m_isSceneTitle = true;
			StopSoundMem(m_bgm);
			break;
		default:
			break;
		}
	}

	// フェードイン
	if (m_isSceneTutorial || m_isSceneStage1 || m_isSceneTitle)
	{
		m_fadeAlpha += kFadeFrame;
		if (m_fadeAlpha > kFadeMax) m_fadeAlpha = kFadeMax;
	}
	// フェードアウト
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
void SceneStageSelect::Draw()
{
	// 背景表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawGraph(0, 0, m_bgHandle, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 表示モードを元に戻す

	// 文字表示
	DrawGraph(kSelectCharPosX, kSelectCharPosY, m_selectCharHandle, true);
	DrawRectRotaGraph(kCharPosX, kCharPosY, 
		0, 0, 
		kSelectSizeX, kSelectSizeY, 
		1.0f, 0.0f, 
		m_charHandle, true);

	// 選択カーソルの表示
	DrawRectRotaGraph(static_cast<int>(m_selectPos.x), static_cast<int>(m_selectPos.y), 
		0, 0, 
		kSelectSizeX, kSelectSizeY, 
		1.0f, 0.0f, 
		m_selectHandle, true);

	// フェード描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x808080, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


/// <summary>
/// 背景描画
/// </summary>
void SceneStageSelect::DrawBg()
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

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
