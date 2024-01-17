#include "RecoveryFullHp.h"
#include "EnemyBase.h"
#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// アイテムのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
}

RecoveryFullHp::RecoveryFullHp()
{
	m_handle = LoadGraph("data/image/Recovery/fullHp.png");
}

RecoveryFullHp::~RecoveryFullHp()
{
}

void RecoveryFullHp::Init()
{
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
	// 中央座標を左上座標に変換
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// スクロール量を反映する
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	DrawRotaGraph(x, y, 1.0, 0.0, m_handle, true, false);

#ifdef _DEBUG
	// アイテムの当たり判定デバッグ表示
	m_colRect.Draw(0x00ff00, false);
#endif
}

void RecoveryFullHp::Start(Vec2 pos)
{
	m_isExist = true;

	// 初期位置の設定
	m_pos = pos;
}
