#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "SceneSelectStage.h"
#include "SceneTitle.h"
#include "Game.h"

// 定数
namespace
{
	const Vec2 kTitleLogoPos = { 950, 400 };
	const Vec2 kTitleBackPos = { 950,400 };
	constexpr float kTitleLogoScale = 0.5f;
	constexpr int kTitleTime = 10;			// タイトルを表示するまでの時間
	constexpr int kTextTime = 60;			// テキストを表示するまでの時間
	constexpr int kTextDisplayTime = 100;	// テキストを表示する間隔
}

/// <summary>
/// コンストラクタ
/// </summary>
SceneTitle::SceneTitle():
	m_titleTime(kTitleTime),
	m_textTime(kTextTime),
	m_textDisplayTime(0)
{
	m_titleLogo = LoadGraph("data/UI/title.png");
	m_titleLogoBack = LoadGraph("data/UI/titleBack.png");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogo);
	DeleteGraph(m_titleLogoBack);
}


/// <summary>
/// 初期化
/// </summary>
void SceneTitle::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <returns></returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	m_titleTime--;
	m_textTime--;
	m_textDisplayTime++;

	// シーン遷移
	if (input.IsTriggered("OK"))
	{
		return std::make_shared<SceneSelectStage>();
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneTitle::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);
	// タイトルロゴ表示
	DrawRectRotaGraphF(kTitleBackPos.x, kTitleBackPos.y, 0, 0, Game::kScreenWidth, Game::kScreenHeight, kTitleLogoScale, 0.0f, m_titleLogoBack, true);
	if (m_titleTime < 0)
	{
		DrawRectRotaGraphF(kTitleLogoPos.x, kTitleLogoPos.y, 0, 0, Game::kScreenWidth, Game::kScreenHeight, kTitleLogoScale, 0.0f, m_titleLogo, true);
	}

	if (m_textTime < 0)
	{
		if (m_textDisplayTime % 180 >= kTextDisplayTime) return;
		DrawString(900, 800, "PRESS ANY BUTTON", 0x000000);
	}

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "タイトル画面", 0xffffff);
#endif
}
