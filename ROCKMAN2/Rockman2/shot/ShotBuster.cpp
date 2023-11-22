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
	m_isExist = true;

	// 初期位置の設定
	m_pos = pos;
}
