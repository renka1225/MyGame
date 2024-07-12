#include "DxLib.h"
#include "UIGauge.h"
#include "EnemyBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyBase::EnemyBase():
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_hp(0.0f),
	m_modelHandle(-1)
{
	m_pUIGauge = std::make_shared<UIGauge>();
}


/// <summary>
/// デストラクタ
/// </summary>
EnemyBase::~EnemyBase()
{
}


/// <summary>
/// 攻撃を受けた際の処理
/// </summary>
void EnemyBase::OnDamage(float damage)
{
	m_hp -= damage;
}

