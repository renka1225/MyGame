#pragma once
#include "Vec2.h"

class FontManager;
class Player;

/// <summary>
/// ポーズシーンクラス
/// </summary>
class ScenePause
{
public:
	ScenePause(Player* pPlayer);
	virtual ~ScenePause();
	void Init();
	void Update();
	void Draw();
	// 武器切り替えの更新
	void UpdateChangeShot();
	// ポーズ画面選択状態更新
	void UpdatePause();

	// 武器切り替え画面が表示されているか取得
	bool IsSelectShotExist() const { return  m_isChangeMenuExist; }
	// ポーズ画面が表示されているか取得
	bool IsPause() const { return m_isPauseExist; }

	// ポーズ画面の選択状態を取得する
	bool IsSelectRetry() const { return m_isRetry; }
	bool IsSelectTitle() const { return m_isTitle; }

private:
	// 武器切り替え選択項目
	enum SelectShot
	{
		kBuster,// バスター
		kMetal, // メタル
		kFire,	// ファイアー
		kLine,	// 2号
		kFullRecovery,	// E缶
		kShotSelectNum // 項目数
	};

	// ポーズ画面選択項目
	enum Pause
	{
		kBack,	// ゲームに戻る
		kRetry,	// リトライ
		kTitle,	// タイトルに戻る
		kSelectNum // 項目数
	};

	// 現在の武器選択状態
	int m_shotSelect;
	// 現在のポーズ選択状態
	int m_pauseSelect;

private:
	// フォント管理
	FontManager* m_pFont;
	// プレイヤーのポインタ
	Player* m_pPlayer;

	// メニュー画面の高さ
	int m_menuHeight;
	// ポーズ画面の表示位置
	Vec2 m_menuPos;
	// 武器選択中カーソルの表示位置
	Vec2 m_selectShotPos;
	// ポーズ画面選択中のカーソル表示位置
	Vec2 m_selectPausePos;
	// 武器切り替え画面が表示されているか true:表示されている
	bool m_isChangeMenuExist;
	// ポーズ画面が表示されているか
	bool m_isPauseExist;

	// ポーズ画面の選択状態
	bool m_isRetry;	// リトライ
	bool m_isTitle;	// タイトルに戻る

	// 画像
	int m_menuBg;		// メニュー画面の背景
	int m_selectHandle; // 選択カーソルの画像

	// 音
	int m_menuSE;		// メニュー画面を開いた際のSE
	int m_selectSE;		// 選択時のSE
	int m_cursorSE;		// カーソル移動時のSE
};

