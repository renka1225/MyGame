#pragma once
#include "SceneStageBase.h"
#include <vector>

class Player;
class Camera;
class Stage;
class EnemyBase;
class CharacterBase;

/// <summary>
/// ステージ1
/// </summary>
class SceneStage1 : public SceneStageBase
{
public:
	SceneStage1() {};
	SceneStage1(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage);
	virtual  ~SceneStage1();
	virtual void Init() override;
	virtual std::shared_ptr<SceneBase> Update(Input& input) override;
	virtual void Draw() override;
};

