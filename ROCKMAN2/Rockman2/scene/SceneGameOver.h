#pragma once

/// <summary>
/// �Q�[���I�[�o�[�̃N���X
/// </summary>
class SceneGameOver
{
public:
	SceneGameOver();
	~SceneGameOver();

	void Init();
	void Update();
	void Draw();
	void End();

	// �V�[�����I�������邩
	bool IsSceneEnd() const { return m_isSceneEnd; }

private:
	// �V�[�����I��������t���O true:�I��
	bool m_isSceneEnd;
};

