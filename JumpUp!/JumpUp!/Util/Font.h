#pragma once

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
		kSize32_4,
		kSize24_4,
		kSize16_4,
		kNormal,
		kNum,		// フォントの種類の数

		// 使うフォントを指定する
		// SceneTitle
		TitleMenu = kSize48_4,

		// ScenePlaying

		// SceneClear
	};

	// フォントのロード、アンロード
	void Load();
	void UnLoad();
}

