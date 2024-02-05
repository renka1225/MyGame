#include "EnemyCat.h"
#include "Bg.h"
#include "Player.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// 敵のサイズ
	constexpr int kWidth = 64;
	constexpr int kHeight = 38;

	// エフェクトのサイズ
	constexpr int kEffectWidth = 32;
	constexpr int kEffectHeight = 32;

	// 拡大率
	constexpr float kEnlarge = 1.3f;
	constexpr float kEffectScale = 7.0f;

	// 移動速度
	constexpr float kSpeedX = 3.0f;
	constexpr float kSpeedY = 10.0f;
	// 最大HP
	constexpr int kHp = 3;

	// 敵アニメーション
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


EnemyCat::EnemyCat() :
	m_walkAnimFrame(0)
{
	m_handle = LoadGraph("data/image/Enemy/cat.png");
}

EnemyCat::~EnemyCat()
{
	DeleteGraph(m_handle);
}

void EnemyCat::Init(Bg* pBg, Player* pPlayer)
{
	m_pBg = pBg;
	m_pPlayer = pPlayer;
	m_hp = kHp;
	m_isDead = false;
}

void EnemyCat::Update()
{
	// 存在しない敵の処理はしない
	if (!m_isExist) return;

	// マップチップとの当たり判定
	Rect chipRect; // 当たったマップチップの矩形
	HitCollision(chipRect);

	// 地面から落ちないようにする
	if (m_pos.x > m_startPos.x + m_moveRangeX)
	{
		m_vec.x *= -1;
		m_dir = kDirLeft;
	}
	else if (m_pos.x < m_startPos.x - m_moveRangeX)
	{
		m_vec.x *= -1;
		m_dir = kDirRight;
	}

	// 移動アニメーション
	m_walkAnimFrame++;
	if (m_walkAnimFrame >= kAnimFrameCycle)
	{
		m_walkAnimFrame = 0;
	}

	// ダメージエフェクト
	m_damageFrame--;
	if (m_damageFrame < 0)
	{
		m_damageFrame = 0;
	}
}

void EnemyCat::Draw()
{
	// 中央座標を左上座標に変換
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// スクロール量を反映する
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// ダメージ演出
	// 10フレーム間隔で表示非表示を切り替える
	if (m_damageFrame % 10 >= 7) return;

	// 猫表示
	// 画像の切り出し座標
	int animFrame = m_walkAnimFrame / kAnimFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;
	DrawRectRotaGraph(x, y, srcX, srcY, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);

	// 消滅時ダメージエフェクト表示
	if (m_isDead)
	{
		// 画像の切り出し座標
		int effectFrame = m_damageFrame / kEffectFrameNum;
		int effectSrcX = kUseFrame[effectFrame] * kEffectWidth;
		int effectSrcY = 0;
		if (m_damageFrame > 0)
		{
			DrawRectRotaGraph(x + 10, y, effectSrcX, effectSrcY, kEffectWidth, kEffectHeight, kEffectScale, 0.0f, m_damageEffect, true);
		}
	}

#ifdef _DEBUG
	// スクロールが反映されないためコメントアウト
	// 当たり判定の表示
	// m_colRect.Draw(0x00ff00, false);
#endif
}

void EnemyCat::Start(float posX, float posY, float moveRangeX)
{
	// 敵キャラクターを登場させる
	m_isExist = true;

	m_pos = { posX, posY };
	m_startPos = { posX, posY };
	m_vec.x = -kSpeedX;
	m_vec.y = kSpeedY;
	m_moveRangeX = moveRangeX;
}

void EnemyCat::HitCollision(Rect chipRect)
{
	// 横から当たったかチェックする
	m_pos.x += m_vec.x;	// 現在位置の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth * kEnlarge), static_cast<float>(kHeight * kEnlarge)); // 当たり判定を生成
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.x > 0.0f) // 右に移動中
		{
			m_pos.x = chipRect.GetLeft() - kWidth * kEnlarge * 0.5f - 1;
			m_vec.x *= -1;
			m_dir = kDirLeft;

		}
		else if (m_vec.x < 0.0f) // 左に移動中
		{
			m_pos.x = chipRect.GetRight() + kWidth * kEnlarge * 0.5f + 1;
			m_vec.x *= -1;
			m_dir = kDirRight;
		}
	}

	// 縦から当たったかチェックする
	m_pos.y += m_vec.y; 	// 現在位置の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth * kEnlarge), static_cast<float>(kHeight * kEnlarge)); // 当たり判定を生成
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kHeight * kEnlarge * 0.5f - 1;
		}
	}
}

void EnemyCat::OnDamage()
{
	// ダメージ演出中は再度食らわない
	if (m_damageFrame > 0) return;
	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;

	// 現在のHPを減らす
	if (m_pPlayer->IsMiddleFire())
	{
		m_hp -= 3;
	}
	else if (m_pPlayer->IsBigFire())
	{
		m_hp -= 5;
	}
	else
	{
		m_hp--;
	};

	// SEを鳴らす
	PlaySoundMem(m_damageSE, DX_PLAYTYPE_BACK, true);

	// HPが0以下になったら存在を消す
	if (m_hp <= 0)
	{
		m_isDead = true;
		m_isExist = false;
	}
}
