#include "SceneOption.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

/// <summary>
/// 定数
/// </summary>
namespace
{
	// フェード最大値
	constexpr int kFadeMax = 255;
	// フェード
	constexpr int kFadeFrame = 8;
}


SceneOption::SceneOption():
	m_isSceneTitle(false),
	m_fadeAlpha(kFadeMax)
{
	m_exHandle = LoadGraph("data/image/ex.png");
}


SceneOption::~SceneOption()
{
	DeleteGraph(m_exHandle);
}


/// <summary>
/// 初期化
/// </summary>
void SceneOption::Init()
{
	m_isSceneTitle = false;
}


/// <summary>
/// 更新
/// </summary>
void SceneOption::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// XキーorBボタンを押したらタイトル画面に戻る
	if (Pad::IsTrigger(PAD_INPUT_B))
	{
		m_isSceneTitle = true;
	}

	// フェードイン
	m_fadeAlpha -= kFadeFrame;
	if (m_fadeAlpha < 0) m_fadeAlpha = 0;
}


/// <summary>
/// 描画
/// </summary>
void SceneOption::Draw()
{
	DrawGraph(0, 0, m_exHandle, true);

#ifdef _DEBUG
	DrawString(20, 20, "操作説明画面", 0xffffff);
#endif
}