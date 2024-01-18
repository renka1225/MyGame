#pragma once
#include "Vec2.h"

/// <summary>
/// �I�v�V�����N���X
/// </summary>
class SceneOption
{
public:
	SceneOption();
	~SceneOption();

	void Init();
	void Update();
	void Draw();
	void End();

	// �V�[���J�ڃt���O
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// �I������
	enum Select
	{
		kBackTitle,	// �^�C�g���ɖ߂�
		kSelectNum	// ���ڐ�
	};

	// ���݂̑I�����
	int m_select;

private:
	// �V�[���J�ڂ̃t���O true:�V�[���Ɉړ�
	bool m_isSceneTitle;
	// �I���J�[�\���̕\���ʒu
	Vec2 m_selectPos;
	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;

	// �摜
	int m_selectHandle; // �I���J�[�\��
	int m_charHandle;	// ����
};

