#include "EnemyBear.h"
#include "Bg.h"
#include "Player.h"
#include "Game.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	/*熊の状態*/
	// 移動速度
	constexpr float kSpeedX = 4.0f;
	constexpr float kSpeedY = 10.0f;
	// 最大HP
	constexpr float kHp = 10.0f;

	// ダメージ量
	constexpr int kMiddleDamage = 3; // 中ダメージ
	constexpr int kBigDamage = 5; // 大ダメージ
	// 回復量
	constexpr float kRecovery = 0.03f;
	// 回復時間
	constexpr float kRecoveryFrame = 30.0f;
	// 回復間隔
	constexpr float kRecoveryIntervalFrame = 120.0f;

	// 敵のサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
	// 拡大率
	constexpr float kEnlarge = 8.0f;
	
	// 当たり判定のサイズ
	constexpr float kColWidth = 20.0f * kEnlarge;
	constexpr float kColHeight = 12.0f * 5.0f;

	// 描画位置調整
	constexpr int kDrawAdjustment = 80;
	// 当たり判定の位置調整
	constexpr float kColAdjustmentX = 1.0f;
	constexpr float kColAdjustmentY = 29.0f;

	// 突進位置
	constexpr float kRunMinPosX = 10.0f;
	constexpr float kRunMaxPosX = 430.0f;

	// 回復位置
	constexpr float kRecoveryMinPosX = 430.0f;
	constexpr float kRecoveryMaxPosX = 1000.0f;
	constexpr float kRecoveryPosY = 100.0f;


	/*待機アニメーション*/
	// アニメーション
	constexpr int kIdleUseFrame[] = { 0, 1, 2, 3 };
	// アニメーション1コマのフレーム数
	constexpr int kIdleAnimFrameNum = 20;
	// アニメーション1サイクルのフレーム数
	constexpr int kIdleAnimFrameCycle = _countof(kIdleUseFrame) * kIdleAnimFrameNum;

	/*突進アニメーション*/
	// アニメーション
	constexpr int kRunUseFrame[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	// アニメーション1コマのフレーム数
	constexpr int kRunAnimFrameNum = 36;
	// アニメーション1サイクルのフレーム数
	constexpr int kRunAnimFrameCycle = _countof(kRunUseFrame) * kRunAnimFrameNum;

	/*回復アニメーション*/
	// アニメーション
	constexpr int kRecUseFrame[] = { 0, 1, 2, 3, 4, 5};
	// アニメーション1コマのフレーム数
	constexpr int kRecAnimFrameNum = 40;
	// アニメーション1サイクルのフレーム数
	constexpr int kRecAnimFrameCycle = _countof(kRecUseFrame) * kRecAnimFrameNum;

	/*エフェクト*/
	// 回復
	// エフェクトのサイズ
	constexpr int kRecEffectSize = 256;
	// エフェクトの表示フレーム
	constexpr int kRecEffectFrame = 30;
	// エフェクトの数
	constexpr int kRecEffectNum = 35;

	// ダメージ
	constexpr int kDamageUseFrame[] = { 0, 1, 2, 3 };
	// アニメーション1コマのフレーム数
	constexpr int kEffectFrameNum = 32;
	// ダメージ演出フレーム数
	constexpr int kDamageFrame = 60;

	// 死亡
	// エフェクトのサイズ
	constexpr int kEffectWidth = 32;
	constexpr int kEffectHeight = 32;
	constexpr float kEffectScale = 5.0f;

	// エフェクトの表示位置調整
	constexpr int kEffectAdjustmentX = 10;
	constexpr int kEffectAdjustmentY = 50;

	// SEを鳴らす位置
	constexpr float kSoundSE = 6048.0f;
}


EnemyBear::EnemyBear() :
	m_recoveryFrame(kRecoveryFrame),
	m_recoveryIntervalFrame(kRecoveryIntervalFrame),
	m_recoveryEffectFrame(0),
	m_animation(kIdle),
	m_idleAnimFrame(0),
	m_runAnimFrame(0),
	m_recoveryAnimFrame(0)
{
	m_handle = LoadGraph("data/image/Enemy/bear.png");
	m_recoveryEffect = LoadGraph("data/image/Effect/recovery.png");
	m_recoverySE = LoadSoundMem("data/Sound/SE/recovery.mp3");
	assert(m_recoveryEffect);
}

EnemyBear::~EnemyBear()
{
	DeleteGraph(m_handle);
	DeleteGraph(m_recoveryEffect);
	DeleteSoundMem(m_recoverySE);
}

void EnemyBear::Init(Bg* pBg, Player* pPlayer)
{
	m_pBg = pBg;
	m_pPlayer = pPlayer;
	m_hp = kHp;
	m_isDead = false;
	m_dir = kDirLeft;
	m_recoveryFrame = kRecoveryFrame;
	m_recoveryIntervalFrame = kRecoveryIntervalFrame;
	m_recoveryEffectFrame = 0;
	m_animation = kIdle;
	m_idleAnimFrame = 0;
	m_runAnimFrame = 0;
	m_recoveryAnimFrame = 0;
}

