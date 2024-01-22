#include "EnemyBird.h"
#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// 敵のサイズ
	constexpr int kWidth = 16;
	constexpr int kHeight = 16;
	// 拡大率
	constexpr float kEnlarge = 3.0f;

	// 移動速度
	constexpr float kSpeed = 7.0f;
	// 最大HP
	constexpr int kHp = 3;

	// アニメーション
	constexpr int kUseFrame[] = { 0, 1, 2, 3 };
	// アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 8;
	// アニメーション1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}


EnemyBird::EnemyBird():
	m_flyAnimFrame(0)
{
	m_handle = LoadGraph("data/image/Enemy/bird.png");
}

EnemyBird::~EnemyBird()
{
	DeleteGraph(m_handle);
}

void EnemyBird::Init()
{
}

void EnemyBird::Update()
{
	// 存在しない敵の処理はしない
		if (!m_isExist) return;

	// TODO:敵を左右に移動させる
	if (m_pos.x < 1200)
	{
		m_vec.x *= -1; // 右に移動
		m_dir = kDirRight;
	}
	else if (m_pos.x > 2000)
	{
		m_vec.x *= -1; // 左に移動
		m_dir = kDirLeft;
	}

	// 現在位置の更新
	m_pos += m_vec;

	// 当たり判定を生成
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth * 3), static_cast<float>(kHeight));

	// 移動アニメーション
	m_flyAnimFrame++;
	if (m_flyAnimFrame >= kAnimFrameCycle)
	{
		m_flyAnimFrame = 0;
	}

	// 画面外に出た処理
	bool isOut = false;	// チェック中の座標が画面外かどうかフラグ
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // 画面左端
	if (m_pos.x > Stage::kMapWidth) isOut = true; // 画面右端

	// 画面内ならここで終了
	if (!isOut) return;

	// 画面外に出たら終了する
	m_isExist = false;
}

void EnemyBird::Draw()
{
	// 中央座標を左上座標に変換
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// スクロール量を反映する
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// 画像の切り出し座標
	int animFrame = m_flyAnimFrame / kAnimFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;

	DrawRectRotaGraph(x, y, srcX, srcY, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);

#ifdef _DEBUG
	// スクロールが反映されないためコメントアウト
	// 当たり判定の表示
	//m_colRect.Draw(0x00ff00, false);
#endif
}

void EnemyBird::Start()
{
	// 敵キャラクターを登場させる
	m_isExist = true;

	m_pos = { 2000, 300 };
	m_vec.x -= kSpeed;
}

void EnemyBird::OnDamage()
{
	// 弾が当たったらHPを減らす
	m_hp--;

	// HPが0以下になったら存在を消す
	if (m_hp <= 0)
	{
		m_isExist = false;
	}
}
