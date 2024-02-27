#pragma once
#include "Vec2.h"

/// <summary>
/// ステージ選択クラス
/// </summary>
class SceneStageSelect
{
public:
	SceneStageSelect();
	virtual ~SceneStageSelect();

	void Init();
	void Update();
	void Draw();
	// 背景表示
	void DrawBg();

	// シーンを終了させるか
	bool IsSceneTutorial() const { return  m_isSceneTutorial; }
	bool IsSceneStage1() const { return m_isSceneStage1; }
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// 選択項目
	enum Select
	{
		kStageTutorial,	// チュートリアルステージ
		kStage1,		// ステージ1
		kBackTitle,		// タイトルに戻る
		kSelectNum		// 項目数
	};

	// 現在の選択状態
	int m_select;

private:
	// シーン選択のフラグ true:シーンに移動
	bool m_isSceneTutorial;
	bool m_isSceneStage1;
	bool m_isSceneTitle;

	// 選択カーソルの表示位置
	Vec2 m_selectPos;
	// 背景の表示位置
	Vec2 m_bgPos;
	// 背景の移動量
	float m_bgMove;

	// フェードイン、アウト
	int m_fadeAlpha;

	// 画像
	int m_selectHandle;			// 選択カーソル
	int m_charHandle;			// 文字
	int m_selectCharHandle;		// ステージ選択の文字
	int m_bgHandle;				// 背景
	int m_bg2Handle;			// 背景
	int m_bg3Handle;			// 背景
	int m_bg4Handle;			// 背景

	// 音
	int m_bgm;					// BGM
	int m_selectSE;				// 選択時のSE
	int m_cursorSE;				// カーソル移動時のSE

	// 画像サイズ
	struct Size
	{
		int width;
		int height;
	};
};

