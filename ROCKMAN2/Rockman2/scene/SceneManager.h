#pragma once

class SceneTitle;
class SceneOption;
class SceneStageSelect;
class SceneMain;
class SceneStage2;
class SceneClear;
class SceneGameOver;

/// <summary>
/// シーンの管理クラス
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void End();
	void Update();
	void Draw();

private:
	// シーン定数の定義
	enum SceneSelect
	{
		kSceneTitle,
		kSceneStageSelect,
		kSceneMain,
		kSceneStage2,
		kSceneClear,
		kSceneGameOver
	};

	// 現在進行中のシーン
	SceneSelect m_runScene;

private:
	// SceneManagerで管理するシーン
	SceneTitle* m_pTitle;
	SceneStageSelect* m_pStageSelect;
	SceneMain* m_pMain;
	SceneStage2* m_pStage2;
	SceneClear* m_pClear;
	SceneGameOver* m_pGameOver;
};

