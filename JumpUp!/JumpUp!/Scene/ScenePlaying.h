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
	void UpdateSelect(Input& input); // �I����Ԃ��X�V
	void DrawOption();				 // ���������\��
	void DrawPause();				 // �|�[�Y��ʂ�\��

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
	int m_select;	// ���݂̑I�����
	bool m_isPause;	// �|�[�Y��ʂ��J���Ă��邩(true:�J���Ă���)

	float m_time;		// �o�ߎ���

	float m_frameAnimTime;	// �g�̃A�j���[�V��������
	int m_frameHandle;		// �|�[�Y��ʂ̘g�̉摜
	int m_pauseBackHandle;	// �|�[�Y��ʂ̔w�i�摜

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
