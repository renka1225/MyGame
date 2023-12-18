#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "Bg.h"
#include "SceneMain.h"
#include "ShotBuster.h"
#include "ShotMetal.h"
#include "ShotFire.h"
#include "ShotLineMove.h"
#include "RecoveryBase.h"
#include <cassert>

// Playerで使用する定数
namespace
{
	// 移動速度
	constexpr float kSpeed = 3.0f;
	// 重力
	constexpr float kGravity = 0.5f;
	// 初速度
	constexpr float kVelocity = -10.0f;

	// プレイヤーのサイズ
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 64;

	// マップチップのサイズ
	constexpr int kMapWidth = 32;
	constexpr int kMapHeight = 32;

	// ダメージ演出のフレーム数
	constexpr int kDamageFrame = 60;

	// プレイヤーの初期位置
	constexpr float kPosX = 0.0f;
	constexpr float kPosY = 500.0f;

	// プレイヤーの最大HP
	constexpr float kMaxHp = 10;
	// 最大弾エネルギー
	constexpr float kMaxShot = 28;
	// 残機
	constexpr int kLife = 10;

	// アイテムの回復量
	constexpr float kSmallRecovery = 2;		// 小アイテム
	constexpr float kGreatRecovery = 10;	// 大アイテム
}


Player::Player(SceneMain* pMain, Bg* pBg) :
	m_pMain(pMain),
	m_pBg(pBg),
	m_pRecovery(nullptr),
	m_pos(kPosX, kPosY),
	m_colRect(),
	m_handle(-1),
	m_isRight(true),
	m_isGround(false),
	m_velocity(0),
	m_jumpFrame(0),
	m_hp(kMaxHp),
	m_life(kLife),
	m_damageFrame(0),
	m_metalEnergy(28),
	m_fireEnergy(28),
	m_lineEnergy(28),
	m_keyState(0),
	m_pressTime(0),
	m_nowPressTime(0)
{
}

Player::~Player()
{
}

/*初期化処理*/
void Player::Init()
{
	// 現在位置
	m_pos.x = kPosX;
	m_pos.y = kPosY;
	// 向き
	m_isRight = true;
	// ジャンプフラグ
	m_isGround = false;
	// 加速度
	m_velocity = 0;
	// HP
	m_hp = kMaxHp;
	// 残機数
	m_life = kLife;
	// ダメージのフレーム数
	m_damageFrame = 0;
}

