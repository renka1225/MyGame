#include "RecoveryFullHp.h"
#include "EnemyBase.h"
#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// アイテムのサイズ
	constexpr int kWidth = 26;
	constexpr int kHeight = 30;
	// 拡大率
	constexpr float kScale = 1.2f;
}

RecoveryFullHp::RecoveryFullHp()
{
	m_handle = LoadGraph("data/image/Recovery/fullHp.png");
}

RecoveryFullHp::~RecoveryFullHp()
{
	DeleteGraph(m_handle);
}

void RecoveryFullHp::Init(Bg* pBg)
{
	m_pBg = pBg;
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
	int x = static_cast<int>(m_pos.x - kWidth * 0.5);
	int y = static_cast<int>(m_pos.y - kHeight * 0.5);

	// スクロール量を反映する
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	DrawRotaGraph(x, y, kScale, 0.0, m_handle, true, false);
}

void RecoveryFullHp::Start(Vec2 pos)
{
	m_isExist = true;

	// 初期位置の設定
	m_pos = pos;
}
