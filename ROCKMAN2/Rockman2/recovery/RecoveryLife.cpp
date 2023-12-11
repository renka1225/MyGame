#include "RecoveryLife.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// アイテムのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
}

RecoveryLife::RecoveryLife():
	m_lifeRecovery(1)
{
	m_lifeRecHandle = LoadGraph("data/image/Recovery/life");
}

RecoveryLife::~RecoveryLife()
{
}

void RecoveryLife::Init()
{
}

void RecoveryLife::Update()
{
	// 画面内に存在しなければ終了する
	if (!m_isExist) return;

	// 当たり判定の更新
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight);

	// 画面外に出た処理
	bool isOut = false;	// チェック中の座標が画面外かどうかフラグ
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // 画面左端
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // 画面右端

	// 画面内ならここで終了
	if (!isOut) return;

	// 画面外に出た
	m_isExist = false;

	DrawGraph(m_pos.x, m_pos.y, m_lifeRecHandle, true);
}

void RecoveryLife::Draw()
{
#ifdef _DEBUG
	// 弾の当たり判定デバッグ表示
	m_colRect.Draw(0xff0000, false);
#endif
}
