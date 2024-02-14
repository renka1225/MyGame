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
		kSceneOpening,
		kSceneTitle,
		kSceneOption,
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
	SceneOpening* m_pOpening;
	SceneTitle* m_pTitle;
	SceneOption* m_pOption;
	SceneStageSelect* m_pStageSelect;
	SceneTutorial* m_pTutorial;
	SceneStage1* m_pStage1;
	SceneClear* m_pClear;
	SceneGameOver* m_pGameOver;
};