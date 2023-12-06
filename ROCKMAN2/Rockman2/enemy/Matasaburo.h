#pragma once
#include "EnemyBase.h"
#include "Vec2.h"

/// <summary>
/// またさぶろうのクラス
/// </summary>
class Matasaburo : public EnemyBase
{
public:
	Matasaburo();
	virtual ~Matasaburo();

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Start() override;
	virtual void OnDamage(int damage) override;

	// 攻撃を受けたとき
	virtual void OnDamage()override;

private:
	int m_handle;
	int m_hp;
};

