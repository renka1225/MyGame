#include "EnemyCat.h"
#include "Bg.h"
#include "Player.h"
#include "Game.h"
#include "DxLib.h"

/// <summary>
/// 定数
/// </summary>
namespace
{
	/*猫の情報*/
	// 移動速度
	constexpr float kSpeedX = 3.0f;
	constexpr float kSpeedY = 10.0f;
	// 最大HP
	constexpr float kHp = 2.0f;

	// 敵のサイズ
	constexpr int kWidth = 60;
	constexpr int kHeight = 36;
	// 拡大率
	constexpr float kEnlarge = 1.3f;

	// ダメージ量
	constexpr int kMiddleDamage = 3; // 中ダメージ
	constexpr int kBigDamage = 5; // 大ダメージ

	// 位置調整
	constexpr float kColSizeAdjustment = 0.5f;
	constexpr float kPosAdjustment = 1.0f;

	/*アニメーション*/
	constexpr int kUseFrame[] = { 0, 1, 2, 3 };
	// アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 8;
	// アニメーション1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
	// ダメージアニメーション
	constexpr int kdamageFrame[] = { 0, 1, 2, 3 };
	// ダメージ演出フレーム数
	constexpr int kDamageFrame = 20;


	/*エフェクト*/
	// エフェクトのサイズ
	constexpr int kEffectWidth = 32;
	constexpr int kEffectHeight = 32;
	// エフェクトの拡大率
	constexpr float kEffectScale = 3.0f;
	// エフェクトのアニメーション1コマのフレーム数
	constexpr int kEffectFrameNum = 40;
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

/// <summary>
/// 初期化
/// </summary>
/// <param name="pBg">背景クラスのポインタ</param>
/// <param name="pPlayer">プレイヤークラスのポインタ</param>
void EnemyCat::Init(Bg* pBg, Player* pPlayer)
{
	m_pBg = pBg;
	m_pPlayer = pPlayer;
	m_hp = kHp;
	m_isDead = false;
}


/// <summary>
/// 更新
/// </summary>
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
	if (m_walkAnimFrame >= kAnimFrameCycle) m_walkAnimFrame = 0;

	// ダメージエフェクト
	m_damageFrame--;
	if (m_damageFrame < 0) m_damageFrame = 0;
}


/// <summary>
/// 描画
/// </summary>
void EnemyCat::Draw()
{
	// 中央座標を左上座標に変換
	int x = static_cast<int>(m_pos.x - kWidth * 0.5);
	int y = static_cast<int>(m_pos.y - kHeight * 0.5);

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
			DrawRectRotaGraph(x + 10, y, 
				effectSrcX, effectSrcY, 
				kEffectWidth, kEffectHeight, 
				kEffectScale, 0.0f, 
				m_damageEffect, true);
		}
	}

#ifdef _DEBUG
	// スクロールが反映されないためコメントアウト
	// 当たり判定の表示
	// m_colRect.Draw(0x00ff00, false);
#endif
}


/// <summary>
/// 生成時の処理
/// </summary>
/// <param name="posX">初期位置のX座標</param>
/// <param name="posY">初期位置のY座標</param>
/// <param name="moveRangeX">移動量</param>
void EnemyCat::Start(float posX, float posY, float moveRangeX)
{
	m_isExist = true;

	m_pos = { posX, posY };
	m_startPos = { posX, posY };
	m_vec.x = -kSpeedX;
	m_vec.y = kSpeedY;
	m_moveRangeX = moveRangeX;
}


/// <summary>
/// マップチップとの当たり判定
/// </summary>
/// <param name="chipRect">マップチップの当たり判定</param>
void EnemyCat::HitCollision(Rect chipRect)
{
	// 横から当たったかチェックする
	m_pos.x += m_vec.x;
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth * kEnlarge), static_cast<float>(kHeight * kEnlarge)); // 当たり判定を生成

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
		if (m_vec.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kHeight * kEnlarge * kColSizeAdjustment - kPosAdjustment;
		}
	}
}

/// <summary>
/// ダメージ処理
/// </summary>
void EnemyCat::OnDamage()
{
	// ダメージ演出中は再度食らわない
	if (m_damageFrame > 0) return;
	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;

	// 現在のHPを減らす
	if (m_pPlayer->IsMiddleFire())
	{
		m_hp -= kMiddleDamage;
	}
	else if (m_pPlayer->IsBigFire())
	{
		m_hp -= kBigDamage;;
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
