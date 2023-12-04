#include "Matasaburo.h"
#include "ShotBase.h"
#include "Game.h"
#include "DxLib.h"

Matasaburo::Matasaburo() :
	EnemyBase(),
	m_hp(3)
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

	// 弾との当たり判定
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])
		{
			Rect shotRect = m_pShot[i]->GetColRect();
			if (shotRect.IsCollision(m_colRect))
			{
				// 弾が当たったらHPを減らす
				m_hp--;

				// HPが0以下になったら敵を削除
				if (m_hp <= 0)
				{
					m_isExist = false;
				}
			}
		}
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
	m_pos.x = static_cast<float>(800);
	m_pos.y = static_cast<float>(500);
}
