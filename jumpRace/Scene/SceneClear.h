#pragma once
#include "SceneBase.h"

/// <summary>
/// クリア画面
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear(int time);
	virtual ~SceneClear() {};

	virtual void Init(std::shared_ptr<ManagerResult> pResult);
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSelect(Input& input);	// 選択状態の更新
	void DrawSelect();					// 選択項目表示
	void DrawResult();					// 結果表示

private:
	int m_clearTime;	// クリアタイム

	// 選択項目
	enum Select
	{
		kStart,		// スタート
		kTitle,		// タイトルに戻る
		kSelectNum	// 選択数
	};
	int m_select;	// 現在の選択状態

private: // 定数
	static constexpr int kClearTimePosX = 500;	// クリアタイム表示位置X
	static constexpr int kClearTimePosY = 100;	// クリアタイム表示位置Y
	static constexpr int kTimePosX = 560;		// 順位表示位置X
	static constexpr int kTimePosY = 180;		// 順位表示位置Y
	static constexpr int kIntervalY = 50;		// 順位表示間隔
	static constexpr int kDisplayRanking = 5;	// 表示する順位数

	static constexpr int kNowSelectPosX = 534;	// 選択中表示位置X
	static constexpr int kNowSelectPosY = 485;	// 選択中表示位置Y
	static constexpr int kNowSelectWidth = 210;	// 選択中表示の横幅
	static constexpr int kNowSelectHeight = 61;	// 選択中表示の縦幅
	static constexpr int kFramePosX = 530;		// 枠表示位置X
	static constexpr int kFramePosY = 480;		// 枠表示位置Y
	static constexpr int kSelectMove = 100;		// 選択表示の移動量

	static constexpr int kStartTextPosX = 580;	// スタート表示位置X
	static constexpr int kStartTextPosY = 500;	// スタート表示位置Y
	static constexpr int kTitleTextPosX = 540;	// タイトルに戻る表示位置X
	static constexpr int kTitleTextPosY = 605;	// タイトルに戻る表示位置Y

	static constexpr int kStartFadeAlpha = 255;		// スタート時のフェードα値
};