void EnemyBear::Update()
{
	// 存在しない敵の処理はしない
	if (!m_isExist) return;

	// マップチップとの当たり判定
	Rect chipRect; // 当たったマップチップの矩形
	HitCollision(chipRect);

	/*移動*/
	// 左右移動を行う
	if (m_pos.x > m_startPos.x + m_moveRangeX)
	{
		m_vec.x *= -1;
		m_dir = kDirRight;
	}
	else if (m_pos.x < m_startPos.x - m_moveRangeX)
	{
		m_vec.x *= -1;
		m_dir = kDirLeft;
	}

	// プレイヤーと熊の距離
	float kDisX = m_pos.x - m_pPlayer->GetPos().x;
	float kDisY = m_pos.y - m_pPlayer->GetPos().y;
	// プレイヤーが近づいたら突進する
	if(kDisX <= kRunMaxPosX && kDisX > kRunMinPosX) // プレイヤーが左から近づいた場合
	{
		m_animation = kRun;
		m_dir = kDirLeft;
		m_vec.x = -kSpeedX;
	}
	else if (kDisX >= -kRunMaxPosX && kDisX < -kRunMinPosX)	// プレイヤーが右から近づいた場合
	{
		m_animation = kRun;
		m_dir = kDirRight;
		m_vec.x = kSpeedX;
	}
	// プレイヤーが離れたら回復する
	else if (fabsf(kDisX) > kRecoveryMinPosX && fabsf(kDisX) < kRecoveryMaxPosX || fabsf(kDisY) > kRecoveryPosY)
	{
		m_animation = kRecovery;
		m_vec.x = 0.0f;
		UpdateRecovery();
	}
	else
	{
		m_animation = kIdle;
		m_vec.x = 0.0f;
	}

	/*アニメーション*/
	UpdateAnim();
}

void EnemyBear::Draw()
{
	// 中央座標を左上座標に変換
	int x = static_cast<int>(m_pos.x - kWidth * 0.5);
	int y = static_cast<int>(m_pos.y - kHeight * 0.5);

	// スクロール量を反映する
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// ダメージ演出
	// 10フレーム間隔で表示非表示を切り替える
	if (m_damageFrame % 10 >= 5) return;

	// 熊表示
	DrawBear(x, y);

	// エフェクト表示
	DrawEffect(x, y);

#ifdef _DEBUG
	// スクロールが反映されないためコメントアウト
	// 当たり判定の表示
	//m_colRect.Draw(0x00ff00, false);

	// MEMO:熊の情報確認
	//printfDx("熊のHP:%f\n", m_hp);
	//printfDx("熊のアニメーション:%d\n", m_animation);
#endif // _DEBUG
}

/// <summary>
/// 敵出現
/// </summary>
/// <param name="posX">初期位置X座標</param>
/// <param name="posY">初期位置Y座標</param>
/// <param name="moveRangeX">移動量</param>
void EnemyBear::Start(float posX, float posY, float moveRangeX)
{
	m_isExist = true;

	m_pos = { posX, posY };
	m_startPos = { posX, posY };
	m_vec = {kSpeedX, kSpeedY};
	m_moveRangeX = moveRangeX;
}


/// <summary>
/// マップチップとの当たり判定
/// </summary>
/// <param name="chipRect">マップチップの当たり判定</param>
void EnemyBear::HitCollision(Rect chipRect)
{
	// 横から当たったかチェックする
	m_pos.x += m_vec.x;
	m_colRect.SetCenter(m_pos.x , m_pos.y, kColWidth, kColHeight); // 当たり判定を生成
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.x > 0.0f) // 右に移動中
		{
			m_pos.x = chipRect.GetLeft() - kColWidth - kColAdjustmentX;
			m_vec.x *= -1;
			m_dir = kDirLeft;
			m_animation = kIdle;

		}
		else if (m_vec.x < 0.0f) // 左に移動中
		{
			m_pos.x = chipRect.GetRight() + kColWidth + kColAdjustmentX;
			m_vec.x *= -1;
			m_dir = kDirRight;
			m_animation = kIdle;
		}
	}

	// 縦から当たったかチェックする
	m_pos.y += m_vec.y;
	m_colRect.SetCenter(m_pos.x, m_pos.y , kColWidth, kColHeight); // 当たり判定を生成
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kColHeight + kColAdjustmentY;
		}
	}
}


/// <summary>
/// ダメージ時
/// </summary>
void EnemyBear::OnDamage()
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
		m_hp -= kBigDamage;
	}
	else
	{
		m_hp--;
	}

	// SEを鳴らす
	PlaySoundMem(m_damageSE, DX_PLAYTYPE_BACK, true);

	// HPが0以下になったら存在を消す
	if (m_hp <= 0)
	{
		m_isExist = false;
		m_isDead = true;
	}
}


