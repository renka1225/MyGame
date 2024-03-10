#pragma once
#include "SceneBase.h"

class Player;
class Camera;

/// <summary>
/// �v���C���̃V�[��
/// </summary>
class ScenePlaying : public SceneBase
{
public:
	ScenePlaying();
	virtual ~ScenePlaying() {};

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:
	// �|�C���^
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;

	int m_time;
};

