#include "DxLib.h"
#include "Input.h"
#include "Vec2.h"
#include "Game.h"
#include "ConversionTime.h"
#include "SceneSelectStage.h"
#include "SceneClear.h"

// 定数
namespace
{
	const char* const kSyoriTextPath = "data/UI/syori.png";	// 勝利のテキスト画像のファイル位置
	const Vec2 kSyoriTextPos = { 650, 100 };				// 勝利のテキスト画像表示位置
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
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <returns></returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
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
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xb3b3b3, true);

	// 勝利の文字を表示
	DrawGraphF(kSyoriTextPos.x, kSyoriTextPos.y, m_textHandle, true);

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "クリア画面", 0xffffff);
	// 中心線
	DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0x0000ff);

	// クリアタイムをフレーム数から秒数に変換
	for (int i = 0; i < m_clearTime.size(); i++)
	{
		int min = Conversion::ChangeMin(m_clearTime[i]);
		int sec = Conversion::ChangeSec(m_clearTime[i]);
		int milliSec = Conversion::ChangeMilliSec(m_clearTime[i]);

		// クリアタイム表示
		DrawFormatString(500, 650 + 100 * i, 0x000000, "%d回戦 %02d:%02d:%03d", i + 1, min, sec, milliSec);
	}

	// トータルタイム表示
	int totalMin = Conversion::ChangeMin(m_totalClearTime);
	int totalSec = Conversion::ChangeSec(m_totalClearTime);
	int totalMilliSec = Conversion::ChangeMilliSec(m_totalClearTime);
	DrawFormatString(500, 550, 0x000000, "TOTAL TIME %02d:%02d:%03d", totalMin, totalSec, totalMilliSec);

	DrawString(1300, 550, "ランキング", 0x000000);
	DrawString(1300, 600, "1位 00:00:00", 0x000000);
	DrawString(1300, 650, "2位 00:00:00", 0x000000);
	DrawString(1300, 700, "3位 00:00:00", 0x000000);
	DrawString(1300, 750, "4位 00:00:00", 0x000000);
	DrawString(1300, 800, "5位 00:00:00", 0x000000);
	DrawString(1600, 1000, "ステージ選択にもどる", 0x000000);
#endif
}
