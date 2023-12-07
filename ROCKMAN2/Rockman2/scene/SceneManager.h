#pragma once

class SceneTitle;
class SceneMain;
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
	// �X�e�[�W�萔�̒�`
	enum SceneKind
	{
		kSceneKindTitle,
		kSceneKindMain,
		kSceneKindGameOver
	};

	// ���ݐi�s���̃V�[��
	SceneKind m_runScene;

private:
	// SceneManager�ŊǗ�����V�[��
	SceneTitle* m_pTitle;
	SceneMain* m_pMain;
	SceneGameOver* m_pGameOver;
	
};

