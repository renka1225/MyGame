#include "SceneGameover.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "ManagerFont.h"
#include "Game.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneGameover::SceneGameover():
	m_textFrame(0),
	m_fadeAlpha(kMaxFade)
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneGameover::Init()
{
	// 処理なし
}


/// <summary>
/// 更新
/// </summary>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneGameover::Update(Input& input)
{
	// フェードアウト
	m_fadeAlpha -= kFadeFrame;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	// 文字点滅
	m_textFrame++;

	//　プレイ画面に遷移
	if (input.IsTriggered("OK"))
	{
		// フェードイン
		m_fadeAlpha += kFadeFrame;
		if (m_fadeAlpha > kMaxFade)
		{
			m_fadeAlpha = kMaxFade;
		}
		return std::make_shared<ScenePlaying>();
	}
	// タイトル画面に遷移
	else if (input.IsTriggered("debug"))
	{
		// フェードイン
		m_fadeAlpha += kFadeFrame;
		if (m_fadeAlpha > kMaxFade)
		{
			m_fadeAlpha = kMaxFade;
		}
		return std::make_shared<SceneTitle>();
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneGameover::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x17949B, true);

#if _DEBUG
	// デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "ゲームオーバー画面");
	// MEMO:中心線
	//DrawLine(Game::kScreenWidth * 0.5f, 0, Game::kScreenWidth * 0.5f, Game::kScreenHeight, 0x0000000, 1);
#endif

	if (m_textFrame % 60 >= 30) return;
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "もう1回遊ぶ");
	DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "タイトルにもどる");

	// フェードインアウト
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x126662, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}