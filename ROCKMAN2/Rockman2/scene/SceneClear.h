#pragma once
#include "Vec2.h"

/// <summary>
/// �N���A�V�[���N���X
/// </summary>
class SceneClear
{
public:
	SceneClear();
	~SceneClear();
	void Init();
	void End();
	void Update();
	void Draw();

	// �V�[�����I�������邩
	bool IsSceneStageSelect() const { return m_isSceneSelectStage; }
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// �I������
	enum Select
	{
		kSelectStage, // �X�e�[�W�I��S
		kTitle,		  // �^�C�g��
		kSelectNum	  // ���ڐ�
	};

	// ���݂̑I�����
	int m_select;

private:
	// �V�[���I���̃t���O true:�V�[���Ɉړ�
	bool m_isSceneSelectStage;
	bool m_isSceneTitle;

	// �I���J�[�\���̕\���ʒu
	Vec2 m_selectPos;

	// �摜
	int m_clearHandle;	// �N���A�̕���
	int m_charHandle;	// ����
	int m_selectHandle; // �I���J�[�\��
};