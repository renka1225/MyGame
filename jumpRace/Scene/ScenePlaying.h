#pragma once
#include "SceneBase.h"
#include <memory>

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
	void StartCount();					// �X�^�[�g�J�E���g��炷
	void StartStaging();				// �X�^�[�g���o�̕\��
	void UpdateCommand(Input& input);	// ���̓R�}���h�̍X�V
	void DrawCommand();					// ���̓R�}���h�̕\��

private:
	// �|�C���^
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
	static constexpr int kStartTime = 60 * 4;		// �X�^�[�g���̉��o����
	static constexpr int kStartCount1 = 60 * 3;		// 1�J�E���g��
	static constexpr int kStartCount2 = 60 * 2;		// 2�J�E���g��
	static constexpr int kStartCount3 = 60;			// 3�J�E���g��
	static constexpr int kStartCount4 = 0;			// startSE��炷
	static constexpr int kStartCountPosX = 500;		// �J�E���g�\���ʒuX
	static constexpr int kStartCountPosY = 400;		// �J�E���g�\���ʒuY
};