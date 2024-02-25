#pragma once
#include "Vec2.h"

/// <summary>
/// ��������N���X
/// </summary>
class SceneOption
{
public:
	SceneOption();
	~SceneOption();

	void Init();
	void Update();
	void Draw();

	// �V�[���J�ڃt���O
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// �V�[���J�ڂ̃t���O true:�V�[���Ɉړ�
	bool m_isSceneTitle;
	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;

	// ��������摜
	int m_exHandle;
};

