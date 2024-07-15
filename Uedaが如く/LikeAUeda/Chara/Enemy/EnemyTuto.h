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
	virtual void Update(Player& player) override;
	virtual void Draw() override;

private:
	void UpdateCol();	// 当たり判定位置の更新
};

