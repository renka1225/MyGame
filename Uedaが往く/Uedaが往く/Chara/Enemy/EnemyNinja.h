#pragma once
#include "EnemyBase.h"

/// <summary>
/// 敵(忍者)
/// </summary>
class EnemyNinja : public EnemyBase
{
public:
	EnemyNinja();
	virtual ~EnemyNinja();
	virtual void Init() override;
	virtual void Update(Player& player, Stage& stage) override;
	virtual void Draw() override;
	// ダメージを受けた際の処理
	virtual void OnDamage(float damage) override;

private:
	// 次の行動を決める
	void DecideNextAction();
};

