#pragma once
#include "EnemyBase.h"
#include <functional>

/// <summary>
/// チュートリアルで使用する敵
/// </summary>
class EnemyTuto : public EnemyBase
{
public:
	EnemyTuto();
	virtual ~EnemyTuto();
	virtual void Init() override;
	virtual void Update(Player& player, Stage& stage) override;
	virtual void Draw() override;

private:
	// 次の行動を決める
	void DecideNextAction();
};