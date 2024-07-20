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
	constexpr float kTitleLogoScale = 0.5f;
}

/// <summary>
/// コンストラクタ
/// </summary>
SceneTitle::SceneTitle()
{
	m_titleLogo = LoadGraph("data/UI/titleLogo.png");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogo);
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
	DrawRectRotaGraphF(kTitleLogoPos.x, kTitleLogoPos.y, 0, 0, Game::kScreenWidth, Game::kScreenHeight, kTitleLogoScale, 0.0f, m_titleLogo, true);

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "タイトル画面", 0xffffff);
#endif
}
