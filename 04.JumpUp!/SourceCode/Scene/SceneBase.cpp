#include "DxLib.h"
#include "Game.h"
#include "SceneBase.h"

// 定数
namespace
{
	constexpr int kFadeColor = 0x5f9ea0; // フェードの色
	constexpr int kMaxFade = 255;		 // フェードの最大値
}

/// <summary>
/// コンストラクタ
/// </summary>
SceneBase::SceneBase():
	m_fadeAlpha(0)
{
}


/// <summary>
/// フェードイン処理
/// </summary>
void SceneBase::FadeIn()
{
	m_fadeAlpha = std::min(m_fadeAlpha, kMaxFade);
}


/// <summary>
/// フェードアウト処理
/// </summary>
void SceneBase::FadeOut()
{
	m_fadeAlpha = std::max(0, m_fadeAlpha);
}


/// <summary>
/// フェードインアウトの描画
/// </summary>
void SceneBase::DrawFade()
{
	// フェードイン
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kFadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
