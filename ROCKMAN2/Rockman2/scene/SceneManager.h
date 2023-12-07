#pragma once

class SceneTitle;
class SceneMain;
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
	// ステージ定数の定義
	enum SceneKind
	{
		kSceneKindTitle,
		kSceneKindMain,
		kSceneKindGameOver
	};

	// 現在進行中のシーン
	SceneKind m_runScene;

private:
	// SceneManagerで管理するシーン
	SceneTitle* m_pTitle;
	SceneMain* m_pMain;
	SceneGameOver* m_pGameOver;
	
};

