#include "EnemyBase.h"
#include "RecoveryBase.h"
#include "RecoverySmallHp.h"
#include "ShotBase.h"
#include "SceneMain.h"
#include "Bg.h"
#include "DxLib.h"
#include "Game.h"

EnemyBase::EnemyBase():
	m_pMain(nullptr),
	m_pBg(nullptr),
	m_pRecovery(nullptr),
	m_handle(-1),
	m_isExist(false),
	m_isDead(false),
	m_hp(0),
	m_dir(kDirLeft)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
	m_isDead = false;
}

void EnemyBase::Update()
{
	// 存在しない敵の処理はしない
	if (!m_isExist) return;
}

void EnemyBase::Draw()
{
}

void EnemyBase::Start(float posX, float posY)
{
	m_isExist = true;
}

void EnemyBase::OnDamage()
{
	// 現在のHPを減らす
	m_hp--;

	// HPが0以下になったら存在を消す
	if (m_hp <= 0)
	{
		m_isExist = false;
		m_isDead = true;
	}
}
