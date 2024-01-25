#pragma once
#include "Vec2.h"

/// <summary>
/// クリアシーンクラス
/// </summary>
class SceneClear
{
public:
	SceneClear();
	~SceneClear();
	void Init();
	void End();
	void Update();
	void Draw();

	// シーンを終了させるか
	bool IsSceneStageSelect() const { return m_isSceneSelectStage; }
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// 選択項目
	enum Select
	{
		kSelectStage, // ステージ選択
		kTitle,		  // タイトル
		kSelectNum	  // 項目数
	};

	// 現在の選択状態
	int m_select;

private:
	// シーン選択のフラグ true:シーンに移動
	bool m_isSceneSelectStage;
	bool m_isSceneTitle;

	// 選択カーソルの表示位置
	Vec2 m_selectPos;

	// 画像
	int m_bgHandle;		// 背景
	int m_clearHandle;	// クリアの文字
	int m_charHandle;	// 文字
	int m_selectHandle; // 選択カーソル
	
	// 音
	int m_selectSE;		// 選択時のSE
};