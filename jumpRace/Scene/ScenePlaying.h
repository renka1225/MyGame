#pragma once
#include "SceneBase.h"
#include <memory>

class ManagerModel;
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
	virtual ~ScenePlaying() {};

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void StartStaging();				// �X�^�[�g���o�̕\��
	void UpdateCommand(Input& input);	// ���̓R�}���h�̍X�V
	void DrawCommand();					// ���̓R�}���h�̕\��

private:
	// �|�C���^
	std::shared_ptr<ManagerModel> m_pModel;		// 3D���f��
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
	int m_nowCommand;	// ���݂̃R�}���h

	int m_startTime;	// �X�^�[�g���̉��o����
	int m_time;			// �o�ߎ���
	int m_pushCount;	// �{�^������������

private:	// �萔
	static constexpr int kMaxPush = 10;		// 50��{�^�����͂��s��

	// �X�^�[�g���o
	static constexpr int kStartTime = 240;			// �X�^�[�g���̉��o����
	static constexpr int kStartCount1 = 180;		// 1�J�E���g��
	static constexpr int kStartCount2 = 120;		// 2�J�E���g��
	static constexpr int kStartCount3 = 60;			// 3�J�E���g��
	static constexpr int kStartCount4 = 0;			// startSE��炷
	static constexpr int kStartCountPosX = 620;		// �J�E���g�\���ʒuX
	static constexpr int kStartCountPosY = 200;		// �J�E���g�\���ʒuY

	static constexpr int kCommandSize = 16;			// ���̓R�}���h�̃T�C�Y
	static constexpr float kCommandScale = 4.0f;	// ���̓R�}���h�̊g�嗦
	static constexpr int kCommandPosX = 645;		// ���̓R�}���h�\���ʒuX
	static constexpr int kCommandPosY = 250;		// ���̓R�}���h�\���ʒuY
};