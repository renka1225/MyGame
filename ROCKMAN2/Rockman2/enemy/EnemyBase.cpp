#include "EnemyBase.h"
#include  "ShotBase.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

EnemyBase::EnemyBase():
	m_handle(-1),
	m_isExist(false),
	m_hp(0)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{

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
