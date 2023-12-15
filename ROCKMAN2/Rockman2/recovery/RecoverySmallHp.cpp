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

	// 初期位置
	constexpr float kPosX = 500;
	constexpr float kPosY = 500;
}

RecoverySmallHp::RecoverySmallHp():
	m_isExist(false),
	m_frame(0)
{
	m_hpSmallRecHandle = LoadGraph("data/image/Recovery/smallHp.png");
}

RecoverySmallHp::~RecoverySmallHp()
{
}

void RecoverySmallHp::Init()
{
	m_isExist = false;
	m_frame = 0;
}

void RecoverySmallHp::Update()
{
	// 存在しないアイテムの処理はしない
	if (!m_isExist) return;

	m_frame++;
	// 5秒以上たったらアイテムを消す
	if (m_frame > 300)
	{
		m_frame = 0;
		m_isExist = false;
	}

	// 当たり判定の更新
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight);

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
	DrawGraph(m_pos.x, m_pos.y, m_hpSmallRecHandle, true);

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
}
