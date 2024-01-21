#include "EnemyCat.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// 敵のサイズ
	constexpr int kWidth = 30;
	constexpr int kHeight = 64;
	// 拡大率
	constexpr float kEnlarge = 3.0f;

	// 移動速度
	constexpr float kSpeed = 2.0f;

	// 最大HP
	constexpr int kHp = 5;
}


EnemyCat::EnemyCat()
{
	m_handle = LoadGraph("data/image/Enemy/cat.png");
}

EnemyCat::~EnemyCat()
{
	DeleteGraph(m_handle);
}

void EnemyCat::Init()
{
	m_hp = kHp;
}

void EnemyCat::Update()
{
	// 存在しない敵の処理はしない
	if (!m_isExist) return;

	// 現在位置の更新
	m_pos += m_vec;

	// TODO:敵を左右に移動させる
	if (m_pos.x < 500 || m_pos.x > 1000)
	{
		m_vec.x *= -1;
	}

	// 画面外に出た処理
	bool isOut = false;	// チェック中の座標が画面外かどうかフラグ
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // 画面左端
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // 画面右端

	// 画面内ならここで終了
	if (!isOut) return;

	// 画面外に出たら終了する
	m_isExist = false;

	// 当たり判定を生成
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth), static_cast<float>(kHeight));
}

void EnemyCat::Draw()
{
	DrawRectRotaGraph(static_cast<int>(m_pos.x + kWidth * 0.5f), static_cast<int>(m_pos.y + kHeight * 0.5f), 0, 0, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);

#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(0x00ff00, false);
#endif
}

void EnemyCat::Start()
{
	// 敵キャラクターを登場させる
	m_isExist = true;

	m_pos = { 1000, 700 };
	m_vec.x -= kSpeed;
}

void EnemyCat::OnDamage()
{
	// 弾が当たったらHPを減らす
	m_hp--;

	// HPが0以下になったら存在を消す
	if (m_hp <= 0)
	{
		m_isExist = false;
	}
}
