#pragma once
#include "SceneBase.h"
#include <memory>

class Player;
class Camera;

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
	void UpdateCommand(Input& input);	// ���̓R�}���h�̍X�V
	void DrawCommand();					// ���̓R�}���h�̕\��

private:
	// �|�C���^
	std::shared_ptr<Player> m_pPlayer;	// �v���C���[
	std::shared_ptr<Camera> m_pCamera;	// �J����

	// ���̓R�}���h�̎��
	enum Command
	{
		A,
		B,
		X,
		Y
	};
	int m_nowCommand;	// ���݂̃R�}���h

	int m_time;			// �o�ߎ���
	int m_pushCount;	// �{�^������������

private:	// �萔
	static constexpr int kMaxPush = 50;		// 50��{�^�����͂��s��
};

