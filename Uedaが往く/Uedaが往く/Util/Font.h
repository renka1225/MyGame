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
		kSize48_4_EDGE,
		kSize42_4,
		kSize42_4_EDGE,
		kSize40_4,
		kSize36_4_EDGE,
		kSize28_4,
		kSize24_4,
		kSize24_4_EDGE,
		kSize16_4,
		kNormal,
		kNum,		// フォントの種類数

		// 使うフォントを指定する
		// SceneSelectStage
		kSelectStage = kSize48_4, // ステージ選択で使う文字サイズ
		// SceneOption
		kOption = kSize48_4,	  // オプションで使用する文字サイズ
		// ScenePause
		kPause = kSize42_4_EDGE,  // ポーズ画面で使用する文字サイズ
		// SceneClear
		kClearTime = kSize42_4,	  // 時間表示で使う文字サイズ
		// SceneGameover
		kGameover = kSize48_4,	  // ゲームオーバーで使う文字サイズ
		// ランキング
		kRanking = kSize42_4,
		kRankingText = kSize48_4_EDGE,
		//右下に表示するボタン表示の文字サイズ
		kButtonText = kSize42_4_EDGE,
		kClearButtonText = kSize36_4_EDGE,
		// 操作説明
		kOperation = kSize24_4_EDGE,
		// 必殺技
		kSpecialAttack = kSize36_4_EDGE,
	};

	// フォントのロード、アンロード
	void Load();
	void UnLoad();

	// フォントのハンドル
	// MEMO:externを使用して異なるソースファイルで変数を共有できるようにする
	extern std::vector<int> m_fontHandle;
}

