#pragma once

class SceneTitle;
class SceneOption;
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
	void End();
	void Update();
	void Draw();

private:
	// �V�[���萔�̒�`
	enum SceneSelect
	{
		kSceneTitle,
		kSceneStage1,
		kSceneClear,
		kSceneGameOver
	};

	// ���ݐi�s���̃V�[��
	SceneSelect m_runScene;

private:
	// SceneManager�ŊǗ�����V�[��
	SceneTitle* m_pTitle;
	SceneStage1* m_pStage1;
	SceneClear* m_pClear;
	SceneGameOver* m_pGameOver;
};

