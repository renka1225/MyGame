#include "SceneClear.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "ManagerResult.h"
#include "ConversionTime.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneClear::SceneClear(int time):
	m_clearTime(time),
	m_select(kStart)
{
	m_fadeAlpha = kStartFadeAlpha;
}


/// <summary>
/// 初期化
/// </summary>
void SceneClear::Init(std::shared_ptr<ManagerResult> pResult)
{
	m_pResult = pResult;
	PlaySoundMem(m_pSound->GetClearBgm(), DX_PLAYTYPE_LOOP);
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">ボタン入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	FadeOut();	// フェードアウト

	UpdateSelect(input);	// 選択状態更新

	if (input.IsTriggered("OK"))
	{
		FadeIn();	// フェードイン
		PlaySoundMem(m_pSound->GetSelectSE(), DX_PLAYTYPE_BACK);

		if (m_select == kStart)
		{
			return std::make_shared<ScenePlaying>();	// ゲームシーンに移動
		}
		else if (m_select == kTitle)
		{
			return std::make_shared<SceneTitle>();		//タイトル画面に移動
		}
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneClear::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x263a4d, true);	// 背景表示

	DrawSelect();	// 選択項目を表示
	DrawResult();	// 結果表示

	DrawFade();		// フェード

#ifdef _DEBUG
	// デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "クリア画面");
	// 中心線
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0xfffff);
#endif
}


/// <summary>
/// 選択状態の更新
/// </summary>
void SceneClear::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		PlaySoundMem(m_pSound->GetCursorSE(), DX_PLAYTYPE_BACK);
		m_select = (m_select + 1) % kSelectNum;	// 選択状態を1つ下げる
	}
	if (input.IsTriggered("up"))
	{
		PlaySoundMem(m_pSound->GetCursorSE(), DX_PLAYTYPE_BACK);
		m_select = (m_select + 1) % kSelectNum;	// 選択状態を1つ上げる
	}
}


/// <summary>
/// 選択項目表示
/// </summary>
void SceneClear::DrawSelect()
{
	// 選択中の項目に色をつける
	DrawBox(kNowSelectPosX, kNowSelectPosY + kSelectMove * m_select,
		kNowSelectPosX + kNowSelectWidth, kNowSelectPosY + kSelectMove * m_select + kNowSelectHeight,
		0x4289A3, true);

	// 枠表示
	for (int i = 0; i < kSelectNum; i++)
	{
		DrawGraph(kFramePosX, kFramePosY + kSelectMove * i, m_frameHandle, true);
	}

	DrawFormatStringToHandle(kStartTextPosX, kStartTextPosY, 0xffffff, m_pFont->GetTextFont(), "もう1回");
	DrawFormatStringToHandle(kTitleTextPosX, kTitleTextPosY, 0xffffff, m_pFont->GetTextFont2(), "タイトルにもどる");
}


/// <summary>
/// 結果表示
/// </summary>
void SceneClear::DrawResult()
{
	// クリアタイム表示
	m_pConversionTime->Change(m_clearTime);	// タイム変換
	DrawFormatStringToHandle(kClearTimePosX, kClearTimePosY, 0xffffff, m_pFont->GetResultTimeFont(), 
		"クリアタイム %02d:%03d", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	for (int i = 0; i < kDisplayRanking; i++)
	{
		m_pConversionTime->Change(m_pResult->GetRanking()[i]); // タイム変換
		DrawFormatStringToHandle(kTimePosX, kTimePosY + kIntervalY * i, 0xffffff, m_pFont->GetResultTimeFont(),
			"%d位 %02d:%03d\n", (i + 1), m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
	}
}