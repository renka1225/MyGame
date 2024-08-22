#pragma once
#include "SceneBase.h"

/// <summary>
/// �I�v�V�������
/// </summary>
class SceneOption : public SceneBase
{
public:
	SceneOption() {};
	SceneOption(std::shared_ptr<SceneBase> pScene);
	virtual ~SceneOption();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSound(Input& input);		// �T�E���h�X�V
	//void UpdateKeyConfig(Input& input); // �L�[�X�V
	void DrawSound();					// �T�E���h�����\��
	void DrawCredit();					// �N���W�b�g�\�L
	void DrawKeyConfig();				// �L�[�R���t�B�O�����\��

private:
	std::shared_ptr<SceneBase> m_pPrevScene;	// �O�Ɏ��s���Ă����V�[��
	int m_afterSelect;							// �I����̏��
	bool m_isSound;								// �T�E���h���I�𒆂�(true:�I��)
	bool m_isCredit;							// �L�[�R���t�B�O���I�𒆂�(true:�I��)
	std::vector<int> m_handle;					// �T�E���h�o�[�Ɏg�p����摜

	// �I����
	enum Select
	{
		kSound,			// �T�E���h
		kCredit,		// �N���W�b�g�\�L
		kSelectNum		// �I��
	};

	// �T�E���h�I����
	enum SelectSound
	{
		kBGM,			// BGM
		kSE,			// SE
		kSelectSoundNum	// �I��
	};

	// �L�[�R���t�B�O�I����
	enum SelectKeyConfig
	{
		kXButton,		// X�{�^��
		kYButton,		// Y�{�^��
		kSelectKeyNum	// �I��
	};
};

