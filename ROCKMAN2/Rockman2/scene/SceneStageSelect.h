#pragma once
#include "Vec2.h"

/// <summary>
/// ステージ選択クラス
/// </summary>
class SceneStageSelect
{
public:
	SceneStageSelect();
	~SceneStageSelect();

	void Init();
	void Update();
	void Draw();
	void End();

	// シーンを終了させるか
	bool IsSceneStage1() const { return m_isSceneStage1; }
	bool IsSceneStage2() const { return m_isSceneStage2; }
	bool IsSceneStage3() const { return m_isSceneStage3; }
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// 選択項目
	enum Select
	{
		kStage1,	// ステージ1
		kStage2,	// ステージ2
		kStage3,	// ステージ3
		kBackTitle,	// タイトルに戻る
		kSelectNum	// 項目数
	};

	// 現在の選択状態
	int m_select;

private:
	// シーン選択のフラグ true:シーンに移動
	bool m_isSceneStage1;
	bool m_isSceneStage2;
	bool m_isSceneStage3;
	bool m_isSceneTitle;
	// 選択カーソルの表示位置
	Vec2 m_selectPos;
	// フェードイン、アウト
	int m_fadeAlpha;

	// 画像
	int m_selectHandle;			// 選択カーソル
	int m_charHandle;			// 文字
	int m_selectCharHandle;		// ステージ選択の文字
	int m_bgHandle;				// 背景

	// 音
	int m_bgm;					// BGM
	int m_selectSE;				// 選択時のSE
};

