#include "RecoveryHp.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// アイテムのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// 初期位置
	constexpr float kPosX = 500;
	constexpr float kPosY = 500;
}

RecoveryHp::RecoveryHp()
{
	m_hpSmallRecHandle = LoadGraph("data/image/Recovery/hpSmall");
	m_hpGreatRecHandle = LoadGraph("data/image/Recovery/hpGreat");
	m_hpFullRecHandle = LoadGraph("data/image/Recovery/hpFull");
}

RecoveryHp::~RecoveryHp()
{
}

void RecoveryHp::Init()
{
}

void RecoveryHp::Update()
{
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

	if (!m_isExist) return;
}

void RecoveryHp::Draw()
{
	DrawGraph(m_pos.x, m_pos.y, m_hpSmallRecHandle, true);
	DrawGraph(m_pos.x, m_pos.y, m_hpGreatRecHandle, true);
	DrawGraph(m_pos.x, m_pos.y, m_hpFullRecHandle, true);

#ifdef _DEBUG
	// 弾の当たり判定デバッグ表示
	m_colRect.Draw(0xff0000, false);
#endif
}

// 回復アイテムの登場
void RecoveryHp::Start()
{
	// アイテムを登場させる
	m_isExist = true;

	// 画像サイズ
	int width = 0;
	int height = 0;
	GetGraphSize(m_hpSmallRecHandle, &width, &height);

	// 現在位置
	m_pos.x = kPosX;
	m_pos.y = kPosY;
}
