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
	void UpdateSelect(Input& input);
	void DrawPause(); // ポーズ画面を表示

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
