#pragma once
#include "SceneBase.h"
#include "DrawDebug.h"

class Player;
class Camera;
class Stage;
class DrawDebug;

/// <summary>
/// プレイ中のシーンクラス
/// </summary>
class ScenePlaying : public SceneBase
{
public:
	ScenePlaying();
	virtual ~ScenePlaying();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	virtual void FadeIn() override;			// フェードインの処理
	virtual void FadeOut() override;		// フェードアウトの処理
	void UpdateSelect(Input& input);		// 選択状態を更新
	void UpdateOperation(Input& input);		// 操作説明の表示状態を更新
	void UpdatePause(Input& input);			// ポーズ画面の表示状態を更新
	void ClearStaging();					// クリア時の演出
	void DrawOperation();					// 操作説明を表示
	void DrawPause();						// ポーズ画面を表示
	void DrawClearStaging();				// クリア時の演出描画

private:
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Stage> m_pStage;
	DrawDebug m_pDrawDebug;

	// ポーズ画面の選択項目の種類
	enum Select
	{
		kBack,		// ゲームに戻る
		kRetry,		// 最初からやり直す
		kTitle,		// タイトルに戻る
		kSelectNum	// 選択数
	};

	// ボタンの種類
	enum Button
	{
		kLSButton = 0,	// 左側のアナログスティック
		kAButton = 1,	// Aボタン
		kBButton = 6,	// Bボタン
		kLRButton = 2,	// LB,RBボタン
		kLineButton = 3,// 三本線ボタン
		kViewButton = 4,// ビューボタン 
		kButtonNum = 5	// ボタンの数
	};

	int m_select;			 // 現在の選択状態
	bool m_isOperation;		 // 操作説明画面を開いているか(true:開いている)
	bool m_isPause;			 // ポーズ画面を開いているか(true:開いている)

	int m_frame;				// 経過フレーム数
	float m_frameAnimTime;		// 枠のアニメーション時間
	float m_clearStagingTime;	// クリア演出時間

	int m_frameHandle;		// ポーズ画面の枠の画像
	int m_pauseBackHandle;	// ポーズ画面の背景画像
	int m_padHandle;		// コントローラーのボタンの画像

#ifdef _DEBUG
	// デバッグ状況
	enum class DebugState
	{
		Normal,	// 通常
		Pause	// ポーズ
	};
	DebugState m_debugState = DebugState::Normal;
#endif
};
