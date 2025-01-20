#pragma once
#include "SceneBase.h"

/// <summary>
/// �N���A��ʃN���X
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear();
	virtual ~SceneClear();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	void SetClearTime(int frame) { m_clearTime = frame; }

private:
	virtual void FadeIn() override;		// �t�F�[�h�C���̏���
	virtual void FadeOut() override;	// �t�F�[�h�A�E�g�̏���
	void UpdateSelect(Input& input);	// �I����Ԃ��X�V

private:
	// �I�����ڂ̎��
	enum Select
	{
		kStart,		// �ăv���C
		kTitle,		// �^�C�g���ɖ߂�
		kSelectNum	// �I��
	};
	int m_select;			// ���݂̑I�����

	int m_clearTime;		// �N���A����
	float m_frameAnimTime;	// �g�̃A�j���[�V��������

	int m_clearHandle;		// �N���A�̕����̉摜
	int m_frameHandle;		// �g�̉摜
};

