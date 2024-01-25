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
	m_dir(kDirLeft),
	m_damageEffect(-1),
	m_damageFrame(0)
{
	m_damageEffect = LoadGraph("data/image/Effect/enemyDamage.png");
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

	// ダメージエフェクト
	m_damageFrame--;
	if (m_damageFrame < 0)
	{
		m_damageFrame = 0;
	}
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
	// ダメージ演出中は再度食らわない
	if (m_damageFrame > 0) return;

	// 演出フレーム数を設定する
	m_damageFrame = 30;

	// 現在のHPを減らす
	m_hp--;

	// HPが0以下になったら存在を消す
	if (m_hp <= 0)
	{
		m_isExist = false;
		m_isDead = true;
	}
}

void EnemyBase::HitCollision(Rect chipRect)
{

}
