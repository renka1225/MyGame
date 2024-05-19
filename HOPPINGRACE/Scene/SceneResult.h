#pragma once
#include "SceneBase.h"

/// <summary>
/// 結果表示画面
/// </summary>
class SceneResult : public SceneBase
{
public:
	SceneResult();
	virtual ~SceneResult();

	virtual void Init(std::shared_ptr<ManagerResult> pResult);
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void DrawRanking();

private:
	int m_rankingTextHandle;	// ランキングのテキスト画像

private:	// 定数
	static constexpr int kButtonPosX = 70;			// ボタン画像表示位置X
	static constexpr int kButtonPosY = 645;			// ボタン画像表示位置Y
	static constexpr int kButtonSize = 16;			// ボタン画像切り出しサイズ
	static constexpr float kButtonScale = 3.0f;		// ボタン画像拡大率
	static constexpr int kRankingTextPosX = 340;	// ランキングの文字表示位置X
	static constexpr int kRankingTextPosY = 100;	// ランキングの文字表示位置Y
	static constexpr int kTextPosX = 87;			// テキスト表示位置X
	static constexpr int kTextPosY = 630;			// テキスト表示位置Y

	static constexpr int kRankPosX = 370;			// 1位～5位表示位置X
	static constexpr int kRank2PosX = 680;			// 6位～10位表示位置X
	static constexpr int kRankPosY = 280;			// 順位表示位置Y
	static constexpr int kTimePosX = 480;			// 1位～5位タイム表示位置X
	static constexpr int kTime2PosX = 790;			// 6位～10位タイム表示位置X
	static constexpr int kTimePosY = 285;			// タイム表示位置Y
	static constexpr int kIntervalY = 70;			// 順位表示間隔
	static constexpr int kDisplayRanking = 10;		// 表示する順位数

	static constexpr int kStartFadeAlpha = 255;		// スタート時のフェードα値
	static constexpr int kSoundPal = 4;				// BGMのフェード量
	static constexpr int kMaxSoundPal = 160;		// BGMの最大音量
};