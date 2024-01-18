#pragma once
#include "Vec2.h"

/// <summary>
/// オプションクラス
/// </summary>
class SceneOption
{
public:
	SceneOption();
	~SceneOption();

	void Init();
	void Update();
	void Draw();
	void End();

	// シーン遷移フラグ
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// 選択項目
	enum Select
	{
		kBackTitle,	// タイトルに戻る
		kSelectNum	// 項目数
	};

	// 現在の選択状態
	int m_select;

private:
	// シーン遷移のフラグ true:シーンに移動
	bool m_isSceneTitle;
	// 選択カーソルの表示位置
	Vec2 m_selectPos;
	// フェードイン、アウト
	int m_fadeAlpha;

	// 画像
	int m_selectHandle; // 選択カーソル
	int m_charHandle;	// 文字
};

