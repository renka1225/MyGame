#include "ShotLineMove.h"
#include "Player.h"
#include "Bg.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>


// 定数の定義
namespace
{
	// 弾の移動速度
	constexpr float kSpeed = 10.0f;
	// ショットの大きさ
	constexpr float kWidth = 52.0f;
	constexpr float kHeight = 16.0f;

	// アイテム2号の当たり判定の幅
	constexpr float kLineMoveWidth = 150.0f;
}

ShotLineMove::ShotLineMove():
	m_stopFrame(0),
	m_energy(28)
{
	m_handle = LoadGraph("data/image/Shot/shotLineMove.png");
}

ShotLineMove::~ShotLineMove()
{
}

void ShotLineMove::Init()
{
	m_stopFrame = 60;
	m_isExist = false;
}

void ShotLineMove::Update()
{
	// 弾が存在しなければ終了する
	if (!m_isExist) return;

	// プレイヤーのポインタが設定されていないとき止まる
	assert(m_pPlayer);

	// 静止時間を減らす
	m_stopFrame--;

	// 静止時間が0になったら動かす
	if (m_stopFrame < 0)
	{
		m_pos += m_vec;		// 現在位置を更新
	}

	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x , m_pos.y, kWidth, kHeight);
	m_lineMoveColRect.SetCenter(m_pos.x, m_pos.y, kLineMoveWidth, kHeight);

	// マップチップに当たったら消す
	Rect chipRect;	// マップチップの当たり判定
	if (m_pBg->IsCollision(m_lineMoveColRect, chipRect))
	{
		m_isExist = false;
	}

	// 乗っている最中にエネルギーがなくなったらアイテム2号を消す
	if (m_pPlayer->GetLineEnergy() < 0)
	{
		m_isExist = false;
	}

	// 画面外に出た処理
	bool isOut = false;	// チェック中の座標が画面外かどうかフラグ
	if (m_pos.x < m_pPlayer->GetPos().x - Game::kScreenWidth * 0.5f) isOut = true; // 画面左端
	if (m_pos.x > m_pPlayer->GetPos().x + Game::kScreenWidth * 0.5f) isOut = true; // 画面右端

	// チェック中の座標が画面内ならここで終了
	if (!isOut) return;

	// ここに来たということは画面外にいる
	m_isExist = false;
}

void ShotLineMove::Draw()
{
	if (!m_isExist) return;

	// 中央座標を左上座標に変換
	int x = static_cast<int>(m_pos.x - kWidth * 0.5);
	int y = static_cast<int>(m_pos.y - kHeight * 0.5);

	// スクロール量を反映する
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	if (m_vec.x > 0)
	{
		DrawGraph(x, y, m_handle, true);
	}
	else
	{
		DrawTurnGraph(x, y, m_handle, true);
	}

#ifdef _DEBUG
	// MEMO:スクロールが反映されないためコメントアウト
	// 弾の当たり判定デバッグ表示
	//m_colRect.Draw(0xff0000, false);
#endif
}

void ShotLineMove::Start(Vec2 pos)
{
	m_isExist = true;

	// 初期位置の設定
	if (m_pPlayer->GetDir()) // プレイヤーが右を向いている場合
	{
		m_pos.x = pos.x + 20;
		// 1フレームあたりの移動ベクトルを決定する
		m_vec.x = kSpeed;
	}
	else // プレイヤーが左を向いている場合
	{
		m_pos.x = pos.x - 20;
		// 1フレームあたりの移動ベクトルを決定する
		m_vec.x = -kSpeed;
	}
	m_pos.y = (pos.y + kHeight / 2);

	// アイテム2号を静止する時間
	m_stopFrame = 150;
}
