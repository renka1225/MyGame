#pragma once
#include "Vec2.h"

/// <summary>
/// �Q�[���I�[�o�[�̃N���X
/// </summary>
class SceneGameOver
{
public:
	SceneGameOver();
	virtual ~SceneGameOver();

	void Init();
	void Update();
	void Draw();
	void DrawBg();

	// �V�[�����I�������邩
	bool IsSeneRetry() const { return m_isSceneRetry; }
	bool IsSceneSelect() const { return m_isSceneSelect; }
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// �I������
	enum Select
	{
		kRetry,		  // ���g���C 
		kSelect,	  // �X�e�[�W�I��
		kTitle,		  // �^�C�g��
		kSelectNum	  // ���ڐ�
	};

	// ���݂̑I�����
	int m_select;
	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;

private:
	// �V�[���I���̃t���O true:�V�[���Ɉړ�
	bool m_isSceneRetry;	// ���g���C
	bool m_isSceneSelect;	// �X�e�[�W�I��
	bool m_isSceneTitle;	// �^�C�g�� 

	// �I���J�[�\���̕\���ʒu
	Vec2 m_selectPos;
	// �w�i�̈ړ���
	float m_bgMove;

	// �摜
	int m_bgHandle;			// �w�i
	int m_bg2Handle;		// �w�i
	int m_bg3Handle;		// �w�i
	int m_gameoverHandle;	// �Q�[���I�[�o�[�̕���
	int m_charHandle;		// ����
	int m_selectHandle;		// �I���J�[�\��

	// ��
	int m_bgm;				// BGM
	int m_selectSE;			// �I������SE
	int m_cursorSE;			// �J�[�\���ړ�����SE

	// �摜�T�C�Y
	struct Size
	{
		int width;
		int height;
	};
};