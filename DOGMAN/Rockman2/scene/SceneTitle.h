#pragma once
#include "Vec2.h"

/// <summary>
///  タイトルシーンのクラス
/// </summary>
class SceneTitle
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	void Init();
	void Update();
	void Draw();
	void DrawBg();

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
	// 背景の移動量
	float m_bgMove;

	// 動画の再生時間
	int m_moveFrame;
	// OPを流すまでの時間
	int m_standFrame;
	// フェードイン、アウト
	int m_fadeAlpha;

	// 画像
	int m_logoHandle; 	// タイトルロゴ
	int m_selectHandle; // 選択カーソル
	int m_charHandle;	// 文字
	int m_bgHandle;		// 背景1
	int m_bg2Handle;	// 背景2
	int m_bg3Handle;	// 背景3
	int m_bg4Handle;	// 背景4

	// 音
	int m_bgm;			// BGM
	int m_selectSE;		// 選択時のSE
	int m_cursorSE;		// カーソル移動時のSE

	// 画像サイズ
	struct Size
	{
		int width;
		int height;
	};
};

