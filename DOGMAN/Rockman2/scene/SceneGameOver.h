#pragma once
#include "Vec2.h"

/// <summary>
/// ゲームオーバーのクラス
/// </summary>
class SceneGameOver
{
public:
	SceneGameOver();
	virtual ~SceneGameOver();

	void Init();
	void Update();
	void Draw();
	void DrawBg();

	// シーンを終了させるか
	bool IsSeneRetry() const { return m_isSceneRetry; }
	bool IsSceneSelect() const { return m_isSceneSelect; }
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// 選択項目
	enum Select
	{
		kRetry,		  // リトライ 
		kSelect,	  // ステージ選択
		kTitle,		  // タイトル
		kSelectNum	  // 項目数
	};

	// 現在の選択状態
	int m_select;
	// フェードイン、アウト
	int m_fadeAlpha;

private:
	// シーン選択のフラグ true:シーンに移動
	bool m_isSceneRetry;	// リトライ
	bool m_isSceneSelect;	// ステージ選択
	bool m_isSceneTitle;	// タイトル 

	// 選択カーソルの表示位置
	Vec2 m_selectPos;
	// 背景の移動量
	float m_bgMove;

	// 画像
	int m_bgHandle;			// 背景
	int m_bg2Handle;		// 背景
	int m_bg3Handle;		// 背景
	int m_gameoverHandle;	// ゲームオーバーの文字
	int m_charHandle;		// 文字
	int m_selectHandle;		// 選択カーソル

	// 音
	int m_bgm;				// BGM
	int m_selectSE;			// 選択時のSE
	int m_cursorSE;			// カーソル移動時のSE

	// 画像サイズ
	struct Size
	{
		int width;
		int height;
	};
};