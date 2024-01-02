#include "RecoverySmallShot.h"
#include "EnemyBase.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// アイテムのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// 落下速度
	constexpr int kSpeed = 5;
}

RecoverySmallShot::RecoverySmallShot()
{
	m_handle = LoadGraph("data/image/Recovery/smallShot.png");
}

RecoverySmallShot::~RecoverySmallShot()
{
}

void RecoverySmallShot::Init()
{
}

void RecoverySmallShot::Update()
{
	// 存在しないアイテムの処理はしない
	if (!m_isExist) return;

	// 現在位置の更新
	m_pos += m_vec;

	// TODO:地面の上に着地するようにする
	if (m_pos.y > 550)
	{
		m_vec.y = 0;
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

	// 画面外に出たらアイテムを消す
	m_isExist = false;
}

void RecoverySmallShot::Draw()
{
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), 1.0, 0.0, m_handle, true, false);
#ifdef _DEBUG
	// 弾の当たり判定デバッグ表示
	m_colRect.Draw(0x00ff00, false);
#endif
}

void RecoverySmallShot::Start(Vec2 pos)
{
	m_isExist = true;

	// 初期位置の設定
	// 倒した敵の現在地を取得する
	m_pos = pos;

	// アイテムを下に落とす
	m_vec.y += kSpeed;
}

