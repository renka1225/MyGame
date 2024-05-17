#pragma once
#include "EnemyBase.h"

/// <summary>
/// 鳥の敵クラス
/// </summary>
class EnemyBird : public EnemyBase
{
public:
	EnemyBird();
	virtual ~EnemyBird();

	virtual void Init(Bg* pBg, Player* pPlayer) override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Start(float posX, float posY, float moveRangeX) override;
	virtual void HitCollision(Rect chipRect) override;
	virtual void OnDamage() override;

private:
	// 歩きアニメーション
	int m_flyAnimFrame;

	// sinでの移動
	float m_sinCount;
};

