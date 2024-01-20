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
		kSceneOption,
		kSceneStageSelect,
		kSceneMain,
		kSceneStage2,
		kSceneStage3,
		kSceneClear,
		kSceneGameOver
	};

	// ���ݐi�s���̃V�[��
	SceneSelect m_runScene;

private:
	// SceneManager�ŊǗ�����V�[��
	SceneTitle* m_pTitle;
	SceneOption* m_pOption;
	SceneStageSelect* m_pStageSelect;
	SceneMain* m_pMain;
	SceneStage2* m_pStage2;
	SceneStage3* m_pStage3;
	SceneClear* m_pClear;
	SceneGameOver* m_pGameOver;
	
};

