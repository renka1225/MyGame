#pragma once

/// <summary>
/// �I�[�v�j���O�Đ��N���X
/// </summary>
class SceneOpening
{
public:
	SceneOpening();
	~SceneOpening();
	void Init();
	void Update();

	// �V�[���J�ڂ̃t���O
	bool IsSceneStart() const { return m_isSceneStart; }

private:
	// �V�[���I���̃t���O true:�V�[���Ɉړ�
	bool m_isSceneStart;

	// ����Đ�����
	int m_moveFrame;

	// ����t�@�C��
	int m_opMove;
};

