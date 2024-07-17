#pragma once
#include "SceneBase.h"

/// <summary>
/// �f�o�b�O�p�V�[��
/// </summary>
class SceneDebug : public SceneBase
{
public:
	SceneDebug();
	virtual ~SceneDebug() {};
	virtual void Init() {};
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSelect(Input& input);	// �I����Ԃ��X�V

private:
	// �V�[���̎��
	enum Select
	{
		kTitle,			// �^�C�g��
		kStageSelect,	// �X�e�[�W�I��
		kOption,		// �I�v�V����
		kStage1,		// �X�e�[�W1
		kStage2,		// �X�e�[�W2
		kSelectNum		// �V�[���̐�
	};

	int m_select;		// ���݂̑I�����
};