/*プレイヤーの更新*/
void Player::Update()
{
	// 移動量
	Vec2 move{ 0.0f, 0.0f };

	// プレイヤーの現在地のマップチップ番号を取得する
	// プレイヤーの現在地 / マップチップのサイズ
	//int mapChipNo = m_pBg->GetChipData((m_pos.x + kPlayerWidth / 2) / kMapWidth, (m_pos.y + kPlayerHeight / 2) / kMapHeight);		// 中心
	//int ulNo = m_pBg->GetChipData(m_pos.x / kMapWidth, m_pos.y / kMapHeight);										// 左上	
	//int urNo = m_pBg->GetChipData((m_pos.x + kPlayerWidth) / kMapWidth, m_pos.y / kMapHeight);					// 右上
	//int dlNo = m_pBg->GetChipData(m_pos.x / kMapWidth, (m_pos.y + kPlayerHeight) / kMapHeight);					// 左下
	//int drNo = m_pBg->GetChipData((m_pos.x + kPlayerWidth) / kMapWidth, (m_pos.y + kPlayerHeight) / kMapHeight);	// 右下

	// マップチップの当たり判定を取得する
	Rect mapChipRect = m_pBg->GetColRect(m_pos.x / kMapWidth, m_pos.y / kMapHeight);

	// プレイヤーとマップの当たり判定
	if (m_colRect.IsCollision(mapChipRect))
	{
		int mapChipNo = m_pBg->GetChipData(m_pos.x / kMapWidth, (m_pos.y +kPlayerHeight) / kMapHeight);

		// プレイヤーが地面に接しているか
		if (mapChipNo == 1)
		{
			m_isGround = true;
			
			//m_pos.x += kSpeed; // これを追加するとプレイヤーが自動スクロールがする
		}
		else
		{
			m_isGround = false;
		}
	}

	/*画面外に出たら画面内に戻す*/
	if (m_pos.x < 0)
	{
		m_pos.x = 0;
	}
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
	}

	/*プレイヤーが穴に落下した場合*/
	if ((m_pos.y - kPlayerHeight) > Game::kScreenHeight)
	{
		// 残機を1減らす
		//m_life--;
		if (m_life >= 0)
		{
			// 残機が0以上だったらプレイヤーを初期位置に戻す
			m_pos.x = kPosX;
			m_pos.y = kPosY;
		}
	}

	/*ダメージ演出*/
	m_damageFrame--;
	if (m_damageFrame < 0)
	{
		m_damageFrame = 0;
	}

	// パッドを使用する
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/*←を押したら左に移動*/
	if (pad & PAD_INPUT_LEFT)
	{
		m_isRight = false;
		move.x -= kSpeed;
		// プレイヤーの左側が壁に接している場合は左に進まないようにする
		/*if (ulNo == 1)
		{
			move.x = 0;
		}*/
	}

	/*→を押したら右に移動*/
	if (pad & PAD_INPUT_RIGHT)
	{
		m_isRight = true;
		move.x += kSpeed;
		// プレイヤーの右側が壁に接している場合は右に進まないようにする
		/*if (urNo == 1)
		{
			move.x = 0;
		}*/
	}

	/*地面に接している間はジャンプしない*/
	if (m_isGround)
	{
		m_jumpFrame = 0;	// ジャンプフレームを初期化
		m_velocity = 0;		// 初速度を初期化

		/*Spaceでジャンプ*/
		if (Pad::IsTrigger(PAD_INPUT_10))
		{
			m_isGround = false;
			m_velocity = kVelocity;
		}
	}

	/*ジャンプ中*/
	if (!m_isGround)
	{
		m_jumpFrame++;	// ジャンプフレームの更新

		//ボタンを離した瞬間にジャンプする
		if (Pad::IsRelease(PAD_INPUT_10))
		{
			// ジャンプの高さを決める
			float jumpHeight;

			if (m_jumpFrame < 10) // 長押し時間10フレーム以下
			{
				jumpHeight = 0.5f;
			}
			else if (m_jumpFrame < 30) // 30フレーム以下
			{
				jumpHeight = 0.8f;
			}
			else	// 30フレーム以上
			{
				jumpHeight = 1.0f;
			}
			m_velocity *= jumpHeight;
		}
		m_velocity += kGravity; // 初速度に重力を足す
		m_pos.y += m_velocity;	// 現在位置の更新
	}

	/*Zキーでバスター発射*/
	if(Pad::IsTrigger(PAD_INPUT_1))
	{
		ShotBuster* pShot = new ShotBuster;

		// 新しい弾を生成する
		pShot->Init();
		pShot->SetMain(m_pMain);
		pShot->SetPlayer(this);
		pShot->Start(m_pos);
		// 以降更新やメモリの解放はSceneMainに任せる
		m_pMain->AddShot(pShot);
	}

	/*Xキーでメタル発射*/
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
			pShot->Start(m_pos);
			// 以降更新やメモリの解放はSceneMainに任せる
			m_pMain->AddShot(pShot);
		}
		else
		{
			m_metalEnergy = 0;
		}
	}

	/*Cキーでファイヤー発射*/
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
			pShot->Start(m_pos);
			// 以降更新やメモリの解放はSceneMainに任せる
			m_pMain->AddShot(pShot);
		}
		else // 弾エネルギーが0以下
		{
			m_fireEnergy = 0; // 現在の弾エネルギーを0にする
		}
	}

	/*Aキーでアイテム2号発射*/
	//if (Pad::IsTrigger(PAD_INPUT_4))
	//{
	//	if (m_lineEnergy > 0)
	//	{
	//		ShotLineMove* pShot = new ShotLineMove;
	//		// 新しい弾を生成する
	//		pShot->Init();
	//		pShot->SetMain(m_pMain);
	//		pShot->SetPlayer(this);
	//		pShot->Start(m_pos);
	//		// 以降更新やメモリの解放はSceneMainに任せる
	//		m_pMain->AddShot(pShot);
	//	}
	//	else
	//	{
	//		m_lineEnergy = 0;
	//	}
	//}

	m_pos += move; // 現在値の更新
	m_colRect.SetLT(m_pos.x, m_pos.y, kPlayerWidth, kPlayerHeight); // 当たり判定の更新
}

void Player::Draw()
{
	if (m_isRight) // 右を向いている場合
	{
		DrawGraph(static_cast<float>(m_pos.x), static_cast<float>(m_pos.y), m_handle, false);
	}
	else // 左を向いている場合
	{
		DrawTurnGraph(static_cast<float>(m_pos.x), static_cast<float>(m_pos.y), m_handle, false);
	}

	// ダメージ演出
	// 2フレーム間隔で表示非表示を切り替える
	if (m_damageFrame % 4 >= 2) return;

#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(0x0000ff, false);
#endif
}


/*プレイヤーのダメージ演出*/
void Player::OnDamage()
{
	// ダメージ演出中は無敵状態になる
	if (m_damageFrame > 0) return;

	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;

	// HPを減らす
	m_hp--;

	if (m_hp <= 0)
	{
		m_life--;		// 残機を1減らす
		m_hp = kMaxHp;	// HP全回復
	}
}

void Player::HpSmallRecovery()
{
	m_hp += kSmallRecovery;	// HP小回復
	if (m_hp > kMaxHp) // 最大HPを超えた場合
	{
		m_hp = kMaxHp;
	}
}

void Player::HpGreatRecovery()
{
	m_hp += kGreatRecovery;	// HP大回復
	if (m_hp > kMaxHp) // 最大HPを超えた場合
	{
		m_hp = kMaxHp;
	}
}

void Player::HpFullRecovery()
{
	m_hp += kMaxHp; // HP全回復
	if (m_hp > kMaxHp) // 最大HPを超えた場合
	{
		m_hp = kMaxHp;
	}
}

void Player::ShotSmallRecovery()
{
	m_metalEnergy += kSmallRecovery; // 弾エネルギー小回復
	if (m_metalEnergy > kMaxShot) // 最大エネルギーを超えた場合
	{
		m_hp = m_metalEnergy;
	}
}

void Player::ShotGreatRecovery()
{
	m_metalEnergy += kGreatRecovery; // 弾エネルギー大回復
	if (m_metalEnergy > kMaxShot) // 最大エネルギーを超えた場合
	{
		m_hp = m_metalEnergy;
	}
}

void Player::LifeRecovery()
{
	m_life += 1;	// 残機を1増やす
	if (m_life > 99)
	{
		m_life = 99;
	}
}
