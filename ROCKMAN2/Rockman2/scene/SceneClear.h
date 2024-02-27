#pragma once
#include "Vec2.h"

/// <summary>
/// �N���A�V�[���N���X
/// </summary>
class SceneClear
{
public:
	SceneClear();
	virtual ~SceneClear();
	void Init();
	void Update();
	void Draw();
	// �w�i�`��
	void DrawBg();

	// �V�[�����I�������邩
	bool IsSceneStageSelect() const { return m_isSceneSelectStage; }
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// �I������
	enum Select
	{
		kSelectStage, // �X�e�[�W�I��
		kTitle,		  // �^�C�g��
		kSelectNum	  // ���ڐ�
	};

	// ���݂̑I�����
	int m_select;

private:
	// �V�[���I���̃t���O true:�V�[���Ɉړ�
	bool m_isSceneSelectStage;	// �X�e�[�W�I��
	bool m_isSceneTitle;		// �^�C�g��

	// �I���J�[�\���̕\���ʒu
	Vec2 m_selectPos;
	// �w�i�̈ړ���
	float m_bgMove;

	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;

	// �摜
	int m_bgHandle;		// �w�i
	int m_bg2Handle;	// �w�i
	int m_bg3Handle;	// �w�i
	int m_bg4Handle;	// �w�i
	int m_clearHandle;	// �N���A�̕���
	int m_charHandle;	// ����
	int m_selectHandle; // �I���J�[�\��
	
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