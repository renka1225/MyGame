#pragma once

class SceneOpening;
class SceneTitle;
class SceneOption;
class SceneStageSelect;
class SceneTutorial;
class SceneStage1;
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
	void Update();
	void Draw();

private:
	// シーン定数の定義
	enum SceneSelect
	{
		kSceneOpening,
		kSceneTitle,
		kSceneOption,
		kSceneStageSelect,
		kSceneTutorial,
		kSceneStage1,
		kSceneClear,
		kSceneGameOver
	};

	// 現在進行中のシーン
	SceneSelect m_runScene;

private:
	// SceneManagerで管理するシーン
	SceneOpening* m_pOpening;
	SceneTitle* m_pTitle;
	SceneOption* m_pOption;
	SceneStageSelect* m_pStageSelect;
	SceneTutorial* m_pTutorial;
	SceneStage1* m_pStage1;
	SceneClear* m_pClear;
	SceneGameOver* m_pGameOver;
};