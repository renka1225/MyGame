#include "ShotBuster.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include <cassert>

// 定数の定義
namespace
{
	// 弾の移動速度
	constexpr float kSpeed = 8.0f;
	// ショットの大きさ
	constexpr float kWidth = 16.0f;
	constexpr float kHeight = 16.0f;
}

ShotBuster::ShotBuster()
{
}

ShotBuster::~ShotBuster()
{
}

void ShotBuster::Init()
{
}

void ShotBuster::Update()
{
	// 弾が存在しなければ終了する
	if (!m_isExist) return;

	// プレイヤーのポインタが設定されていないとき止まる
	assert(m_pPlayer);

	// 画面外に出た処理
	// 過去の表示位置も含めてすべて画面外に出たら終了
	bool isOut = false;	// チェック中の座標が画面外かどうかのフラグ
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true;
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true;
	if (m_pos.y < 0.0f - kHeight / 2) isOut = true;
	if (m_pos.y > Game::kScreenHeight + kHeight / 2) isOut = true;
	// チェック中の座標が画面内ならここで終了
	if (!isOut) return;

	// 障害物に当たったら消える
	//if ()
	//{
	//	m_isExist = false;
	//	return;	// 終了が確定したら以降の処理は行わない
	//}

	// 画面外に出たら消える
	m_isExist = false;
}

void ShotBuster::Draw()
{
	if (!m_isExist) return;
	DrawCircle(m_pos.x - kWidth / 2, m_pos.y - kHeight / 2, 0x00ff00, true);
}

void ShotBuster::Start(Vec2 pos)
{
	// m_pMain == nullptrなら止まる
	assert(m_pMain);

	m_isExist = true;

	// 初期位置の設定
	m_pos = pos;
}
