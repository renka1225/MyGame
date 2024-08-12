#pragma once
#include "SceneBase.h"

class SceneStageBase;

/// <summary>
/// �Q�[���I�[�o�[�V�[��
/// </summary>
class SceneGameover : public SceneBase
{
public:
	SceneGameover() {};
	SceneGameover(std::shared_ptr<SceneBase> pScene);
	virtual ~SceneGameover();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSelect(Input& input);	// �I����Ԃ̍X�V

private:
	std::shared_ptr<SceneBase> m_pPrevScene;	// �O�Ɏ��s���Ă����V�[��
	int m_textHandle;	// �e�L�X�g�̉摜
	int m_cursorHandle;	// �J�[�\���̉摜

	// �I������
	enum Select
	{
		kRetry,			// ���g���C
		kStageSelect,	// �X�e�[�W�I��
		kTitle,			// �^�C�g��
		kSelectNum,		// �I��
	};
};

