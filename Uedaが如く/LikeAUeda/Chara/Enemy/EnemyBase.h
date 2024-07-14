#pragma once
#include "CharacterBase.h"
#include <memory>

class Player;
class UIGauge;

/// <summary>
/// 敵の基底クラス
/// </summary>
class EnemyBase : public CharacterBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();
	virtual void Init() = 0;
	virtual void Update(Player& player) = 0;
	virtual void Draw() = 0;
	virtual void OnDamage(float damage);	// 攻撃を受けた際の処理

	float GetHp() const { return m_hp; }	// 敵のHPを取得
	VECTOR GetPos() const { return m_pos; } // 敵の座標を取得

protected:
	std::shared_ptr<UIGauge> m_pUIGauge;

	VECTOR m_pos;		// 位置
	int m_modelHandle;	// 敵の3Dモデル
};

