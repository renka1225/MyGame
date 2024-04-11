#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "ManagerFont.h"
#include "Game.h"
#include "DxLib.h"

SceneTitle::SceneTitle():
	m_textFrame(0),
	m_fadeAlpha(0),
	m_select(kStart)
{
	m_titleLogo = LoadGraph("data/UI/titleLogo.png");
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

	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;					// 選択状態を1つ下げる
	}
	if(input.IsTriggered("up"))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum; 	// 選択状態を1つ上げる
	}

	// シーン遷移
	if (input.IsTriggered("OK"))
	{
		// フェードイン
		m_fadeAlpha += kFadeFrame;
		if (m_fadeAlpha > kMaxFade)
		{
			m_fadeAlpha = kMaxFade;
		}

		if (m_select == kStart)
		{
			return std::make_shared<ScenePlaying>();	// ゲームシーンに移動
		}
		else if (m_select == kEnd)
		{
			DxLib_End();	// ゲーム終了
		}
	}
	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneTitle::Draw()
{
	// 背景表示
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x17949B, true);
	// タイトルロゴ表示
	DrawGraph(kLogoPosX, kLogoPosY, m_titleLogo, true);

#if _DEBUG
	// MEMO:デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "タイトル画面");
	// MEMO:中心線
	//DrawLine(Game::kScreenWidth * 0.5f, 0, Game::kScreenWidth * 0.5f, Game::kScreenHeight, 0x0000000, 1);
#endif

	// 選択中のテキストを点滅させる
	if (m_select == kStart)
	{
		DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "おわる");
		if (m_textFrame % 60 >= kTextFrame) return;
		DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "はじめる");
	}
	else if (m_select == kEnd)
	{
		DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "はじめる");
		if (m_textFrame % 60 >= kTextFrame) return;
		DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "おわる");
	}

	// フェードイン
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x126662, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}