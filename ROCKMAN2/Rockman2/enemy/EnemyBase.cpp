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
	// 存在しない敵の処理はしない
	if (!m_isExist) return;

	// グラフィックが設定されていなければ止まる
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
	// 現在のHPを減らす
	m_hp--;

	// HPが0以下になったら存在を消す
	if (m_hp <= 0)
	{
		m_isExist = false;

		RecoverySmallHp* pRecovery = new RecoverySmallHp;

		// 新しい回復アイテムを生成する
		pRecovery->Init();
		pRecovery->SetMain(m_pMain);
		pRecovery->SetEnemy(this);
		pRecovery->Start(m_pos);
		// 以降更新やメモリの解放はSceneMainに任せる
		m_pMain->AddItem(pRecovery);

		// TODO: 確率でアイテムをドロップ
		//switch (GetRand(5))
		//{
		//case 0: // 何もドロップしない
		//	break;
		//case 1:	// HP回復(小)ドロップ
		//	m_pRecovery->SmallHp();
		//	break;
		//case 2:	// HP回復(大)ドロップ
		//	m_pRecovery->GreatHp();
		//	break;
		//case 3:	// 弾エネルギー回復(小)ドロップ
		//	m_pRecovery->SmallShot();
		//	break;
		//case 4:	// 弾エネルギー回復(大)ドロップ
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

	// 中心座標を指定して当たり判定のRectを生成する
	m_colRect.SetCenter(m_pos.x, m_pos.y, width, height);
}
