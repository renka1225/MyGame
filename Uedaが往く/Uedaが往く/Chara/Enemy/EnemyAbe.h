#pragma once
#include "EnemyBase.h"

/// <summary>
/// Abe(–ê‚³‚ñ)
/// </summary>
class EnemyAbe : public EnemyBase
{
public:
	EnemyAbe();
	virtual ~EnemyAbe();
	virtual void Init(VECTOR pos) override;
	virtual void Update(Player& player, Stage& stage, SceneStageBase& sceneStage) override;
	virtual void Draw() override;
};

