#include "DxLib.h"
#include "Vec2.h"
#include "UIProduction.h"
#include "Game.h"

// 定数
namespace
{
	/*試合開始時*/
	const char* const kFightTextPath = "data/UI/Fight!.png"; // "Fight"のテキスト画像位置
	const char* const kNumTextPath = "data/UI/number.png";	 // 数字の画像位置

	constexpr int kFightTextDispStart = 80;					// "Fight"のテキストを表示し始める時間
	const Vec2 kFightTextPos = { 960, 550 };				// "Fight"のテキスト位置
	constexpr float kFightTextScele = 0.6f;					// "Fight"のテキストサイズ
	const Vec2 kMatcheNumTextPos = { 850, 600 };			// 現在の試合数表示位置
	constexpr int kMatchNumTextWidth = 260;					// 1つ当たりのテキストの幅
	constexpr int kMatchNumTextInterval = 70;				// テキストの表示間隔
	constexpr int kTextAdj= 60;								// テキストの表示間隔調整
	constexpr float kMatchNumTextScele = 0.5f;				// 試合数のテキストサイズ
}


/// <summary>
/// コンストラクタ
/// </summary>
UIProduction::UIProduction()
{
	m_fightTextHandle = LoadGraph(kFightTextPath);
	m_numTextHandle = LoadGraph(kNumTextPath);
}


/// <summary>
/// デストラクタ
/// </summary>
UIProduction::~UIProduction()
{
	DeleteGraph(m_fightTextHandle);
	DeleteGraph(m_numTextHandle);
}


/// <summary>
/// 更新
/// </summary>
void UIProduction::Update()
{
}


/// <summary>
///  スタート時の演出を表示
/// </summary>
/// <param name="time">次の試合が始まるまでの時間</param>
/// <param name="matchNum">現在の試合数</param>
/// <param name="maxMatch">最大の試合数</param>
void UIProduction::DrawStartProduction(int time, int matchNum, int maxMatch)
{
	if (time > kFightTextDispStart)
	{
		int sizeW, sizeH;
		GetGraphSize(m_numTextHandle, &sizeW, &sizeH);
		// 現在の試合数を表示
		DrawRectRotaGraphF(kMatcheNumTextPos.x, kMatcheNumTextPos.y, 
			kMatchNumTextWidth * matchNum, 0, kMatchNumTextWidth, sizeH,
			kMatchNumTextScele, 0.0f, m_numTextHandle, true);
		// /表示
		DrawRectRotaGraphF(kMatcheNumTextPos.x + kMatchNumTextInterval, kMatcheNumTextPos.y, 
			sizeW - kMatchNumTextWidth, 0, kMatchNumTextWidth, sizeH,
			kMatchNumTextScele, 0.0f, m_numTextHandle, true);
		// 最大試合数を表示
		DrawRectRotaGraphF(kMatcheNumTextPos.x + kMatchNumTextInterval * 2 + kTextAdj, kMatcheNumTextPos.y, 
			kMatchNumTextWidth * (maxMatch - 1), 0, kMatchNumTextWidth, sizeH,
			kMatchNumTextScele, 0.0f, m_numTextHandle, true);
	}
	// "Fight!"の文字を表示
	else if (time < kFightTextDispStart && time > 0)
	{
		int sizeW, sizeH;
		GetGraphSize(m_fightTextHandle, &sizeW, &sizeH);
		DrawRectRotaGraphF(kFightTextPos.x, kFightTextPos.y, 0, 0, sizeW, sizeH, kFightTextScele, 0.0f, m_fightTextHandle, true);
	}
}