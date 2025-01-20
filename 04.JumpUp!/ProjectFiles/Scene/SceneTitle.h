#pragma once
#include "SceneBase.h"

/// <summary>
/// �^�C�g�����
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
	virtual void FadeIn() override;		// �t�F�[�h�C���̏���
	virtual void FadeOut() override;	// �t�F�[�h�A�E�g�̏���
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

	float m_stageRotate;	// �X�e�[�W�̉�]��
	float m_frameAnimTime;	// �g�̃A�j���[�V��������

	int m_titleHandle;		 // �^�C�g�����S�̉摜
	int m_frameHandle;		 // �g�̉摜
	int m_stageHandle;		 // �X�e�[�W��3D���f��
};