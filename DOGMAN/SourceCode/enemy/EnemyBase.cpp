#include "EnemyBase.h"
#include "RecoveryBase.h"
#include "RecoverySmallHp.h"
#include "ShotBase.h"
#include "SceneMain.h"
#include "Bg.h"
#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

EnemyBase::EnemyBase():
	m_pMain(nullptr),
	m_pBg(nullptr),
	m_pRecovery(nullptr),
	m_pPlayer(nullptr),
	m_handle(-1),
	m_isExist(false),
	m_isDead(false),
	m_hp(0),
	m_dir(kDirLeft),
	m_damageSE(-1),
	m_damageEffect(-1),
	m_damageFrame(0),
	m_moveRangeX(0.0f)
{
	// 音の読み込み
	m_damageSE = LoadSoundMem("data/sound/SE/enemyDamage.mp3");
	assert(m_damageSE != -1);
	// 画像の読み込み
	m_damageEffect = LoadGraph("data/image/Effect/enemyDead.png");
	assert(m_damageEffect != -1);
}

EnemyBase::~EnemyBase()
{
	DeleteSoundMem(m_damageSE);
	DeleteGraph(m_damageEffect);
}

void EnemyBase::Init(Bg* pBg, Player* pPlayer)
{
	m_pBg = pBg;
	m_pPlayer = pPlayer;
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

void EnemyBase::Start(float posX, float posY, float moveRangeX)
{
	m_isExist = true;
}

void EnemyBase::OnDamage()
{
	// ダメージ演出中は再度食らわない
	if (m_damageFrame > 0) return;

	// 現在のHPを減らす
	if (m_pPlayer->IsMiddleFire())
	{
		m_hp -= 3;
	}
	else if (m_pPlayer->IsBigFire())
	{
		m_hp -= 5;
	}
	else
	{
		m_hp--;
	}

	// SEを鳴らす
	PlaySoundMem(m_damageSE, DX_PLAYTYPE_NORMAL, true);

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
