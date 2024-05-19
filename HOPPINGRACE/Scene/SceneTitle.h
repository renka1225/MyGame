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

	virtual void Init(std::shared_ptr<ManagerResult> pResult);
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSelect(Input& input);	// 選択状態の更新
	void DrawSelect();					// 選択項目を表示

private:
	// 選択項目
	enum Select
	{
		kStart,		// スタート
		kResult,	// スコア確認
		kEnd,		// ゲーム終了
		kSelectNum	// 選択数
	};

	int m_select;		// 現在の選択状態

	int m_playMovie;	// プレイ動画
	int m_titleLogo;	// タイトルロゴ

private: // 定数
	static constexpr int kTitleLogoPosX = 350;	// タイトル表示位置X
	static constexpr int kTitleLogoPosY = 100;	// タイトル表示位置Y

	static constexpr int kNowSelectPosX = 534;	// 選択中表示位置X
	static constexpr int kNowSelectPosY = 445;	// 選択中表示位置Y
	static constexpr int kNowSelectWidth = 210;	// 選択中表示の横幅
	static constexpr int kNowSelectHeight = 61;	// 選択中表示の縦幅
	static constexpr int kFramePosX = 530;		// 枠表示位置X
	static constexpr int kFramePosY = 440;		// 枠表示位置Y
	static constexpr int kSelectMove = 80;		// 選択表示の移動量

	static constexpr int kStartTextPosX = 580;	// スタート表示位置X
	static constexpr int kStartTextPosY = 460;	// スタート表示位置Y
	static constexpr int kResultTextPosX = 560;	// リザルト表示位置X
	static constexpr int kResultTextPosY = 540;	// リザルト表示位置Y
	static constexpr int kEndTextPosX = 600;	// ゲーム終了表示位置X
	static constexpr int kEndTextPosY = 620;	// ゲーム終了表示位置Y

	// クレジット表記位置
	static constexpr int kCreditPosX = 900;		// クレジット表記位置X
	static constexpr int kCreditPosY = 670;		// クレジット表記位置Y
	static constexpr int kCreditPos2Y = 690;	// クレジット表記位置Y

	static constexpr int kStartFadeAlpha = 200;		// スタート時のフェードα値
	static constexpr int kSoundPal = 3;				// BGMのフェード量
	static constexpr int kMaxSoundPal = 160;		// BGMの最大音量
};