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

void EnemyBase::Start(float posX, float posY)
{
	m_isExist = true;
}

void EnemyBase::OnDamage()
{
	// �_���[�W���o���͍ēx�H���Ȃ�
	if (m_damageFrame > 0) return;

	// ���o�t���[������ݒ肷��
	m_damageFrame = 30;

	// ���݂�HP�����炷
	m_hp--;

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
