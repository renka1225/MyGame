#pragma once
#include <vector>

// フォント関連
namespace Font
{
	// フォントの種類
	enum class FontId
	{
		// フォントサイズ、太さ
		kSize96_4,
		kSize64_4,
		kSize48_4,
		kSize42_4,
		kSize40_4,
		kSize28_4,
		kSize24_4,
		kSize16_4,
		kNormal,
		kNum,		// フォントの種類数

		// 使うフォントを指定する
		// SceneSelectStage
		kSelectStage = kSize48_4, // ステージ選択で使う文字サイズ
		// SceneOption
		kOption = kSize48_4,	  // オプションで使用する文字サイズ
		// ScenePause
		kPause = kSize42_4,		  // ポーズ画面で使用する文字サイズ
		// SceneClear
		kClearTime = kSize42_4,	  // 時間表示で使う文字サイズ
		// SceneGameover
		kGameover = kSize48_4,	  // ゲームオーバーで使う文字サイズ
		// ランキング
		kRanking = kSize42_4,
		kRankingText = kSize48_4,
		//右下に表示するボタン表示の文字サイズ
		kButtonText = kSize42_4,
	};

	// フォントのロード、アンロード
	void Load();
	void UnLoad();

	// フォントのハンドル
	// MEMO:externを使用して異なるソースファイルで変数を共有できるようにする
	extern std::vector<int> m_fontHandle;
}

