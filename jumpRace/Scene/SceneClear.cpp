#include "SceneClear.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "ManagerFont.h"
#include "ManagerResult.h"
#include "ConversionTime.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneClear::SceneClear(std::shared_ptr<ManagerResult> pResult, int time):
	m_clearTime(time),
	m_select(kStart)
{
	m_pResult = pResult;

	m_pConversionTime->Change(m_pResult->GetHighScore());
	printfDx("%d\n", m_pResult->GetHighScore());
	printfDx("ベストタイム:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	m_pConversionTime->Change(m_pResult->GetSecond());
	printfDx("2位:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	m_pConversionTime->Change(m_pResult->GetThird());
	printfDx("3位:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
}


/// <summary>
/// デストラクタ
/// </summary>
SceneClear::~SceneClear()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneClear::Init()
{
	// 処理なし
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">ボタン入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	UpdateSelect(input);	// 選択状態更新

	if (input.IsTriggered("sceneChange"))
	{
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
	// 選択項目を表示
	DrawSelect();
	// 結果表示
	DrawResult();

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
		m_select = (m_select + 1) % kSelectNum;	// 選択状態を1つ下げる
	}
	if (input.IsTriggered("up"))
	{
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
		0x00ff00, true);

	// 枠表示
	for (int i = 0; i < kSelectNum; i++)
	{
		DrawGraph(kFramePosX, kFramePosY + kSelectMove * i, m_frameHandle, true);
	}

	DrawFormatStringToHandle(kStartTextPosX, kStartTextPosY, 0xffffff, m_pFont->GetTextFont(), "もう1回");
	DrawFormatStringToHandle(kTitleTextPosX, kTitleTextPosY, 0xffffff, m_pFont->GetTextFont(), "タイトルにもどる");
}


/// <summary>
/// 結果表示
/// </summary>
void SceneClear::DrawResult()
{
	// クリアタイム表示
	m_pConversionTime->Change(m_clearTime);	// タイム変換
	DrawFormatStringToHandle(kClearTimePosX, kClearTimePosY, 0xffffff, m_pFont->GetResultTimeFont(), 
		"クリアタイム:%02d:%03d", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	// ハイスコア表示
	m_pConversionTime->Change(m_pResult->GetHighScore());	// タイム変換
	DrawFormatStringToHandle(kTimePosX, kHighScorePosY, 0xffffff, m_pFont->GetResultTimeFont(),
		"1位:%02d:%03d", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	m_pConversionTime->Change(m_pResult->GetSecond());		// タイム変換
	DrawFormatStringToHandle(kTimePosX, kSecondPosY, 0xffffff, m_pFont->GetResultTimeFont(),
		"2位:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	m_pConversionTime->Change(m_pResult->GetThird());		// タイム変換
	DrawFormatStringToHandle(kTimePosX, kThirdPosY, 0xffffff, m_pFont->GetResultTimeFont(),
		"3位:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
}
