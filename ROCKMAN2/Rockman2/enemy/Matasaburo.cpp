#include "Matasaburo.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	constexpr float kSpeed = 4.0f;
}

Matasaburo::Matasaburo() :
	EnemyBase(),
	m_hp(1)
{
	m_handle = LoadGraph("data/image/Enemy/matasaburo.png");
}

Matasaburo::~Matasaburo()
{
}

void Matasaburo::Update()
{

	// 存在しない敵の処理はしない
	if (!m_isExist) return;

	// 当たり判定の更新
	UpdateCollision();

	// 画面外に出たら存在を消す
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	if (m_pos.x > Game::kScreenWidth - width / 2)
	{
		m_isExist = false;
	}
}

void Matasaburo::Draw()
{
	// 中心位置を基準として描画する
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), 1.0, 0.0, m_handle, true, false);

#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(0x00ff00, false);
#endif
}


void Matasaburo::Start()
{
	// 敵キャラクターを登場させる
	m_isExist = true;

	// 画像サイズ
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	// 現在位置
	m_pos.x = static_cast<float>(900);
	m_pos.y = static_cast<float>(500);

<<<<<<< HEAD
	m_vec.x -= 5;
}

void Matasaburo::OnDamage()
{
	// 弾が当たったらHPを減らす
	m_hp--;

	// HPが0以下になったら存在を消す
=======
	// 1フレームあたりの移動ベクトルを決定する
	m_vec.x = -kSpeed;
}

void Matasaburo::OnDamage(int damage)
{
	// HPを減らす
	m_hp -= damage;

>>>>>>> b7e625657adb768e3ac97a47834cb71cb76e3f7e
	if (m_hp <= 0)
	{
		m_isExist = false;
	}
}
