#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "SceneMain.h"
#include "ShotBuster.h"
#include "ShotMetal.h"
#include "ShotFire.h"
#include <cassert>

// Playerで使用する定数
namespace
{
	// 移動速度
	constexpr float kSpeed = 3.0f;
	// ジャンプ速度
	constexpr float kJumpSpeed = -10.0f;
	// ジャンプの長さ
	constexpr float kJumpTime = 10.0f;
	// 落下速度
	constexpr float kFallSpeed = 8.0f;

	// プレイヤーのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 64;

	// 床の高さ
	constexpr int kFloorHeight = 300;
}


Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	m_pos(Game::kScreenWidth / 2, kFloorHeight),
	m_handle(-1),
	m_isRight(true),
	m_jumpFrame(0),
	m_isJumpFlag(false),
	m_hp(28),
	m_life(2),
	m_metalEnergy(28),
	m_fireEnergy(28),
	m_pressTime(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	// パッドの十字キーを使用してプレイヤーを移動させる
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	Vec2 move{ 0.0f, kFallSpeed }; // 移動量

	// ←を押したら左に移動
	if (pad & PAD_INPUT_LEFT)
	{
		//move.x -= kSpeed;
		m_isRight = false;

	}

	// →を押したら右に移動
	if (pad & PAD_INPUT_RIGHT)
	{
		//move.x += kSpeed;
		m_isRight = true;
	}

	// Spaceでジャンプ
	if (Pad::IsTrigger(PAD_INPUT_10))
	{
		if (!m_isJumpFlag && m_jumpFrame <= 0)
		{
			m_isJumpFlag = true;
			m_jumpFrame = kJumpTime; // ジャンプの長さ
			move.y = kJumpSpeed * kJumpTime;
		}
		else
		{
			move.y += kFallSpeed;	// 落下し続ける
			m_jumpFrame--;
		}
	}

	// Zキーでバスター発射
	if(Pad::IsTrigger(PAD_INPUT_1))
	{
		ShotBuster* pShot = new ShotBuster;

		// 新しい弾を生成する
		pShot->Init();
		pShot->SetMain(m_pMain);
		pShot->SetPlayer(this);
		pShot->Start(GetPos());
		// 以降更新やメモリの解放はSceneMainに任せる
		m_pMain->AddShot(pShot);
	}

	// Xキーでメタル発射
	if (Pad::IsTrigger(PAD_INPUT_2))
	{
		if (m_metalEnergy > 0)
		{
			// 弾エネルギーを0.25減らす
			m_metalEnergy -= 0.25f;

			ShotMetal* pShot = new ShotMetal;

			// 新しい弾を生成する
			pShot->Init();
			pShot->SetMain(m_pMain);
			pShot->SetPlayer(this);
			pShot->Start(GetPos());
			// 以降更新やメモリの解放はSceneMainに任せる
			m_pMain->AddShot(pShot);
		}
		else
		{
			m_metalEnergy = 0;
		}
	}

	// Cキーでファイヤー発射
	// Cキーが押された瞬間を取得
	if (Pad::IsTrigger(PAD_INPUT_3))
	{
		m_pressTime = GetNowCount();
	}
	// cキーが押されているか判定
	if (Pad::IsPress(PAD_INPUT_3))
	{
		m_nowPressTime = GetNowCount() - m_pressTime; // ボタンを押して離すまでの時間
	}
	// cキーが離された瞬間を判定
	if (Pad::IsRelease(PAD_INPUT_3))
	{
		if (m_fireEnergy > 0) // 弾エネルギーが0以上
		{
			if (m_nowPressTime < 2000) // 長押し時間が2秒以下
			{
				m_fireEnergy--; // 弾エネルギーを1減らす
			}
			else if (m_nowPressTime < 5000) // 長押し時間が5秒以下
			{
				if (m_fireEnergy - 6 < 0) // 弾エネルギーが足りない場合
				{
					m_fireEnergy--; // 弾エネルギーを1減らす
				}
				else
				{
					m_fireEnergy -= 6; // 弾エネルギーを6減らす
				}
			}
			else // 長押し時間が5秒以上
			{
				if (m_fireEnergy - 10 < 0) // 弾エネルギーが足りない場合
				{
					m_fireEnergy--; // 弾エネルギーを1減らす
				}
				else
				{
					m_fireEnergy -= 10; // 弾エネルギーを10減らす
				}
			}

			// 新しい弾を生成する
			ShotFire* pShot = new ShotFire;
			pShot->Init();
			pShot->SetMain(m_pMain);
			pShot->SetPlayer(this);
			pShot->Start(GetPos());
			// 以降更新やメモリの解放はSceneMainに任せる
			m_pMain->AddShot(pShot);
		}
		else // 弾エネルギーが0以下
		{
			m_fireEnergy = 0; // 現在の弾エネルギーを0にする
		}
	}

	if (kFloorHeight < m_pos.y) // 床より下に移動したら床上に戻す
	{
		m_pos.y = kFloorHeight;
		m_jumpFrame = 0;
		m_isJumpFlag = false;
	}
	if(m_pos.y < 0) // 画面外に出たら画面内に戻す
	{
		m_pos.y = 0;
	}

	m_pos += move; // 現在値の更新
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight); // 当たり判定の更新
}

void Player::Draw()
{
	if (m_isRight) // 右を向いている場合
	{
		DrawGraph(m_pos.x, m_pos.y, m_handle, false);
	}
	else // 左を向いている場合
	{
		DrawTurnGraph(m_pos.x, m_pos.y, m_handle, false);
	}

#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(0x0000ff, false);
	// 長押し時間の表示
	DrawFormatString(8, 50, 0xffffff, "長押し時間:%d", m_nowPressTime);
#endif
}
