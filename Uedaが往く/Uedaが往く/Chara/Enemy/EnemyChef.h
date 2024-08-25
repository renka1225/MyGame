#pragma once
#include "EnemyBase.h"

/// <summary>
/// ÉVÉFÉt
/// </summary>
class EnemyChef : public EnemyBase
{
public:
	EnemyChef();
	virtual ~EnemyChef();
	virtual void Init(std::shared_ptr<EffectManager> pEffect, VECTOR pos) override;
	virtual void Update(Player& player, Stage& stage, SceneStageBase& sceneStage) override;
	virtual void Draw() override;
};

