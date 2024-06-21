#pragma once
#include "SceneBase.h"

/// <summary>
/// �^�C�g����ʃN���X
/// </summary>
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSelect(Input& input);	// �I����Ԃ��X�V

private:
	// �I�����ڂ̎��
	enum Select
	{
		kStart,		// �Q�[���X�^�[�g
		kEnd,		// �Q�[���I��
		kSelectNum	// �I��
	};

	int m_select;	// ���݂̑I�����

	int m_titleHandle;		 // �^�C�g�����S�̉摜
	int m_frameHandle;		 // �g�̉摜
	int m_selectFrameHandle; // ���ݑI�𒆂̘g�̉摜
};