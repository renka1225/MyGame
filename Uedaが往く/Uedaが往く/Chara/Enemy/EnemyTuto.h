#pragma once
#include "EnemyBase.h"

/// <summary>
/// �`���[�g���A���Ŏg�p����G
/// </summary>
class EnemyTuto : public EnemyBase
{
public:
	EnemyTuto();
	virtual ~EnemyTuto();
	virtual void Init() override;
	virtual void Update(Player& player, Stage& stage) override;
	virtual void Draw() override;
};

