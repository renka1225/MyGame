#pragma once
#include "CharacterBase.h"
#include <memory>

class Player;

/// <summary>
/// �G�̊��N���X
/// </summary>
class EnemyBase : public CharacterBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();
	virtual void Init() = 0;
	virtual void Update(Player& player) = 0;
	virtual void Draw() = 0;

	float GetHp() const { return m_hp; }	// �G��HP���擾
	VECTOR GetPos() const { return m_pos; } // �G�̍��W���擾

protected:
	virtual void UpdateAngle(Player& player);	// �G�̊p�x���X�V
	void CheckCollision(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);
};

