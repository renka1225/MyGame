#pragma once
#include "SceneBase.h"

/// <summary>
/// �Q�[���I�[�o�[�V�[��
/// </summary>
class SceneGameover : public SceneBase
{
public:
	SceneGameover();
	virtual ~SceneGameover();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSelect(Input& input);	// �I����Ԃ̍X�V

private:
	// �I������
	enum Select
	{
		kRetry,			// ���g���C
		kStageSelect,	// �X�e�[�W�I��
		kTitle,			// �^�C�g��
		kSelectNum,		// �I��
	};

	int m_textHandle;	// �e�L�X�g�̉摜
	int m_cursorHandle;	// �J�[�\���̉摜
};

