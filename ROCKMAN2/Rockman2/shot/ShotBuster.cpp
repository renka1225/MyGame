#include "ShotBuster.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include "Bg.h"
#include "Game.h"
#include <cassert>

// 定数の定義
namespace
{
	// 弾の移動速度
	constexpr float kSpeed = 15.0f;
	// ショットの大きさ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
	// 画像の拡大率
	constexpr float kScale = 0.5f;
}

ShotBuster::ShotBuster()
{
	// 弾のグラフィックロード
	m_handle = LoadGraph("data/image/Shot/shotBuster.png");
}

ShotBuster::~ShotBuster()
{
	DeleteGraph(m_handle);
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

	// 現在位置の更新
	m_pos += m_vec;

	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);

	// 画面外に出た処理
	bool isOut = false;	// チェック中の座標が画面外かどうかフラグ
	if (m_pos.x < m_pPlayer->GetPos().x - Game::kScreenWidth * 0.5) isOut = true; // 画面左端
	if (m_pos.x > m_pPlayer->GetPos().x + Game::kScreenWidth * 0.5) isOut = true; // 画面右端

	// 画面内ならここで終了
	if (!isOut) return;

	// 画面外に出た
	m_isExist = false;

}

void ShotBuster::Draw()
{
	if (!m_isExist) return;

	// 中央座標を左上座標に変換
	int x = static_cast<int>(m_pos.x - kWidth * 0.5);
	int y = static_cast<int>(m_pos.y - kHeight * 0.5);

	// スクロール量を反映する
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	DrawRectRotaGraph(x, y, 0, 0, kWidth, kHeight, kScale, 0.0f, m_handle, true);

#ifdef _DEBUG
	// MEMO:スクロールが反映されないためコメントアウト
	// 弾の当たり判定デバッグ表示
	//m_colRect.Draw(0xff0000, false);
#endif
}

void ShotBuster::Start(Vec2 pos)
{
	m_isExist = true;

	// 初期位置の設定
	m_pos = pos;

	// 1フレームあたりの移動ベクトルを決定する
	if (m_pPlayer->GetDir()) // プレイヤーが右を向いている場合
	{
		m_vec.x = kSpeed;
	}
	else // プレイヤーが左を向いている場合
	{
		m_vec.x = -kSpeed;
	}
}