/// <summary>
/// 回復処理
/// </summary>
void EnemyBear::UpdateRecovery()
{
	m_recoveryIntervalFrame--;

	if (m_recoveryIntervalFrame < 0.0f)
	{
		m_recoveryFrame--;

		// 回復する
		if (m_recoveryFrame > 0.0f)
		{
			m_hp += kRecovery;
			if (m_hp >= kHp)
			{
				m_hp = kHp;
			}
			// 回復エフェクト
			m_recoveryEffectFrame += kRecEffectSize;
			if (m_recoveryEffectFrame >= kRecEffectSize * kRecEffectNum)
			{
				m_recoveryEffectFrame = 0;
			}
			//	回復SE
			if (CheckSoundMem(m_recoverySE) == 0 && m_pPlayer->GetPos().x > kSoundSE)
			{
				PlaySoundMem(m_recoverySE, DX_PLAYTYPE_BACK, true);
			}
		}
		else
		{
			m_recoveryFrame = kRecoveryFrame;
			m_recoveryIntervalFrame = kRecoveryIntervalFrame;
			m_animation = kIdle;
		}
	}
}


/// <summary>
/// アニメーションの処理
/// </summary>
void EnemyBear::UpdateAnim()
{
	// 移動アニメーション
	m_idleAnimFrame++;
	if (m_idleAnimFrame >= kIdleAnimFrameCycle) m_idleAnimFrame = 0;
	
	// 突進アニメーション
	m_runAnimFrame++;
	if (m_runAnimFrame >= kRunAnimFrameCycle) m_runAnimFrame = 0;
	
	// 回復アニメーション
	m_recoveryAnimFrame++;
	if (m_recoveryAnimFrame >= kRecAnimFrameCycle) m_recoveryAnimFrame = 0;

	// ダメージエフェクト
	m_damageFrame--;
	if (m_damageFrame < 0) 	m_damageFrame = 0;
}


/// <summary>
/// 熊の描画
/// </summary>
void EnemyBear::DrawBear(int x, int y)
{
	// 画像の切り出し座標
	// 待機状態
	int idleAnimFrame = m_idleAnimFrame / kIdleAnimFrameNum;
	int idleSrcX = kIdleUseFrame[idleAnimFrame] * kWidth;
	int idleSrcY = kHeight * m_dir;
	// 突進状態
	int runAnimFrame = m_runAnimFrame / kRunAnimFrameNum;
	int runSrcX = kRunUseFrame[runAnimFrame] * kWidth;
	int runSrcY = kHeight * (2 + m_dir);
	// 回復状態
	int recAnimFrame = m_recoveryAnimFrame / kRecAnimFrameNum;
	int recSrcX = kRecUseFrame[recAnimFrame] * kWidth;
	int recSrcY = kHeight * (4 + m_dir);

	// 待機状態
	if (m_animation == Anim::kIdle)
	{
		DrawRectRotaGraph(x, y - kDrawAdjustment,
			idleSrcX, idleSrcY, 
			kWidth, kHeight, 
			kEnlarge, 0.0f, 
			m_handle, true);
	}
	// 突進状態
	else if (m_animation == Anim::kRun)
	{
		DrawRectRotaGraph(x, y - kDrawAdjustment,
			runSrcX, runSrcY, 
			kWidth, kHeight, 
			kEnlarge, 0.0f, 
			m_handle, true);
	}
	// 回復状態
	else if (m_animation == Anim::kRecovery)
	{
		DrawRectRotaGraph(x, y - kDrawAdjustment,
			recSrcX, recSrcY, 
			kWidth, kHeight, 
			kEnlarge, 0.0f, 
			m_handle, true);
	}

}


/// <summary>
/// エフェクトの描画
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void EnemyBear::DrawEffect(int x, int y)
{
	// 回復エフェクト
	if (m_animation == kRecovery && m_recoveryFrame > 0.0f)
	{
		DrawRectRotaGraph(x , y - kEffectAdjustmentY,
			m_recoveryEffectFrame, 0, 
			kRecEffectSize, kRecEffectSize, 
			1.0f, 0.0f, 
			m_recoveryEffect, true);
	}

	// 死亡エフェクト
	if (m_isDead)
	{
		// 画像の切り出し座標
		int effectFrame = m_damageFrame / kEffectFrameNum;
		int effectSrcX = kDamageUseFrame[effectFrame] * kEffectWidth;
		int effectSrcY = 0;
		if (m_damageFrame > 0)
		{
			DrawRectRotaGraph(x - kEffectAdjustmentX, y,
				effectSrcX, effectSrcY, 
				kEffectWidth, kEffectHeight, 
				kEffectScale, 0.0f,
				m_damageEffect, true);
		}
	}
}
