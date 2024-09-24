#pragma once
#include "SceneBase.h"


/// <summary>
/// タイトル画面
/// </summary>
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init() {};
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_textFrame;	// テキスト表示時間
	int m_fadeAlpha;	// フェードのα値

	int m_titleLogo;	// タイトルロゴの画像

	// 選択項目
	enum Select
	{
		kStart,		// スタート
		kEnd,		// ゲーム終了
		kSelectNum	// 項目数
	};
	int m_select;	// 現在の選択状態

private:	// 定数
	static constexpr int kLogoPosX = 610;		// タイトルロゴ表示位置X
	static constexpr int kLogoPosY = 100;		// タイトルロゴ表示位置Y
	static constexpr int kCursorPosX = 700;		// カーソル表示位置X
	static constexpr int kTextPosX = 840;		// テキスト表示位置X
	static constexpr int kTextPosY = 700;		// テキスト表示位置Y
	static constexpr int kText2PosX = 870;		// テキスト2表示位置X
	static constexpr int kText2PosY = 850;		// テキスト2表示位置Y
	static constexpr int kTextFrame = 30;		// テキスト表示フレーム
	static constexpr int kCreditTextPosX = 1500;// クレジット表示位置X
	static constexpr int kCreditTextPosY = 950;	// クレジット表示位置Y

	static constexpr int kMaxFade = 255;		// フェードα最大値
	static constexpr int kFadeFrame = 8;		// フェード変化量
};