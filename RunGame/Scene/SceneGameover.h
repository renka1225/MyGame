#pragma once
#include "SceneBase.h"

/// <summary>
/// ゲームオーバーシーン
/// </summary>
class SceneGameover : public SceneBase
{
public:
	SceneGameover();
	virtual ~SceneGameover() {};

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_textFrame;	// テキスト表示時間
	int m_fadeAlpha;	// フェードのα値

	// 選択項目
	enum Select
	{
		kStart,		// スタート
		kTitle,		// タイトルに戻る
		kSelectNum	// 項目数
	};
	int m_select;	// 現在の選択状態

private:	// 定数
	static constexpr int kTextPosX = 750;			// テキスト表示位置X
	static constexpr int kTextPosY = 700;			// テキスト表示位置Y
	static constexpr int kText2PosX = 720;			// テキスト2表示位置X
	static constexpr int kText2PosY = 850;			// テキスト2表示位置Y

	// フェード
	static constexpr int kMaxFade = 255;			// フェードα最大値
	static constexpr int kStartFadeAlpha = 150;		// スタート時のフェードα値
	static constexpr int kFadeFrame = 8;			// フェード変化量
};