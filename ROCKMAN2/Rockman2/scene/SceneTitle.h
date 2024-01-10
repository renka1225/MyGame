#pragma once

/// <summary>
///  �^�C�g���V�[���̃N���X
/// </summary>
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void Update();
	void Draw();
	void End();

	// �V�[�����I�������邩
	bool IsSceneEnd() const { return m_isSceneEnd; }

private:
	// �V�[���I���̃t���O true:�I��
	bool m_isSceneEnd;

	// ���S
	int m_logoHandle;
};

