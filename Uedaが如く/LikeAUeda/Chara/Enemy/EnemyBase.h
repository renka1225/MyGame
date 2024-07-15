#pragma once
#include "CharacterBase.h"
#include <memory>

class Player;

/// <summary>
/// “G‚ÌŠî’êƒNƒ‰ƒX
/// </summary>
class EnemyBase : public CharacterBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();
	virtual void Init() = 0;
	virtual void Update(Player& player) = 0;
	virtual void Draw() = 0;

	float GetHp() const { return m_hp; }	// “G‚ÌHP‚ğæ“¾
	VECTOR GetPos() const { return m_pos; } // “G‚ÌÀ•W‚ğæ“¾

protected:
	virtual void UpdateAngle(Player& player);	// “G‚ÌŠp“x‚ğXV
	void CheckCollision(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);
};

