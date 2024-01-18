#pragma once
#include "Vec2.h"

/// <summary>
///  タイトルシーンのクラス
/// </summary>
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void Update();
	void Draw();
	void End();

	// シーン遷移のフラグ
	bool IsSceneStart() const { return m_isSceneStart; }
	bool IsSceneOption() const { return m_isSceneOption; }

private:
	// 選択項目
	enum Select
	{
		kStart,	 // スタート
		kOption, // オプション
		kExit,	 // ゲーム終了
		kSelectNum // 項目数
	};

	// 現在の選択状態
	int m_select;

private:
	// シーン選択のフラグ true:シーンに移動
	bool m_isSceneStart;
	bool m_isSceneOption;

	// 選択カーソルの表示位置
	Vec2 m_selectPos;
	// 背景の表示位置
	Vec2 m_bgPos;
	// 背景の移動量
	Vec2 m_bgMove;

	// フェードイン、アウト
	int m_fadeAlpha;
	// 画像
	int m_logoHandle; 	// タイトルロゴ
	int m_selectHandle; // 選択カーソル
	int m_charHandle;	// 文字
	int m_bg;			// 背景
};

