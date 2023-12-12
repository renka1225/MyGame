#include "RecoveryFullHp.h"
#include "Player.h"
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

RecoveryFullHp::RecoveryFullHp()
{
	m_hpFullRecHandle = LoadGraph("data/image/Recovery/FullHp.png");
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

	// 当たり判定の更新
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight);

	Rect playerRect = m_pPlayer->GetColRect();	// プレイヤーの当たり判定

	// プレイヤーと回復アイテムの当たり判定
	if (playerRect.IsCollision(m_colRect))
	{
		m_pPlayer->HpGreatRecovery();

		// 取得したらアイテムを消す
		m_isExist = false;
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

void RecoveryFullHp::Draw()
{
	DrawGraph(m_pos.x, m_pos.y, m_hpFullRecHandle, true);

#ifdef _DEBUG
	// アイテムの当たり判定デバッグ表示
	m_colRect.Draw(0xff0000, false);
#endif
}

void RecoveryFullHp::Start(Vec2 pos)
{
	m_isExist = true;

	// 初期位置の設定
	m_pos = pos;
}