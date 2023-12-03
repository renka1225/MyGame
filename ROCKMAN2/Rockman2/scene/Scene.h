#pragma once

class Pad;
class SceneManager;

/// <summary>
/// �V�[�����N���X
/// </summary>
class Scene
{
protected:
	SceneManager& m_manager; // �V�[���Ǘ��N���X�̎Q��

public:
	// ��������SceneManager�̎Q�Ƃ��󂯎��
	Scene(SceneManager& manager);

	// �V�[���̍X�V
	virtual void Update(Pad& pad) = 0;

	// �V�[���̕`��
	virtual void Draw() = 0;
};

