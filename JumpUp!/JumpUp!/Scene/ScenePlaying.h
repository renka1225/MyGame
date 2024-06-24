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
	void UpdateSelect(Input& input); // 選択状態を更新
	void DrawOption();				 // 操作説明を表示
	void DrawPause();				 // ポーズ画面を表示

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
	int m_select;	// 現在の選択状態
	bool m_isPause;	// ポーズ画面を開いているか(true:開いている)

	float m_time;		// 経過時間

	float m_frameAnimTime;	// 枠のアニメーション時間
	int m_frameHandle;		// ポーズ画面の枠の画像
	int m_pauseBackHandle;	// ポーズ画面の背景画像

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
