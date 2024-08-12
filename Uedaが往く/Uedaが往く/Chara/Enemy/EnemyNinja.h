#pragma once
#include "EnemyBase.h"

/// <summary>
/// “G(”EŽÒ)
/// </summary>
class EnemyNinja : public EnemyBase
{
public:
	EnemyNinja();
	virtual ~EnemyNinja();
	virtual void Init(VECTOR pos) override;
	virtual void Update(Player& player, Stage& stage, SceneStageBase& sceneStage) override;
	virtual void Draw() override;
};

