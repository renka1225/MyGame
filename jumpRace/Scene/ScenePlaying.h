#pragma once
#include "SceneBase.h"
#include <memory>

class ManagerModel;
class ManagerLight;
class Player;
class Camera;
class Background;

/// <summary>
/// �v���C���
/// </summary>
class ScenePlaying : public SceneBase
{
public:
	ScenePlaying();
	virtual ~ScenePlaying();

	virtual void Init(std::shared_ptr<ManagerResult> pResult);
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void StartStaging();				// �X�^�[�g���o�̕\��
	void ClearStaging();				// �N���A���o�̕\��
	void UpdateCommand(Input& input);	// ���̓R�}���h�̍X�V
	void DrawCommand();					// ���̓R�}���h�̕\��

private:
	// �|�C���^
	std::shared_ptr<ManagerModel> m_pModel;		// 3D���f��
	std::shared_ptr<ManagerLight> m_pLight;		// ���C�g
	std::shared_ptr<Player> m_pPlayer;			// �v���C���[
	std::shared_ptr<Camera> m_pCamera;			// �J����
	std::shared_ptr<Background> m_pBackground;	// �w�i

	// ���̓R�}���h�̎��
	enum Command
	{
		A,
		B,
		X,
		Y
	};
	int m_nowCommand;		// ���݂̃R�}���h

	int m_startTime;		// �X�^�[�g���̉��o����
	int m_clearStagingTime;	// �N���A���̉��o����
	int m_time;				// �o�ߎ���
	int m_stopTime;			// �����Ȃ�����
	int m_pushCount;		// �{�^������������

	int m_startCount3;		// �X�^�[�g�J�E���g��UI
	int m_startCount2;		// �X�^�[�g�J�E���g��UI
	int m_startCount1;		// �X�^�[�g�J�E���g��UI

private:	// �萔
	static constexpr int kMaxPush = 30;				// 30��{�^�����͂��s��

	// �X�^�[�g���o
	static constexpr int kStartTime = 240;			// �X�^�[�g���̉��o����
	static constexpr int kStartCount1 = 180;		// 1�J�E���g��
	static constexpr int kStartCount2 = 120;		// 2�J�E���g��
	static constexpr int kStartCount3 = 60;			// 3�J�E���g��
	static constexpr int kStartCount4 = 0;			// startSE��炷
	static constexpr int kStartCountPosX = 600;		// �J�E���g�\���ʒuX
	static constexpr int kStartCountPosY = 250;		// �J�E���g�\���ʒuY
	static constexpr int kClearStagingTime = 300;	// �N���A���̉��o����

	static constexpr int kCommandSize = 16;			// ���̓R�}���h�̃T�C�Y
	static constexpr float kCommandScale = 4.0f;	// ���̓R�}���h�̊g�嗦
	static constexpr int kCommandPosX = 645;		// ���̓R�}���h�\���ʒuX
	static constexpr int kCommandPosY = 250;		// ���̓R�}���h�\���ʒuY
	static constexpr int kTimePosX = 560;			// �^�C���\���ʒuX
	static constexpr int kTimePosY = 110;			// �^�C���\���ʒuY
	static constexpr int kTimeEdgePosX = 558;		// �^�C���̃e�L�X�g�����ʒuX
	static constexpr int kTimeEdgePosY = 111;		// �^�C���̃e�L�X�g�����ʒuY

	static constexpr int kStopTime = 30;			// �~�X���ɓ����Ȃ��Ȃ鎞��
	static constexpr int kNextCommandTime = 10;		// ���̃R�}���h��\������܂ł̎���

	static constexpr int kStartFadeAlpha = 255;		// �X�^�[�g���̃t�F�[�h���l
};