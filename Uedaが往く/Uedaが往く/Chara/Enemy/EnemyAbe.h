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
	virtual void Init() override;
	virtual void Update(Player& player, Stage& stage) override;
	virtual void Draw() override;
};

