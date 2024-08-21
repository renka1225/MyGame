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
	const Vec2 kTimeTextPos = { 400, 550 };					// 時間表示位置
	const Vec2 kRankingTextPos = { 1250, 460 };				// "ランキング"表示位置
	constexpr float kTimeTextInterval = 100.0f;				// テキスト表示間隔
	constexpr float kTimeTextAdj = 155.0f;					// テキスト表示位置調整
	constexpr int kTextColor = 0xfffffff;					// テキストの色
}


/// <summary>
/// 引数付きコンストラクタ
/// </summary>
/// <param name="clearTime">クリアタイム</param>
SceneClear::SceneClear(std::vector<int> clearTime):
	m_totalClearTime(0)
{
	m_textHandle = LoadGraph(kSyoriTextPath);
	m_clearTime = clearTime;
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
void SceneClear::Init()
{
	// トータルのクリア時間を計算する
	for (int i = 0; i < m_clearTime.size(); i++)
	{
		m_totalClearTime += m_clearTime[i];
	}

	// ランキングの更新、取得
	m_pRank->UpdateRanking(m_totalClearTime);
	m_pRank->GetRanking();
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <returns>遷移先</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	// BGMを鳴らす
	if (!CheckSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kClear)]))
	{
		PlaySoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kClear)], DX_PLAYTYPE_LOOP);
	}

	if (input.IsTriggered("OK"))
	{
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
	DrawFormatStringFToHandle(kTimeTextPos.x - kTimeTextAdj, kTimeTextPos.y,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearTime)], "TOTAL TIME %02d:%02d:%03d", totalMin, totalSec, totalMilliSec);

	// クリアタイムをフレーム数から秒数に変換
	for (int i = 0; i < m_clearTime.size(); i++)
	{
		int min = Conversion::ChangeMin(m_clearTime[i]);
		int sec = Conversion::ChangeSec(m_clearTime[i]);
		int milliSec = Conversion::ChangeMilliSec(m_clearTime[i]);

		DrawFormatStringFToHandle(kTimeTextPos.x, kTimeTextPos.y + kTimeTextInterval * (i + 1),
			kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearTime)], "%d回戦 %02d:%02d:%03d", i + 1, min, sec, milliSec);
	}

	// ランキング表示
	DrawStringFToHandle(kRankingTextPos.x, kRankingTextPos.y,
		"ランキング", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kRankingText)]);
	m_pRank->DrawClearRanking();

	// テキスト表示
	m_pUI->DrawClearButtonText();

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "クリア画面", 0xffffff);
	// 中心線
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0x0000ff);
#endif
}
