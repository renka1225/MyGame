#pragma once
#include "EnemyBase.h"

/// <summary>
/// �`���[�g���A���Ŏg�p����G
/// </summary>
class EnemyTuto : public EnemyBase
{
public:
	EnemyTuto();
	virtual ~EnemyTuto();
	virtual void Init() override;
	virtual void Update(Player& player) override;
	virtual void Draw() override;

private:
	void UpdateCol();	// �����蔻��ʒu�̍X�V
};

