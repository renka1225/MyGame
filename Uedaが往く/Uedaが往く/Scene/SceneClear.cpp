#include "DxLib.h"
#include "Input.h"
#include "Vec2.h"
#include "Game.h"
#include "Sound.h"
#include "Font.h"
#include "UI.h"
#include "Ranking.h"
#include "ConversionTime.h"
#include "SceneSelectStage.h"
#include "SceneClear.h"

// 定数
namespace
{
	const char* const kSyoriTextPath = "data/UI/syori.png";	// 勝利のテキスト画像のファイル位置
	const Vec2 kSyoriTextPos = { 650, 100 };				// 勝利のテキスト画像表示位置
	const Vec2 kTimeTextPos = { 600, 550 };					// 時間表示位置
	const Vec2 kRankingTextPos = { 1250, 460 };				// "ランキング"表示位置
	constexpr float kTimeTextInterval = 100.0f;				// テキスト表示間隔
	constexpr float kTotalTimeTextAdj = 350.0f;				// テキスト表示位置調整
	constexpr float kTimeTextAdj = 250.0f;					// テキスト表示位置調整
	constexpr int kTextColor = 0xffffff;					// テキストの色
	constexpr int kTextColorRed = 0xb50d0d;					// テキストの色(赤)

	constexpr int kStartFadeAlpha = 255; // スタート時のフェード値
	constexpr int kFadeFrame = 4;		 // フェード変化量
}


/// <summary>
/// 引数付きコンストラクタ
/// </summary>
/// <param name="clearTime">クリアタイム</param>
SceneClear::SceneClear(int stageKind, std::vector<int> clearTime):
	m_totalClearTime(0)
{
	m_fadeAlpha = kStartFadeAlpha;
	m_clearTime = clearTime;
	m_stageKind = stageKind;
	m_textHandle = LoadGraph(kSyoriTextPath);
}


/// <summary>
/// デストラクタ
/// </summary>
SceneClear::~SceneClear()
{
	StopSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kClear)]);
	DeleteGraph(m_textHandle);
}


/// <summary>
/// 初期化
/// </summary>
/// <param name="stage">クリアしたステージ</param>
void SceneClear::Init()
{
	// トータルのクリア時間を計算する
	for (int i = 0; i < m_clearTime.size(); i++)
	{
		m_totalClearTime += m_clearTime[i];
	}

	// ランキングの更新、取得
	m_pRank->UpdateRanking(m_stageKind, m_totalClearTime);
	m_pRank->GetRanking(m_stageKind);
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <returns>遷移先</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	FadeOut(kFadeFrame); // フェードアウト

	// BGMを鳴らす
	if (!CheckSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kClear)]))
	{
		PlaySoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kClear)], DX_PLAYTYPE_LOOP);
	}

	if (input.IsTriggered("OK"))
	{
		FadeIn(kFadeFrame); // フェードイン
		return std::make_shared<SceneSelectStage>();
	}
	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneClear::Draw()
{
	// 背景表示
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xb3b3b3, true);

	// 勝利の文字を表示
	DrawGraphF(kSyoriTextPos.x, kSyoriTextPos.y, m_textHandle, true);

	// トータルタイム表示
	int totalMin = Conversion::ChangeMin(m_totalClearTime);
	int totalSec = Conversion::ChangeSec(m_totalClearTime);
	int totalMilliSec = Conversion::ChangeMilliSec(m_totalClearTime);
	DrawStringToHandle(kTimeTextPos.x - kTotalTimeTextAdj, kTimeTextPos.y, "TOTAL TIME", kTextColorRed, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearTime)]);
	DrawFormatStringFToHandle(kTimeTextPos.x, kTimeTextPos.y,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearTime)], "%02d:%02d:%03d", totalMin, totalSec, totalMilliSec);


	// クリアタイムを表示
	for (int i = 0; i < m_clearTime.size(); i++)
	{
		// クリアタイムをフレーム数から秒数に変換
		int min = Conversion::ChangeMin(m_clearTime[i]);
		int sec = Conversion::ChangeSec(m_clearTime[i]);
		int milliSec = Conversion::ChangeMilliSec(m_clearTime[i]);

		DrawFormatStringToHandle(kTimeTextPos.x - kTimeTextAdj, kTimeTextPos.y + kTimeTextInterval * (i + 1),
			kTextColorRed, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearTime)], "%d回戦 ", i + 1);
		DrawFormatStringFToHandle(kTimeTextPos.x, kTimeTextPos.y + kTimeTextInterval * (i + 1),
			kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearTime)], "%02d:%02d:%03d", min, sec, milliSec);
	}

	// ランキング表示
	DrawStringFToHandle(kRankingTextPos.x, kRankingTextPos.y,
		"ランキング", kTextColorRed, Font::m_fontHandle[static_cast<int>(Font::FontId::kRankingText)]);
	m_pRank->DrawClearRanking();

	// テキスト表示
	m_pUI->DrawClearButtonText();

	DrawFade();	// フェードインアウト描画

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "クリア画面", 0xffffff);
	// 中心線
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0x0000ff);
#endif
}
