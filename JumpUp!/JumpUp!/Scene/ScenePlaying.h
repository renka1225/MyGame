#pragma once
#include "SceneBase.h"
#include "DrawDebug.h"

class Player;
class Camera;
class Stage;
class DrawDebug;

/// <summary>
/// �v���C���̃V�[���N���X
/// </summary>
class ScenePlaying : public SceneBase
{
public:
	ScenePlaying();
	virtual ~ScenePlaying();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	virtual void FadeIn() override;			// �t�F�[�h�C���̏���
	virtual void FadeOut() override;		// �t�F�[�h�A�E�g�̏���
	void UpdateSelect(Input& input);		// �I����Ԃ��X�V
	void UpdateOperation(Input& input);		// ��������̕\����Ԃ��X�V
	void UpdatePause(Input& input);			// �|�[�Y��ʂ̕\����Ԃ��X�V
	void ClearStaging();					// �N���A���̉��o
	void DrawOperation();					// ���������\��
	void DrawPause();						// �|�[�Y��ʂ�\��
	void DrawClearStaging();				// �N���A���̉��o�`��

private:
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Stage> m_pStage;
	DrawDebug m_pDrawDebug;

	// �|�[�Y��ʂ̑I�����ڂ̎��
	enum Select
	{
		kBack,		// �Q�[���ɖ߂�
		kRetry,		// �ŏ������蒼��
		kTitle,		// �^�C�g���ɖ߂�
		kSelectNum	// �I��
	};

	// �{�^���̎��
	enum Button
	{
		kLSButton = 0,	// �����̃A�i���O�X�e�B�b�N
		kAButton = 1,	// A�{�^��
		kBButton = 6,	// B�{�^��
		kLRButton = 2,	// LB,RB�{�^��
		kLineButton = 3,// �O�{���{�^��
		kViewButton = 4,// �r���[�{�^�� 
		kButtonNum = 5	// �{�^���̐�
	};

	int m_select;			 // ���݂̑I�����
	bool m_isOperation;		 // ���������ʂ��J���Ă��邩(true:�J���Ă���)
	bool m_isPause;			 // �|�[�Y��ʂ��J���Ă��邩(true:�J���Ă���)

	int m_frame;				// �o�߃t���[����
	float m_frameAnimTime;		// �g�̃A�j���[�V��������
	float m_clearStagingTime;	// �N���A���o����

	int m_frameHandle;		// �|�[�Y��ʂ̘g�̉摜
	int m_pauseBackHandle;	// �|�[�Y��ʂ̔w�i�摜
	int m_padHandle;		// �R���g���[���[�̃{�^���̉摜

#ifdef _DEBUG
	// �f�o�b�O��
	enum class DebugState
	{
		Normal,	// �ʏ�
		Pause	// �|�[�Y
	};
	DebugState m_debugState = DebugState::Normal;
#endif
};
