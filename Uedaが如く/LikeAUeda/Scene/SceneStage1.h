#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class Stage;

/// <summary>
/// ステージ1
/// </summary>
class SceneStage1 : public SceneBase
{
public:
	SceneStage1() {};
	SceneStage1(std::shared_ptr<Player> player, std::shared_ptr<Camera> camera, std::shared_ptr<Stage> pStage);
	virtual  ~SceneStage1();
	virtual void Init(LoadData& data);
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Stage> m_pStage;
};

