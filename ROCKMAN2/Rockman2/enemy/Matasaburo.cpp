#include "Matasaburo.h"
#include "RecoverySmallHp.h"
#include "RecoverySmallShot.h"
#include "SceneMain.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// 移動速度
	constexpr float kSpeed = 4.0f;

	// 最大HP
	constexpr int kHp = 3;

	// 初期位置
	constexpr float kPosX = 900;
	constexpr float kPosY = 500;
}

Matasaburo::Matasaburo() :
	EnemyBase(),
	m_hp(kHp)
{
	m_handle = LoadGraph("data/image/Enemy/matasaburo.png");
}

Matasaburo::~Matasaburo()
{
}

// 初期化
void Matasaburo::Init()
{
	// HP
	m_hp = kHp;

	// 現在位置
	m_pos.x = kPosX;
	m_pos.y = kPosY;
}

void Matasaburo::Update()
{
	// 存在しない敵の処理はしない
	if (!m_isExist) return;

	// 現在位置の更新
	m_pos += m_vec;

	// 当たり判定の更新
	UpdateCollision();

	// 画面外に出たら存在を消す
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	// 画面より右に出た
	if (m_pos.x > Game::kScreenWidth - width / 2)
	{
		m_isExist = false;
	}
	// 画面より左に出た
	if (m_pos.x < 0 - width / 2)
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
	m_pos.x = kPosX;
	m_pos.y = kPosY;

	m_vec.x -= 5;
}

void Matasaburo::OnDamage()
{
	// 弾が当たったらHPを減らす
	m_hp--;

	// HPが0以下になったら存在を消す
	if (m_hp <= 0)
	{
		m_isExist = false;
	}
}