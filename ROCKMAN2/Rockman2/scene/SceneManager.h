#pragma once

class SceneTitle;
class SceneOption;
class SceneStageSelect;
class SceneMain;
class SceneStage2;
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
	void End();
	void Update();
	void Draw();

private:
	// �V�[���萔�̒�`
	enum SceneSelect
	{
		kSceneTitle,
		kSceneStageSelect,
		kSceneMain,
		kSceneStage2,
		kSceneClear,
		kSceneGameOver
	};

	// ���ݐi�s���̃V�[��
	SceneSelect m_runScene;

private:
	// SceneManager�ŊǗ�����V�[��
	SceneTitle* m_pTitle;
	SceneStageSelect* m_pStageSelect;
	SceneMain* m_pMain;
	SceneStage2* m_pStage2;
	SceneClear* m_pClear;
	SceneGameOver* m_pGameOver;
};

