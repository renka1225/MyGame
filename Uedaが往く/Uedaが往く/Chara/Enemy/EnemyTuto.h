#pragma once
#include "EnemyBase.h"
#include <functional>

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
	//// ��ԑJ�ڗp�֐��|�C���^
	//typedef void (EnemyTuto:: *UpdateFunc)();
	//UpdateFunc m_updater;
	//std::vector<UpdateFunc> m_updateFuncTbl;
};