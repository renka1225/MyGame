#pragma once
#include "Vec2.h"

/// <summary>
///  �^�C�g���V�[���̃N���X
/// </summary>
class SceneTitle
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	void Init();
	void Update();
	void Draw();
	void DrawBg();

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
	// �w�i�̈ړ���
	float m_bgMove;

	// ����̍Đ�����
	int m_moveFrame;
	// OP�𗬂��܂ł̎���
	int m_standFrame;
	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;

	// �摜
	int m_logoHandle; 	// �^�C�g�����S
	int m_selectHandle; // �I���J�[�\��
	int m_charHandle;	// ����
	int m_bgHandle;		// �w�i1
	int m_bg2Handle;	// �w�i2
	int m_bg3Handle;	// �w�i3
	int m_bg4Handle;	// �w�i4

	// ��
	int m_bgm;			// BGM
	int m_selectSE;		// �I������SE
	int m_cursorSE;		// �J�[�\���ړ�����SE

	// �摜�T�C�Y
	struct Size
	{
		int width;
		int height;
	};
};
