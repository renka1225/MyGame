#pragma once
#include "EnemyBase.h"

/// <summary>
/// �G(�E��)
/// </summary>
class EnemyNinja : public EnemyBase
{
public:
	EnemyNinja();
	virtual ~EnemyNinja();
	virtual void Init() override;
	virtual void Update(Player& player, Stage& stage) override;
	virtual void Draw() override;
	// �_���[�W���󂯂��ۂ̏���
	virtual void OnDamage(float damage) override;

private:
	// ���̍s�������߂�
	void DecideNextAction();
};

