#include "RecoverySmallHp.h"
#include "EnemyBase.h"
#include "Game.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	// アイテムのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// アイテムの落下速度
	constexpr int kSpeed = 5;
}

RecoverySmallHp::RecoverySmallHp():
	m_frame(0)
{
	m_handle = LoadGraph("data/image/Recovery/smallHp.png");
}

RecoverySmallHp::~RecoverySmallHp()
{
}

void RecoverySmallHp::Init()
{
	m_frame = 0;
}

void RecoverySmallHp::Update()
{
	// 存在しないアイテムの処理はしない
	if (!m_isExist) return;

	// 現在位置の更新
	m_pos += m_vec;
	// TODO:地面より下に落ちないようにする
	if (m_pos.y > 550)
	{
		m_pos.y = 550;
	}

	// 当たり判定の更新
	UpdateCollision();

	// 5秒以上たったらアイテムを消す
	m_frame++;
	if (m_frame > 300)
	{
		m_isExist = false;
		m_frame = 0;
	}

	// 画面外に出た処理
	bool isOut = false;	// チェック中の座標が画面外かどうかフラグ
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // 画面左端
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // 画面右端

	// 画面内ならここで終了
	if (!isOut) return;

	// 画面外に出たら終了する
	m_isExist = false;
}

void RecoverySmallHp::Draw()
{
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), 1.0, 0.0, m_handle, true, false);

#ifdef _DEBUG
	// アイテムの当たり判定デバッグ表示
	m_colRect.Draw(0xff0000, false);
#endif
}

void RecoverySmallHp::Start(Vec2 pos)
{
	m_isExist = true;

	// 初期位置の設定
	// 倒した敵の現在地を取得する
	m_pos = pos;

	// アイテムを下に落とす
	m_vec.y += kSpeed;
}
