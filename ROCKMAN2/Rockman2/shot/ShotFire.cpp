#include "ShotFire.h"
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
	constexpr float kSmallScale = 0.5f;
	constexpr float kMiddleScale = 0.8f;
	constexpr float kBigScale = 1.2f;
}

ShotFire::ShotFire()
{
	// 画像読み込み
	m_fire1Handle = LoadGraph("data/image/Shot/shotFire.png");
	m_fire2Handle = LoadGraph("data/image/Shot/shotFire2.png");
	m_fire3Handle = LoadGraph("data/image/Shot/shotFire3.png");
}

ShotFire::~ShotFire()
{
	DeleteGraph(m_fire1Handle);
	DeleteGraph(m_fire2Handle);
	DeleteGraph(m_fire3Handle);
}

void ShotFire::Init()
{
}

void ShotFire::Update()
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
	if (m_pos.x < m_pPlayer->GetPos().x - Game::kScreenWidth * 0.5f) isOut = true; // 画面左端
	if (m_pos.x > m_pPlayer->GetPos().x + Game::kScreenWidth * 0.5f) isOut = true; // 画面右端

	// チェック中の座標が画面内ならここで終了
	if (!isOut) return;

	// ここに来たということは画面外にいる
	m_isExist = false;
}

void ShotFire::Draw()
{
	if (!m_isExist) return;

	// 中央座標を左上座標に変換
	int x = static_cast<int>(m_pos.x - kWidth * 0.5);
	int y = static_cast<int>(m_pos.y - kHeight * 0.5);

	// スクロール量を反映する
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// 弾の表示
	if (m_pPlayer->IsSmallFire()) // 長押し時間が2秒以下
	{
		DrawRectRotaGraph(x, y, 0, 0, kWidth, kHeight, kSmallScale, 0.0f, m_fire1Handle, true);
	}
	else if (m_pPlayer->IsMiddleFire()) // 長押し時間が5秒以下
	{
		
		DrawRectRotaGraph(x, y, 0, 0, kWidth, kHeight, kMiddleScale, 0.0f, m_fire2Handle, true);
		
	}
	else // 長押し時間が5秒以上
	{
		DrawRectRotaGraph(x, y, 0, 0, kWidth, kHeight, kBigScale, 0.0f, m_fire3Handle, true);
	}

#ifdef _DEBUG
	// MEMO:スクロールが反映されないためコメントアウト
	// 弾の当たり判定デバッグ表示
	//m_colRect.Draw(0xff0000, false);
#endif
}

void ShotFire::Start(Vec2 pos)
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
