#pragma once
#include <memory>

class Player;
class UIGauge;

/// <summary>
/// “G‚ÌŠî’êƒNƒ‰ƒX
/// </summary>
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();
	virtual void Init() = 0;
	virtual void Update(Player& player) = 0;
	virtual void Draw() = 0;
	virtual void OnDamage(float damage);	// UŒ‚‚ğó‚¯‚½Û‚Ìˆ—

	float GetHp() const { return m_hp; }	// “G‚ÌHP‚ğæ“¾
	VECTOR GetPos() const { return m_pos; } // “G‚ÌÀ•W‚ğæ“¾

protected:
	std::shared_ptr<UIGauge> m_pUIGauge;

	VECTOR m_pos;		// ˆÊ’u
	float m_hp;			// HP
	int m_modelHandle;	// “G‚Ì3Dƒ‚ƒfƒ‹
};

