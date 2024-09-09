#include "SceneClear.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "Game.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneClear::SceneClear():
	m_textFrame(0),
	m_fadeAlpha(kStartFadeAlpha),
	m_select(kStart)
{
	m_clearText = LoadGraph("data/UI/clear.png");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneClear::~SceneClear()
{
	DeleteGraph(m_clearText);
}


/// <summary>
/// 更新
/// </summary>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	if (!CheckSoundMem(m_pSound->GetClearBgm()))
	{
		PlaySoundMem(m_pSound->GetClearBgm(), DX_PLAYTYPE_BACK);	// BGMを鳴らす
	}

	// フェードアウト
	m_fadeAlpha -= kFadeFrame;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	m_textFrame++;	// 文字点滅

	if (input.IsTriggered("down"))
	{
		PlaySoundMem(m_pSound->GetSelectSE(), DX_PLAYTYPE_BACK);	// SEを鳴らす
		m_select = (m_select + 1) % kSelectNum;						// 選択状態を1つ下げる
		if (m_cursorPosY == kTextPosY)
		{
			m_cursorPosY = kText2PosY;
		}
		else
		{
			m_cursorPosY = kTextPosY;
		}
	}
	if (input.IsTriggered("up"))
	{
		PlaySoundMem(m_pSound->GetSelectSE(), DX_PLAYTYPE_BACK);	// SEを鳴らす
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum; 		// 選択状態を1つ上げる
		if (m_cursorPosY == kTextPosY)
		{
			m_cursorPosY = kText2PosY;
		}
		else
		{
			m_cursorPosY = kTextPosY;
		}
	}

	//　画面遷移
	if (input.IsTriggered("OK"))
	{
		PlaySoundMem(m_pSound->GetDetermineSE(), DX_PLAYTYPE_BACK);	// SEを鳴らす
		// フェードイン
		m_fadeAlpha += kFadeFrame;
		if (m_fadeAlpha > kMaxFade)
		{
			m_fadeAlpha = kMaxFade;
		}

		if(m_select == kStart)
		{
			return std::make_shared<ScenePlaying>();	// ゲームシーンに移動
		}
		else if (m_select == kTitle)
		{
			return std::make_shared<SceneTitle>();		// タイトル画面に移動
		}
	}
	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneClear::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x17949B, true);	// 背景
	DrawGraph(kClearTextPosX, kClearTextPosY, m_clearText, true);			// CLEARの文字
	DrawGraph(kCursorPosX, m_cursorPosY, m_cursorHandle, true);				// カーソル表示

#if _DEBUG
	// MEMO:デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "クリア画面");
	// MEMO:中心線
	//DrawLine(Game::kScreenWidth * 0.5f, 0, Game::kScreenWidth * 0.5f, Game::kScreenHeight, 0x0000000, 1);
#endif

	// 選択中のテキストを点滅させる
	if (m_select == kStart)
	{
		DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "タイトルにもどる");
		if (m_textFrame % 60 >= kTextFrame) return;
		DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "もう1回遊ぶ");
	}
	else if (m_select == kTitle)
	{
		DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "もう1回遊ぶ");
		if (m_textFrame % 60 >= kTextFrame) return;
		DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "タイトルにもどる");
	}

	// フェードインアウト
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x126662, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}