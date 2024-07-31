#pragma once
#include "EnemyBase.h"

/// <summary>
/// �V�F�t
/// </summary>
class EnemyChef : public EnemyBase
{
public:
	EnemyChef();
	virtual ~EnemyChef();
	virtual void Init() override;
	virtual void Update(Player& player, Stage& stage) override;
	virtual void Draw() override;
	// �_���[�W���󂯂��ۂ̏���
	virtual void OnDamage(float damage) override;

private:
	// ���̍s�������߂�
	void DecideNextAction();
};

