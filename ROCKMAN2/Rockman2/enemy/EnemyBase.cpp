#include "EnemyBase.h"
#include "RecoveryBase.h"
#include "RecoverySmallHp.h"
#include  "ShotBase.h"
#include "SceneMain.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

EnemyBase::EnemyBase():
	m_handle(-1),
	m_isExist(false),
	m_hp(0),
	m_pRecovery(nullptr)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
	m_hp = 0;
}

void EnemyBase::Update()
{
	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	// �O���t�B�b�N���ݒ肳��Ă��Ȃ���Ύ~�܂�
	assert(m_handle != -1);
}

void EnemyBase::Draw()
{
}

void EnemyBase::Start()
{
	m_isExist = false;
}

void EnemyBase::OnDamage()
{
	// ���݂�HP�����炷
	m_hp--;

	// HP��0�ȉ��ɂȂ����瑶�݂�����
	if (m_hp <= 0)
	{
		m_isExist = false;

		RecoverySmallHp* pRecovery = new RecoverySmallHp;

		// �V�����񕜃A�C�e���𐶐�����
		pRecovery->Init();
		pRecovery->SetMain(m_pMain);
		pRecovery->SetEnemy(this);
		pRecovery->Start(m_pos);
		// �ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
		m_pMain->AddItem(pRecovery);

		// TODO: �m���ŃA�C�e�����h���b�v
		//switch (GetRand(5))
		//{
		//case 0: // �����h���b�v���Ȃ�
		//	break;
		//case 1:	// HP��(��)�h���b�v
		//	m_pRecovery->SmallHp();
		//	break;
		//case 2:	// HP��(��)�h���b�v
		//	m_pRecovery->GreatHp();
		//	break;
		//case 3:	// �e�G�l���M�[��(��)�h���b�v
		//	m_pRecovery->SmallShot();
		//	break;
		//case 4:	// �e�G�l���M�[��(��)�h���b�v
		//	m_pRecovery->GreatShot();
		//	break;
		//case 5:
		//	m_pRecovery->Life();
		//	break;
		//}
	}
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	// ���S���W���w�肵�ē����蔻���Rect�𐶐�����
	m_colRect.SetCenter(m_pos.x, m_pos.y, width, height);
}
