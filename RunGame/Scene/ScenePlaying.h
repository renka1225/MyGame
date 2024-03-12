#pragma once
#include "SceneBase.h"

class ManagerModel;
class Player;
class Enemy;
class Camera;

/// <summary>
/// プレイ中のシーン
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
	// ポインタ
	std::shared_ptr<ManagerModel> m_pModel;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Camera> m_pCamera;

	int m_time;
};