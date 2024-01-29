#include "EnemyBird.h"
#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// 敵のサイズ
	constexpr int kWidth = 16;
	constexpr int kHeight = 16;

	// エフェクトのサイズ
	constexpr int kEffectWidth = 32;
	constexpr int kEffectHeight = 32;

	// 拡大率
	constexpr float kEnlarge = 3.0f;
	constexpr float kEffectScale = 7.0f;

	// 移動速度
	constexpr float kSpeed = 3.0f;
	// 最大HP
	constexpr int kHp = 1;

	// アニメーション
	constexpr int kUseFrame[] = { 0, 1, 2, 3 };
	// アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 8;
	// アニメーション1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	// エフェクト
	constexpr int kdamageFrame[] = { 0, 1, 2, 3 };
	// アニメーション1コマのフレーム数
	constexpr int kEffectFrameNum = 8;
	// ダメージ演出フレーム数
	constexpr int kDamageFrame = 60;
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
	m_hp = kHp;
	m_isDead = false;
}

void EnemyBird::Update()
{
	// 存在しない敵の処理はしない
	if (!m_isExist) return;

	// マップチップとの当たり判定
	Rect chipRect; // 当たったマップチップの矩形
	HitCollision(chipRect);

	// 移動アニメーション
	m_flyAnimFrame++;
	if (m_flyAnimFrame >= kAnimFrameCycle)
	{
		m_flyAnimFrame = 0;
	}

	// ダメージエフェクト
	m_damageFrame--;
	if (m_damageFrame < 0)
	{
		m_damageFrame = 0;
	}
}

void EnemyBird::Draw()
{
	// 中央座標を左上座標に変換
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// スクロール量を反映する
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// 鳥表示
	// 画像の切り出し座標
	int animFrame = m_flyAnimFrame / kAnimFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;

	DrawRectRotaGraph(x, y, srcX, srcY, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);

	// ダメージエフェクト表示
	// 画像の切り出し座標
	int effectFrame = m_damageFrame / kEffectFrameNum;
	int effectSrcX = kUseFrame[animFrame] * kEffectWidth;
	int effectSrcY = kHeight;
	if (m_damageFrame > 0)
	{
		DrawRectRotaGraph(x, y, effectSrcX, effectSrcY, kEffectWidth, kEffectHeight, kEnlarge, 0.0f, m_damageEffect, true);
	}

	// 消滅時ダメージエフェクト表示
	if (m_isDead)
	{
		// 画像の切り出し座標
		int effectFrame = m_damageFrame / kEffectFrameNum;
		int effectSrcX = kUseFrame[effectFrame] * kEffectWidth;
		int effectSrcY = 0;
		if (m_damageFrame > 0)
		{
			DrawRectRotaGraph(x , y, effectSrcX, effectSrcY, kEffectWidth, kEffectHeight, kEffectScale, 0.0f, m_damageEffect, true);
		}
	}

#ifdef _DEBUG
	// スクロールが反映されないためコメントアウト
	// 当たり判定の表示
	//m_colRect.Draw(0x00ff00, false);
#endif
}

void EnemyBird::Start(float posX, float posY)
{
	// 敵キャラクターを登場させる
	m_isExist = true;

	m_pos = { posX, posY };
	m_vec.x -= kSpeed;
}

void EnemyBird::HitCollision(Rect chipRect)
{
	// 横から当たったかチェックする
	m_pos.x += m_vec.x;	// 現在位置の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth), static_cast<float>(kHeight)); // 当たり判定を生成
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.x > 0.0f) // 右に移動中
		{
			m_pos.x = chipRect.GetLeft() - kWidth * 0.5f - 1;
			m_vec.x *= -1;
			m_dir = kDirLeft;

		}
		else if (m_vec.x < 0.0f) // 左に移動中
		{
			m_pos.x = chipRect.GetRight() + kWidth * 0.5f + 1;
			m_vec.x *= -1;
			m_dir = kDirRight;
		}
	}

	// 縦から当たったかチェックする
	m_pos.y += m_vec.y; 	// 現在位置の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth), static_cast<float>(kHeight)); // 当たり判定を生成
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kHeight * 0.5f - 1;
		}
	}
}

void EnemyBird::OnDamage()
{
	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;

	// 弾が当たったらHPを減らす
	m_hp--;

	// HPが0以下になったら存在を消す
	if (m_hp <= 0)
	{
		m_isExist = false;
		m_isDead = true;
	}
}
