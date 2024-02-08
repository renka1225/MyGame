#pragma once

class SceneTitle;
class SceneStageSelect;
class SceneTutorial;
class SceneStage1;
class SceneClear;
class SceneGameOver;

/// <summary>
/// �V�[���̊Ǘ��N���X
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
	// �V�[���萔�̒�`
	enum SceneSelect
	{
		kSceneTitle,
		kSceneStageSelect,
		kSceneTutorial,
		kSceneStage1,
		kSceneClear,
		kSceneGameOver
	};

	// ���ݐi�s���̃V�[��
	SceneSelect m_runScene;

private:
	// SceneManager�ŊǗ�����V�[��
	SceneTitle* m_pTitle;
	SceneStageSelect* m_pStageSelect;
	SceneTutorial* m_pTutorial;
	SceneStage1* m_pStage1;
	SceneClear* m_pClear;
	SceneGameOver* m_pGameOver;
};