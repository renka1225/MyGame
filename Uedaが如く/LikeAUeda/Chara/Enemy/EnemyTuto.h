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
	virtual void Update(Player& player, Stage& stage) override;
	virtual void Draw() override;

private:
	// �����蔻��ʒu�̍X�V
	void UpdateCol();
	// �A�j���[�V�����X�e�[�g�̍X�V
	void UpdateAnimState(EnemyState prevState);
	// �A�j���[�V��������
	virtual void UpdateAnim() override;
};

