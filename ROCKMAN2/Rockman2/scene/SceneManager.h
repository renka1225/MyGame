#pragma once

class SceneTitle;
class SceneOption;
class SceneStageSelect;
class SceneMain;
class SceneStage2;
class SceneStage3;
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
		kSceneOption,
		kSceneStageSelect,
		kSceneMain,
		kSceneStage2,
		kSceneStage3,
		kSceneClear,
		kSceneGameOver
	};

	// 現在進行中のシーン
	SceneSelect m_runScene;

private:
	// SceneManagerで管理するシーン
	SceneTitle* m_pTitle;
	SceneOption* m_pOption;
	SceneStageSelect* m_pStageSelect;
	SceneMain* m_pMain;
	SceneStage2* m_pStage2;
	SceneStage3* m_pStage3;
	SceneClear* m_pClear;
	SceneGameOver* m_pGameOver;
	
};

