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
	// ‘¶İ‚µ‚È‚¢“G‚Ìˆ—‚Í‚µ‚È‚¢
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
	// Œ»İ‚ÌHP‚ğŒ¸‚ç‚·
	m_hp--;

	// HP‚ª0ˆÈ‰º‚É‚È‚Á‚½‚ç‘¶İ‚ğÁ‚·
	if (m_hp <= 0)
	{
		m_isExist = false;
		m_isDead = true;
	}
}
