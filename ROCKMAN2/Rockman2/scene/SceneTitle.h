#pragma once
#include "Vec2.h"

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

	// �V�[���J�ڂ̃t���O
	bool IsSceneStart() const { return m_isSceneStart; }
	bool IsSceneOption() const { return m_isSceneOption; }

private:
	// �I������
	enum Select
	{
		kStart,	 // �X�^�[�g
		kOption, // �I�v�V����
		kExit,	 // �Q�[���I��
		kSelectNum // ���ڐ�
	};

	// ���݂̑I�����
	int m_select;

private:
	// �V�[���I���̃t���O true:�V�[���Ɉړ�
	bool m_isSceneStart;
	bool m_isSceneOption;

	// �I���J�[�\���̕\���ʒu
	Vec2 m_selectPos;
	// �w�i�̕\���ʒu
	Vec2 m_bgPos;
	// �w�i�̈ړ���
	Vec2 m_bgMove;

	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;
	// �摜
	int m_logoHandle; 	// �^�C�g�����S
	int m_selectHandle; // �I���J�[�\��
	int m_charHandle;	// ����
	int m_bgHandle;			// �w�i
};

