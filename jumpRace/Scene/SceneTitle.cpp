#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "SceneResult.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneTitle::SceneTitle():
	m_select(kStart)
{
	m_titleLogo = LoadGraph("data/UI/title.png");
	m_fadeAlpha = kStartFadeAlpha;
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
void SceneTitle::Init(std::shared_ptr<ManagerResult> pResult)
{
	m_pResult = pResult;
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">ボタン入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	if (!CheckSoundMem(m_pSound->GetTitleBgm()))
	{
		PlaySoundMem(m_pSound->GetTitleBgm(), DX_PLAYTYPE_BACK);
	}

	FadeOut();	// フェードアウト
	UpdateSelect(input);	// 選択状態更新

	if (input.IsTriggered("OK"))
	{
		FadeIn();	// フェードイン
		PlaySoundMem(m_pSound->GetSelectSE(), DX_PLAYTYPE_BACK);

		// 画面切り替え
		if (m_select == kStart)
		{
			return std::make_shared<ScenePlaying>();	// ゲームシーンに移動
		}
		else if (m_select == kResult)
		{
			return std::make_shared<SceneResult>();		// 結果確認画面に移動
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
	// クレジット表記
	DrawFormatStringToHandle(900, 670, 0xffffff, m_pFont->GetCreditFont(), "Sound/OtoLogic");
	DrawFormatStringToHandle(900, 690, 0xffffff, m_pFont->GetCreditFont(), "利用ソフト/VOICEVOX:ナースロボ＿タイプＴ");

	// タイトル表示
	DrawGraph(kTitleLogoPosX, kTitleLogoPosY, m_titleLogo, true);

	DrawSelect();	// 選択項目を表示

	DrawFade();		// フェードイン

#ifdef _DEBUG
	// デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "タイトル画面");
	// 中心線
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0xfffff);
#endif
}


/// <summary>
/// 選択状態の更新
/// </summary>
void SceneTitle::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		PlaySoundMem(m_pSound->GetCursorSE(), DX_PLAYTYPE_BACK);
		m_select = (m_select + 1) % kSelectNum;	// 選択状態を1つ下げる
	}
	if (input.IsTriggered("up"))
	{
		PlaySoundMem(m_pSound->GetCursorSE(), DX_PLAYTYPE_BACK);
		m_select = (m_select + 2) % kSelectNum;	// 選択状態を1つ上げる
	}
}


/// <summary>
/// 選択項目を表示
/// </summary>
void SceneTitle::DrawSelect()
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

	// テキスト表示
	DrawFormatStringToHandle(kStartTextPosX, kStartTextPosY, 0xffffff, m_pFont->GetTextFont(), "スタート");
	DrawFormatStringToHandle(kResultTextPosX, kResultTextPosY, 0xffffff, m_pFont->GetTextFont(), "ランキング");
	DrawFormatStringToHandle(kEndTextPosX, kEndTextPosY, 0xffffff, m_pFont->GetTextFont(), "おわる");
}
