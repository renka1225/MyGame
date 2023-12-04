#include "Matasaburo.h"
#include "Game.h"
#include "DxLib.h"

Matasaburo::Matasaburo():
	EnemyBase()
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

	// 現在位置の更新
	m_pos += m_vec;

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

void Matasaburo::Start()
{
	// 敵キャラクターを登場させる
	m_isExist = true;

	// 画像サイズ
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	// 現在位置
	m_pos.x = static_cast<float>(800);
	m_pos.y = static_cast<float>(500);
}
