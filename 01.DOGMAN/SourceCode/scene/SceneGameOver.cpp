#include "SceneGameOver.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

/// <summary>
/// 定数
/// </summary>
namespace
{
	// Gameoverの文字表示位置
	constexpr int kGameOverPosX = 960;
	constexpr int kGameOverPosY = 280;
	// Gameoverの文字サイズ
	constexpr int kGameOverSizeX = 1592;
	constexpr int kGameOverSizeY = 174;
	// Gameoverの文字拡大率
	constexpr float kGameOverScale = 0.8f;

	// 文字表示位置
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 720;

	// 選択カーソルの初期位置
	constexpr int kInitSelectPosX = 910;
	constexpr int kInitSelectPosY = 540;
	// 選択カーソルの移動量
	constexpr int kSelectmoveY = 185;
	// 選択カーソルのサイズ
	constexpr int kSelectSizeX = 500;
	constexpr int kSelectSizeY = 700;

	// 背景拡大率
	constexpr float kBgScale = 3.0f;
	// 背景画像の移動量
	constexpr float kBgMove = -1.0f;

	//フェード
	constexpr int kFadeFrame = 8;
	// 最大フェード量
	constexpr int kFadeMax = 255;
}


SceneGameOver::SceneGameOver():
	m_select(kRetry),
	m_isSceneRetry(false),
	m_isSceneSelect(false),
	m_isSceneTitle(false),
	m_fadeAlpha(kFadeMax),
	m_bgMove(0.0f)
{
	// 画像読み込み
	m_bgHandle = LoadGraph("data/image/BackGround/gameover/gameover.png");
	m_bg2Handle = LoadGraph("data/image/BackGround/gameover/2.png");
	m_bg3Handle = LoadGraph("data/image/BackGround/gameover/3.png");
	m_gameoverHandle = LoadGraph("data/image/UI/gameover.png");
	m_charHandle = LoadGraph("data/image/UI/gameoverSelect.png");
	m_selectHandle = LoadGraph("data/image/UI/select.png");

	// 音読み込み
	m_bgm = LoadSoundMem("data/sound/BGM/gameover.mp3");
	m_selectSE = LoadSoundMem("data/sound/SE/select.wav");
	m_cursorSE = LoadSoundMem("data/sound/SE/cursor.mp3");
}


SceneGameOver::~SceneGameOver()
{
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_bg2Handle);
	DeleteGraph(m_bg3Handle);
	DeleteGraph(m_gameoverHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_selectHandle);
	DeleteSoundMem(m_bgm);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_cursorSE);
}


/// <summary>
/// 初期化
/// </summary>
void SceneGameOver::Init()
{
	m_isSceneRetry = false;
	m_isSceneSelect = false;
	m_isSceneTitle = false;
	m_fadeAlpha = kFadeMax;
	m_select = kRetry;
	m_selectPos = { kInitSelectPosX, kInitSelectPosY };
	m_bgMove = kBgMove;

	// BGMを鳴らす
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
}


/// <summary>
/// 更新
/// </summary>
void SceneGameOver::Update()
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
		case kRetry:
			m_isSceneRetry = true;
			StopSoundMem(m_bgm);
			break;
		case kSelect:
			m_isSceneSelect = true;
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
	if (m_isSceneRetry || m_isSceneTitle)
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
void SceneGameOver::Draw()
{
	// 背景表示
	DrawBg();

	// ゲームオーバー表示
	DrawRectRotaGraph(kGameOverPosX, kGameOverPosY, 
		0, 0,
		kGameOverSizeX, kGameOverSizeY, 
		kGameOverScale, 0.0f,
		m_gameoverHandle, true);

	// 文字表示
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

#ifdef _DEBUG
	DrawString(10, 10, "ゲームオーバー", 0xff0000);
#endif
}


/// <summary>
/// 背景描画
/// </summary>
void SceneGameOver::DrawBg()
{
	// 画像サイズを取得
	Size bg2Size;
	Size bg3Size;
	GetGraphSize(m_bg2Handle, &bg2Size.width, &bg2Size.height);
	GetGraphSize(m_bg3Handle, &bg3Size.width, &bg3Size.height);

	// スクロール量を計算する
	int scrollBg2 = static_cast<int>(m_bgMove * 0.1f) % static_cast<int>(bg2Size.width * kBgScale);
	int scrollBg3 = static_cast<int>(m_bgMove * 0.5f) % static_cast<int>(bg3Size.width * kBgScale);

	// 描画
	DrawGraph(0, 0, m_bgHandle, true);

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

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

