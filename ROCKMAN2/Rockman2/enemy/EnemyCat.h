#pragma once
#include "EnemyBase.h"

/// <summary>
/// ”L‚Ì“GƒNƒ‰ƒX
/// </summary>
class EnemyCat : public EnemyBase
{
public:
	EnemyCat();
	virtual ~EnemyCat();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Start() override;
	virtual void OnDamage() override;
};

