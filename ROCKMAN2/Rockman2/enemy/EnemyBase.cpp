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
	m_damageFrame(0)
{
	// ���̓ǂݍ���
	m_damageSE = LoadSoundMem("data/sound/SE/enemyDamage.mp3");
	assert(m_damageSE != -1);
	// �摜�̓ǂݍ���
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
	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	// �_���[�W�G�t�F�N�g
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
	// �_���[�W���o���͍ēx�H���Ȃ�
	if (m_damageFrame > 0) return;

	// ���݂�HP�����炷
	m_hp--;

	// SE��炷
	PlaySoundMem(m_damageSE, DX_PLAYTYPE_NORMAL, true);

	// HP��0�ȉ��ɂȂ����瑶�݂�����
	if (m_hp <= 0)
	{
		m_isExist = false;
		m_isDead = true;
	}
}

void EnemyBase::HitCollision(Rect chipRect)
{

}
