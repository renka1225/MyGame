#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "Sound.h"
#include "SceneSelectStage.h"
#include "SceneTitle.h"
#include "Game.h"

// 定数
namespace
{
	const Vec2 kTitleLogoPos = { 950.0f, 400.0f };	// タイトルロゴ表示位置
	constexpr float kTitleLogoMinScale = 0.5f;		// タイトルロゴの最小サイズ
	constexpr float kTitleLogoMaxScale = 10.0f;		// タイトルロゴの最大サイズ
	constexpr float kTitleLogoChangeScale = 0.3f;	// タイトルロゴのサイズ変化量
	const Vec2 kTextPos = { 500.0f, 880.0f };		// "PRESS ANY BUTTON"のテキスト位置
	constexpr int kTextDisplayTime = 2;				// テキストを表示する間隔
	constexpr int kTextDisplayAnimTime = 240;		// テキストアニメーションの時間
	constexpr int kMaxAlpha = 255;					// 最大アルファ値
	constexpr int kMinAlpha = 30;					// 最小アルファ値
	constexpr int kTitleTime = 60;					// タイトルを表示するまでの時間
	constexpr int kTextTime = 120;					// テキストを表示するまでの時間
	constexpr int kBGMTime = 150;					// BGMを再生しはじめる時間
}

/// <summary>
/// コンストラクタ
/// </summary>
SceneTitle::SceneTitle():
	m_time(0),
	m_textDisplayTime(0),
	m_titleLogoScale(kTitleLogoMaxScale),
	m_textAlpha(0)
{
	m_titleLogo = LoadGraph("data/UI/title.png");
	m_titleLogoBack = LoadGraph("data/UI/titleBack.png");
	m_textHandle = LoadGraph("data/UI/PRESS.png");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneTitle::~SceneTitle()
{
	StopSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kTitleBGM)]);
	DeleteGraph(m_titleLogo);
	DeleteGraph(m_titleLogoBack);
	DeleteGraph(m_textHandle);
}


/// <summary>
/// 初期化
/// </summary>
void SceneTitle::Init()
{
	// 処理なし
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	m_time++;

	UpdateDisplay(); // テキストの表示を更新する

	// タイトルロゴ表示後BGMを鳴らす
	if (m_time > kBGMTime)
	{
		if (!CheckSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kTitleBGM)]))
		{
			PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kTitleBGM)], DX_PLAYTYPE_LOOP);
		}
	}

	// シーン遷移
	if (input.IsTriggered("OK"))
	{
		return std::make_shared<SceneSelectStage>(); // ステージ選択へ遷移
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneTitle::Draw()
{
	// 背景描画
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);

	// タイトルロゴ表示
	DrawRectRotaGraphF(kTitleLogoPos.x, kTitleLogoPos.y, 0, 0, Game::kScreenWidth, Game::kScreenHeight, m_titleLogoScale, 0.0f, m_titleLogoBack, true);
	if (m_time > kTitleTime)
	{
		DrawRectRotaGraphF(kTitleLogoPos.x, kTitleLogoPos.y, 0, 0, Game::kScreenWidth, Game::kScreenHeight, m_titleLogoScale, 0.0f, m_titleLogo, true);
	}

	// "PRESSANYBUTTON"表示
	if (m_time > kTextTime)
	{
		// 文字を点滅させる
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_textAlpha);
		DrawGraphF(kTextPos.x, kTextPos.y, m_textHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "タイトル画面", 0xffffff);
#endif
}


/// <summary>
/// テキストの表示を更新する
/// </summary>
void SceneTitle::UpdateDisplay()
{
	// テキストのアルファ値を調整する
	m_textDisplayTime += kTextDisplayTime;
	m_textDisplayTime %= kTextDisplayAnimTime;
	// MEMO:sin波を使って0～1の範囲にする
	float sinAlpha = 0.5f + 0.5f * sinf(static_cast<float>(m_textDisplayTime) / kTextDisplayAnimTime * DX_PI_F);
	m_textAlpha = kMinAlpha + static_cast<int>((kMaxAlpha - kMinAlpha) * sinAlpha);

	// タイトルロゴのサイズをだんだん小さくする
	m_titleLogoScale -= kTitleLogoChangeScale;
	m_titleLogoScale = std::max(kTitleLogoMinScale, m_titleLogoScale);
}
