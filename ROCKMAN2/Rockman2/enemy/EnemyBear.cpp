#include "EnemyBear.h"
#include "Bg.h"
#include "Player.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// 敵のサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// エフェクトのサイズ
	constexpr int kEffectWidth = 32;
	constexpr int kEffectHeight = 32;

	// 拡大率
	constexpr float kEnlarge = 8.0f;
	constexpr float kEffectScale = 5.0f;

	// 当たり判定のサイズ
	constexpr float kColWidth = 20.0f * kEnlarge;
	constexpr float kColHeight = 12.0f * kEffectScale;

	// 移動速度
	constexpr float kSpeedX = 5.0f;
	constexpr float kSpeedY = 10.0f;
	// 最大HP
	constexpr int kHp = 15;

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
	constexpr int kRunAnimFrameNum = 18;
	// アニメーション1サイクルのフレーム数
	constexpr int kRunAnimFrameCycle = _countof(kRunUseFrame) * kRunAnimFrameNum;

	/*回復アニメーション*/
	// アニメーション
	constexpr int kRecUseFrame[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	// アニメーション1コマのフレーム数
	constexpr int kRecAnimFrameNum = 30;
	// アニメーション1サイクルのフレーム数
	constexpr int kRecAnimFrameCycle = _countof(kRecUseFrame) * kRecAnimFrameNum;


	/*エフェクト*/
	constexpr int kDamageUseFrame[] = { 0, 1, 2, 3 };
	// アニメーション1コマのフレーム数
	constexpr int kEffectFrameNum = 16;
	// ダメージ演出フレーム数
	constexpr int kDamageFrame = 60;
}


EnemyBear::EnemyBear() :
	m_animation(kIdle),
	m_idleAnimFrame(0),
	m_runAnimFrame(0),
	m_recoveryAnimFrame(0)
{
	m_handle = LoadGraph("data/image/Enemy/bear.png");
}

EnemyBear::~EnemyBear()
{
	DeleteGraph(m_handle);
}

void EnemyBear::Init(Bg* pBg, Player* pPlayer)
{
	m_pBg = pBg;
	m_pPlayer = pPlayer;
	m_hp = kHp;
	m_isDead = false;
	m_animation = kIdle;
	m_dir = kDirLeft;
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
	float kDis = m_pos.x - m_pPlayer->GetPos().x;
	// プレイヤーが近づいたら突進する
	if(kDis <= 300.0f && kDis > -0.0f) // プレイヤーが左から近づいた場合
	{
		m_animation = kRun;
		m_dir = kDirLeft;
		m_vec.x = -kSpeedX;
	}
	if (kDis >= -300.0f && kDis < 0.0f)	// プレイヤーが右から近づいた場合
	{
		m_animation = kRun;
		m_dir = kDirRight;
		m_vec.x = kSpeedX;
	}
	if(fabsf(kDis) > 300.0f)
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
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// スクロール量を反映する
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// ダメージ演出
	// 10フレーム間隔で表示非表示を切り替える
	if (m_damageFrame % 10 >= 5) return;

	// 熊表示
	DrawBear(x, y);

	// 消滅時ダメージエフェクト表示
	if (m_isDead)
	{
		// 画像の切り出し座標
		int effectFrame = m_damageFrame / kEffectFrameNum;
		int effectSrcX = kDamageUseFrame[effectFrame] * kEffectWidth;
		int effectSrcY = 0;
		if (m_damageFrame > 0)
		{
			DrawRectRotaGraph(x - 10, y, effectSrcX, effectSrcY, kEffectWidth, kEffectHeight, kEffectScale, 0.0f, m_damageEffect, true);
		}
	}

#ifdef _DEBUG
	// スクロールが反映されないためコメントアウト
	// 当たり判定の表示
	m_colRect.Draw(0x00ff00, false);
#endif
}

/// <summary>
/// 敵出現
/// </summary>
/// <param name="posX">現在地</param>
/// <param name="posY">現在地</param>
/// <param name="moveRangeX">移動量</param>
void EnemyBear::Start(float posX, float posY, float moveRangeX)
{
	// 敵キャラクターを登場させる
	m_isExist = true;

	m_pos = { posX, posY };
	m_startPos = { posX, posY };
	m_vec = {kSpeedX, kSpeedY};
	m_moveRangeX = moveRangeX;
}

/// <summary>
/// マップチップとの当たり判定
/// </summary>
/// <param name="chipRect"></param>
void EnemyBear::HitCollision(Rect chipRect)
{
	// 横から当たったかチェックする
	m_pos.x += m_vec.x;	// 現在位置の更新
	m_colRect.SetCenter(m_pos.x , m_pos.y, kColWidth, kColHeight); // 当たり判定を生成
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.x > 0.0f) // 右に移動中
		{
			m_pos.x = chipRect.GetLeft() - kColWidth - 1.0f;
			m_vec.x *= -1;
			m_dir = kDirLeft;

		}
		else if (m_vec.x < 0.0f) // 左に移動中
		{
			m_pos.x = chipRect.GetRight() + kColWidth + 1.0f;
			m_vec.x *= -1;
			m_dir = kDirRight;
		}
	}

	// 縦から当たったかチェックする
	m_pos.y += m_vec.y; 	// 現在位置の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y , kColWidth, kColHeight); // 当たり判定を生成
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kColHeight + 30.0f - 1.0f;
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
		m_hp -= 3;
	}
	else if (m_pPlayer->IsBigFire())
	{
		m_hp -= 5;
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
/// アニメーションの処理
/// </summary>
void EnemyBear::UpdateAnim()
{
	// 移動アニメーション
	m_idleAnimFrame++;
	if (m_idleAnimFrame >= kIdleAnimFrameCycle)
	{
		m_idleAnimFrame = 0;
	}
	// 突進アニメーション
	m_runAnimFrame++;
	if (m_runAnimFrame >= kRunAnimFrameCycle)
	{
		m_runAnimFrame = 0;
	}
	// 回復アニメーション
	m_idleAnimFrame++;
	if (m_recoveryAnimFrame >= kRecAnimFrameCycle)
	{
		m_recoveryAnimFrame = 0;
	}
	// ダメージエフェクト
	m_damageFrame--;
	if (m_damageFrame < 0)
	{
		m_damageFrame = 0;
	}
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
		DrawRectRotaGraph(x, y - 80, idleSrcX, idleSrcY, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);
	}
	// 突進状態
	else if (m_animation == Anim::kRun)
	{
		DrawRectRotaGraph(x, y - 80, runSrcX, runSrcY, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);
	}
	// 回復状態
	else if (m_animation == Anim::kRecovery)
	{
		DrawRectRotaGraph(x, y - 80, recSrcX, recSrcY, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);
	}

}