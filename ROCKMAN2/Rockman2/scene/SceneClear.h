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

private:
	// 選択項目
	enum Select
	{
		kSelectStage, // ステージ選択
		kTitle,		  // タイトル
		kSelectNum	// 項目数
	};

	// 現在の選択状態
	int m_select;

private:
	// シーン終了のフラグ true:終了
	bool m_isSceneEnd;

	// 選択中の四角の表示位置
	Vec2 m_selectPos;
};

