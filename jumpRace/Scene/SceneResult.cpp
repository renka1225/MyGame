#include "SceneResult.h"
#include "SceneTitle.h"
#include "ManagerFont.h"
#include "ManagerResult.h"
#include "ConversionTime.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneResult::SceneResult()
{
	m_fadeAlpha = kStartFadeAlpha;
	m_rankingTextHandle = LoadGraph("data/UI/ranking.png");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneResult::~SceneResult()
{
	DeleteGraph(m_rankingTextHandle);
}


/// <summary>
/// 初期化
/// </summary>
void SceneResult::Init(std::shared_ptr<ManagerResult> pResult)
{
	m_pResult = pResult;
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">ボタン入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneResult::Update(Input& input)
{
	FadeOut();	// フェードアウト

	if (input.IsTriggered("back"))
	{
		FadeIn();	// フェードイン
		return std::make_shared<SceneTitle>();		//タイトル画面に移動
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneResult::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x456889, true);	// 背景表示
	DrawGraph(kRankingTextPosX, kRankingTextPosY, m_rankingTextHandle, true);		// ランキングの文字表示
	DrawRectRotaGraph(kButtonPosX, kButtonPosY, kButtonSize, kButtonSize, kButtonSize, kButtonSize, kButtonScale, 0.0f, m_buttonHandle, true);	// ボタン画像表示
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffffff, m_pFont->GetTextFont(), "でもどる");	// 文字表示

	DrawRanking();	// ランキング表示

	DrawFade();		// フェード

#ifdef _DEBUG
	// MEMO:デバッグ表示
	DrawString(0, 0, "ランキング画面", 0xffffff);
	// 中心線
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0xfffff);
#endif
}


/// <summary>
/// ランキング表示
/// </summary>
void SceneResult::DrawRanking()
{
	for (int i = 0; i < kDisplayRanking; i++)
	{
		auto ranking = m_pResult->GetRanking()[i]; // ランキングを取得
		m_pConversionTime->Change(ranking);		   // タイム変換
		if (i < 5)
		{
			DrawFormatStringToHandle(kRankPosX, kRankPosY + kIntervalY * i, 0xffffff, m_pFont->GetResultTimeFont(),
				"%02d位:%02d:%03d\n", (i + 1), m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
		}
		else
		{
			DrawFormatStringToHandle(kRank2PosX, kRankPosY + kIntervalY * (i % 5), 0xffffff, m_pFont->GetResultTimeFont(),
				"%02d位:%02d:%03d\n", (i + 1), m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
		}
	}
}