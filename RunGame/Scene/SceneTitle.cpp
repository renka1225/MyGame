#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "ManagerFont.h"
#include "Game.h"
#include "DxLib.h"

SceneTitle::SceneTitle():
	m_textFrame(0),
	m_fadeAlpha(0)
{
	m_titleLogo = LoadGraph("data/title_test.png");
}


SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogo);
}


/// <summary>
/// 初期化
/// </summary>
void SceneTitle::Init()
{
	// 処理なし
}


/// <summary>
///	更新
/// </summary>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	m_textFrame++;

	// プレイ画面に遷移
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
	// ゲーム終了
	if (input.IsTriggered("end"))
	{
		DxLib_End();
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneTitle::Draw()
{
	// タイトルロゴ表示
	DrawGraph(0, 0, m_titleLogo, false);

#if _DEBUG
	// MEMO:デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "タイトル画面");
	// MEMO:中心線
	//DrawLine(Game::kScreenWidth * 0.5f, 0, Game::kScreenWidth * 0.5f, Game::kScreenHeight, 0x0000000, 1);
#endif

	// テキスト表示
	if (m_textFrame % 60 >= 30) return;
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "はじめる");
	DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "おわる");

	// フェードイン
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x126662, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}