#pragma once
#include "CharacterBase.h"
#include <memory>

class Player;

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

	float GetHp() const { return m_hp; }	// 敵のHPを取得
	VECTOR GetPos() const { return m_pos; } // 敵の座標を取得

protected:
	virtual void UpdateAngle(Player& player);	// 敵の角度を更新
	void CheckCollision(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);
};

