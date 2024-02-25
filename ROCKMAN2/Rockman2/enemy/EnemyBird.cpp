#include "EnemyBird.h"
#include "Bg.h"
#include "Player.h"
#include "Game.h"
#include "DxLib.h"
#include <cmath>

/// <summary>
/// 定数
/// </summary>
namespace
{
	/*鳥の情報*/
	// 移動速度
	constexpr float kSpeedX = 1.0f;
	constexpr float kSpeedY = 10.0f;
	constexpr float kSinSpeed = 0.05f;
	constexpr float kAnimationSize = 3.0f;

	// 最大HP
	constexpr float kHp = 1.0f;

	// サイズ
	constexpr int kWidth = 16;
	constexpr int kHeight = 16;
	// 拡大率
	constexpr float kEnlarge = 3.4f;

	// 位置調整
	constexpr float kColSizeAdjustment = 0.5f;
	constexpr float kPosAdjustment = 1.0f;

	/*アニメーション*/
	constexpr int kUseFrame[] = { 0, 1, 2, 3 };
	// アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 8;
	// アニメーション1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
	// ダメージ
	constexpr int kdamageFrame[] = { 0, 1, 2, 3 };
	// ダメージ演出フレーム数
	constexpr int kDamageFrame = 60;

	/*エフェクト*/
	// エフェクトのサイズ
	constexpr int kEffectWidth = 32;
	constexpr int kEffectHeight = 32;
	// アニメーション1コマのフレーム数
	constexpr int kEffectFrameNum = 40;
	//拡大率
	constexpr float kEffectScale = 5.0f;
}


EnemyBird::EnemyBird():
	m_flyAnimFrame(0),
	m_sinCount(0.0f)
{
	m_handle = LoadGraph("data/image/Enemy/bird.png");
}


EnemyBird::~EnemyBird()
{
	DeleteGraph(m_handle);
}


/// <summary>
/// 初期化
/// </summary>
/// <param name="pBg">背景クラスのポインタ</param>
/// <param name="pPlayer">プレイヤークラスのポインタ</param>
void EnemyBird::Init(Bg* pBg, Player* pPlayer)
{
	m_pBg = pBg;
	m_pPlayer = pPlayer;
	m_hp = kHp;
	m_sinCount = 0;
	m_isDead = false;
}


/// <summary>
/// 更新
/// </summary>
void EnemyBird::Update()
{
	// 存在しない敵の処理はしない
	if (!m_isExist) return;

	// マップチップとの当たり判定
	Rect chipRect; // 当たったマップチップの矩形
	HitCollision(chipRect);

	// 移動
	m_sinCount += kSinSpeed;
	m_vec.y = sinf(m_sinCount) * kAnimationSize;

	// 左右移動するようにする
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
	m_flyAnimFrame++;
	if (m_flyAnimFrame >= kAnimFrameCycle) m_flyAnimFrame = 0;

	// ダメージエフェクト
	m_damageFrame--;
	if (m_damageFrame < 0) m_damageFrame = 0;
}


/// <summary>
/// 描画
/// </summary>
void EnemyBird::Draw()
{
	// 中央座標を左上座標に変換
	int x = static_cast<int>(m_pos.x - kWidth * 0.5);
	int y = static_cast<int>(m_pos.y - kHeight * 0.5);

	// スクロール量を反映する
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// 鳥表示
	// 画像の切り出し座標
	int animFrame = m_flyAnimFrame / kAnimFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;

	DrawRectRotaGraph(x, y,
		srcX, srcY,
		kWidth, kHeight, 
		kEnlarge, 0.0f,
		m_handle, true);

	// 消滅時ダメージエフェクト表示
	if (m_isDead)
	{
		// 画像の切り出し座標
		int effectFrame = m_damageFrame / kEffectFrameNum;
		int effectSrcX = kUseFrame[effectFrame] * kEffectWidth;
		int effectSrcY = 0;
		if (m_damageFrame > 0)
		{
			DrawRectRotaGraph(x , y,
				effectSrcX, effectSrcY,
				kEffectWidth, kEffectHeight, 
				kEffectScale, 0.0f, 
				m_damageEffect, true);
		}
	}

#ifdef _DEBUG
	// スクロールが反映されないためコメントアウト
	// 当たり判定の表示
	//m_colRect.Draw(0x00ff00, false);
#endif
}


/// <summary>
/// 生成時の処理
/// </summary>
/// <param name="posX">初期位置のX座標</param>
/// <param name="posY">初期位置のY座標</param>
/// <param name="moveRangeX">移動量</param>
void EnemyBird::Start(float posX, float posY, float moveRangeX)
{
	m_isExist = true;

	m_pos = { posX, posY };
	m_startPos = { posX, posY };
	m_vec.x = -kSpeedX;
	m_vec.y = 0.0f;
	m_moveRangeX = moveRangeX;
}


/// <summary>
/// マップチップとの当たり判定
/// </summary>
/// <param name="chipRect">マップチップの当たり判定</param>
void EnemyBird::HitCollision(Rect chipRect)
{
	// 横から当たったかチェックする
	m_pos.x += m_vec.x;
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth), static_cast<float>(kHeight)); // 当たり判定を生成

	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.x > 0.0f) // 右に移動中
		{
			m_pos.x = chipRect.GetLeft() - kWidth * kEnlarge * kColSizeAdjustment - kPosAdjustment;
			m_vec.x *= -1;
			m_dir = kDirLeft;
		}
		else if (m_vec.x < 0.0f) // 左に移動中
		{
			m_pos.x = chipRect.GetRight() + kWidth * kEnlarge * kColSizeAdjustment + kPosAdjustment;
			m_vec.x *= -1;
			m_dir = kDirRight;
		}
	}

	// 縦から当たったかチェックする
	m_pos.y += m_vec.y;
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth * kEnlarge), static_cast<float>(kHeight * kEnlarge)); // 当たり判定を生成

	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.y > 0.0f && m_vec.x == 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kHeight * kEnlarge * kColSizeAdjustment - kPosAdjustment;
			m_vec.y *= -1;
		}
		else if (m_vec.y < 0.0f && m_vec.x == 0.0f)
		{
			m_pos.y = chipRect.GetBottom() + kHeight * kEnlarge * kColSizeAdjustment + kPosAdjustment;
			m_vec.y *= -1;
		}
	}
}

/// <summary>
/// ダメージ時の処理
/// </summary>
void EnemyBird::OnDamage()
{
	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;

	// 弾が当たったらHPを減らす
	m_hp--;

	// SEを鳴らす
	PlaySoundMem(m_damageSE, DX_PLAYTYPE_BACK, true);

	// HPが0以下になったら存在を消す
	if (m_hp <= 0)
	{
		m_isExist = false;
		m_isDead = true;
	}
}
