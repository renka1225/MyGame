#include "SceneBase.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "ManagerResult.h"
#include "ConversionTime.h"
#include "Game.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneBase::SceneBase():
	m_fadeAlpha(0),
	m_soundPal(kStartSoundPal)
{
	m_pFont = std::make_shared<ManagerFont>();
	m_pSound = std::make_shared<ManagerSound>();
	m_pConversionTime = std::make_shared<ConversionTime>();

	m_frameHandle = LoadGraph("data/UI/frame.png");
	m_buttonHandle = LoadGraph("data/UI/button.png");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneBase::~SceneBase()
{
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_buttonHandle);
}


/// <summary>
/// フェードイン
/// </summary>
void SceneBase::FadeIn()
{
	m_fadeAlpha += kFadeFrame;
	if (m_fadeAlpha > kMaxFade)
	{
		m_fadeAlpha = kMaxFade;
	}
}


/// <summary>
/// フェードアウト
/// </summary>
void SceneBase::FadeOut()
{
	m_fadeAlpha -= kFadeFrame;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}
}


/// <summary>
/// フェードインアウトの描画
/// </summary>
void SceneBase::DrawFade()
{
	// フェードイン
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
