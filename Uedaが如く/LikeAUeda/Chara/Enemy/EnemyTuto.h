#pragma once
#include "EnemyBase.h"

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
	// 当たり判定位置の更新
	void UpdateCol();
};

