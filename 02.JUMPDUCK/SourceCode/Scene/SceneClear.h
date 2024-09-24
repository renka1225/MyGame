#pragma once
#include "SceneBase.h"

/// <summary>
/// クリアシーン
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear();
	virtual ~SceneClear();

	virtual void Init() {};
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_textFrame;	// テキスト表示時間
	int m_fadeAlpha;	// フェードのα値

	int m_clearText;	// CLEARの文字

	// 選択項目
	enum Select
	{
		kStart,		// スタート
		kTitle,		// タイトルに戻る
		kSelectNum	// 項目数
	};
	int m_select;	// 現在の選択状態

private:	// 定数
	static constexpr int kClearTextPosX = 500;		// CLEAR表示位置X
	static constexpr int kClearTextPosY = 180;		// CLEAR表示位置Y
	static constexpr int kCursorPosX = 600;			// カーソル表示位置
	static constexpr int kTextPosX = 750;			// テキスト表示位置X
	static constexpr int kTextPosY = 700;			// テキスト表示位置Y
	static constexpr int kText2PosX = 720;			// テキスト2表示位置X
	static constexpr int kText2PosY = 850;			// テキスト2表示位置Y
	static constexpr int kTextFrame = 30;			// テキスト表示フレーム

	// フェード
	static constexpr int kMaxFade = 255;			// フェードα最大値
	static constexpr int kStartFadeAlpha = 150;		// スタート時のフェードα値
	static constexpr int kFadeFrame = 8;			// フェード変化量
};