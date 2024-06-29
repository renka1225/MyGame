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
		kSize32_4,
		kSize28_4,
		kSize24_4,
		kSize16_4,
		kNormal,
		kNum,		// フォントの種類の数

		// 使うフォントを指定する
		// SceneTitle
		kTitleMenu = kSize64_4,

		// ScenePlaying
		kOperation = kSize28_4,		// "操作説明"の文字サイズ
		kOperationMenu = kSize24_4,	// 操作説明部分の文字サイズ
		kPauseMenu = kSize42_4,
		kMenuTitle = kSize42_4,

		// SceneClear
		kClearMenu = kSize42_4,
	};

	// フォントのロード、アンロード
	void Load();
	void UnLoad();

	// フォントのハンドル
	// MEMO:externを使用して異なるソースファイルで変数を共有できるようにする
	extern std::vector<int> m_fontHandle;
}

