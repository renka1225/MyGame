#include "RecoverySmallHp.h"
#include "Player.h"
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
	m_pPlayer(nullptr),
	m_pEnemy(nullptr),
	m_isExist(false)
{
	m_hpSmallRecHandle = LoadGraph("data/image/Recovery/smallHp.png");
}

RecoverySmallHp::~RecoverySmallHp()
{
}

void RecoverySmallHp::Init()
{
	m_isExist = false;
}

void RecoverySmallHp::Update()
{
	// 存在しないアイテムの処理はしない
	if (!m_isExist) return;

	// 当たり判定の更新
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight);

	//Rect playerRect = m_pPlayer->GetColRect();	// プレイヤーの当たり判定

	//// プレイヤーと回復アイテムの当たり判定
	//if (playerRect.IsCollision(m_colRect))
	//{
	//	m_pPlayer->HpSmallRecovery();

	//	// 取得したらアイテムを消す
	//	m_isExist = false;
	//}

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
