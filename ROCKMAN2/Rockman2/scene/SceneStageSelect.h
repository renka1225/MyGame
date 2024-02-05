#pragma once
#include "Vec2.h"

/// <summary>
/// �X�e�[�W�I���N���X
/// </summary>
class SceneStageSelect
{
public:
	SceneStageSelect();
	~SceneStageSelect();

	void Init();
	void Update();
	void Draw();
	void End();
	// �w�i�\��
	void DrawBg();

	// �V�[�����I�������邩
	bool IsSceneStage1() const { return m_isSceneStage1; }
	bool IsSceneStage2() const { return m_isSceneStage2; }
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// �I������
	enum Select
	{
		kStage1,	// �X�e�[�W1
		kStage2,	// �X�e�[�W2
		kBackTitle,	// �^�C�g���ɖ߂�
		kSelectNum	// ���ڐ�
	};

	// ���݂̑I�����
	int m_select;

private:
	// �V�[���I���̃t���O true:�V�[���Ɉړ�
	bool m_isSceneStage1;
	bool m_isSceneStage2;
	bool m_isSceneStage3;
	bool m_isSceneTitle;

	// �I���J�[�\���̕\���ʒu
	Vec2 m_selectPos;
	// �w�i�̕\���ʒu
	Vec2 m_bgPos;
	// �w�i�̈ړ���
	float m_bgMove;

	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;

	// �摜
	int m_selectHandle;			// �I���J�[�\��
	int m_charHandle;			// ����
	int m_selectCharHandle;		// �X�e�[�W�I���̕���
	int m_bgHandle;				// �w�i
	int m_bg2Handle;			// �w�i
	int m_bg3Handle;			// �w�i
	int m_bg4Handle;			// �w�i

	// ��
	int m_bgm;					// BGM
	int m_selectSE;				// �I������SE
	int m_cursorSE;				// �J�[�\���ړ�����SE

	// �摜�T�C�Y
	struct Size
	{
		int width;
		int height;
	};
};

