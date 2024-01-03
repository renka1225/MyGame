#include "RecoveryFullHp.h"
#include "EnemyBase.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// アイテムのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
}

RecoveryFullHp::RecoveryFullHp():
	m_pMain(nullptr),
	m_handle(-1),
	m_isExist(false)
{
	m_handle = LoadGraph("data/image/Recovery/fullHp.png");
}

RecoveryFullHp::~RecoveryFullHp()
{
}

void RecoveryFullHp::Init()
{
	m_pos.x = 320;
	m_pos.y = 500;
}

void RecoveryFullHp::Update()
{
	// 存在しないアイテムの処理はしない
	if (!m_isExist) return;

	// 当たり判定
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
}

void RecoveryFullHp::Draw()
{
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), 1.0, 0.0, m_handle, true, false);

#ifdef _DEBUG
	// アイテムの当たり判定デバッグ表示
	m_colRect.Draw(0x00ff00, false);
#endif
}
