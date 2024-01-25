#pragma once
#include "EnemyBase.h"

/// <summary>
/// 熊の敵クラス
/// </summary>
class EnemyBear : public EnemyBase
{
public:
	EnemyBear();
	virtual ~EnemyBear();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Start(float posX, float posY) override;
	virtual void HitCollision(Rect chipRect) override;
	virtual void OnDamage() override;

private:
	// 歩きアニメーション
	int m_walkAnimFrame;
};

