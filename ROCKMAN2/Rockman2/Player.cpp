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
	constexpr float kSpeed = 2.0f;
	// 重力
	constexpr float kGravity = 0.5f;
	// 初速度
	constexpr float kVelocity = -12.0f;

	// プレイヤーのサイズ
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 64;

	// マップチップのサイズ
	constexpr int kMapWidth = 32;
	constexpr int kMapHeight = 32;

	// ダメージ演出のフレーム数
	constexpr int kDamageFrame = 60;

	// プレイヤーの初期位置
	constexpr float kPosX = 30.0f;
	constexpr float kPosY = 500.0f;

	// プレイヤーの最大HP
	constexpr float kMaxHp = 28;
	// 最大弾エネルギー
	constexpr float kMaxShot = 28;
	// 残機
	constexpr int kLife = 10;

	// アイテムの回復量
	constexpr float kSmallRecovery = 2;		// 小アイテム
	constexpr float kGreatRecovery = 10;	// 大アイテム

	// アイテム2号のサイズ
	constexpr int kShotWidth = 32;
}


Player::Player(SceneMain* pMain, Bg* pBg) :
	m_pMain(pMain),
	m_pBg(pBg),
	m_pRecovery(nullptr),
	m_pos(0, 0),
	m_colRect(),
	m_handle(-1),
	m_isRight(true),
	m_isGround(false),
	m_velocity(0),
	m_jumpFrame(0),
	m_hp(kMaxHp),
	m_life(kLife),
	m_fullHpRecovery(0),
	m_damageFrame(0),
	m_metalEnergy(28),
	m_fireEnergy(28),
	m_lineEnergy(28),
	m_isBuster(false),
	m_isMetal(false),
	m_isFire(false),
	m_isLineMove(false),
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
	// 開始時はバスターを打てるようにする
	m_isBuster = true;
	m_isMetal = false;
	m_isFire = false;
	m_isLineMove = false;
}

/*プレイヤーの更新*/
void Player::Update()
{
	// 移動量
	Vec2 move {0.0f, 0.0f};

	// パッドを使用する
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/*←を押したら左に移動*/
	if (pad & PAD_INPUT_LEFT)
	{
		m_isRight = false;
		move.x -= kSpeed;
	}

	/*→を押したら右に移動*/
	if (pad & PAD_INPUT_RIGHT)
	{
		m_isRight = true;
		move.x += kSpeed;
	}

	/*マップチップに当たった処理*/
	HitCollision();

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

	/*バスター発射*/
	if (m_isBuster)
	{
		if (Pad::IsTrigger(PAD_INPUT_1))
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

	}

	/*メタル発射*/
	if (m_isMetal)
	{
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			if (m_metalEnergy > 0)
			{
				ShotMetal* pShot = new ShotMetal;
				// 新しい弾を生成する
				pShot->Init();
				pShot->SetMain(m_pMain);
				pShot->SetPlayer(this);
				pShot->Start(m_pos);
				// 以降更新やメモリの解放はSceneMainに任せる
				m_pMain->AddShot(pShot);

				if (pShot->IsExist())
				{
					// 弾エネルギーを0.25減らす
					m_metalEnergy -= 0.25f;
				}
			}
			else
			{
				m_metalEnergy = 0;
			}
		}
	}

	/*ファイヤー発射*/
	if (m_isFire)
	{
	// キーが押された瞬間を取得
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			m_pressTime = GetNowCount();
		}
		// キーが押されているか判定
		if (Pad::IsPress(PAD_INPUT_1))
		{
			m_nowPressTime = GetNowCount() - m_pressTime; // ボタンを押して離すまでの時間
		}
		// キーが離された瞬間を判定
		if (Pad::IsRelease(PAD_INPUT_1))
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
	}
	
	/*アイテム2号発射*/
	if (m_isLineMove)
	{
		// ボタンを押したら発射
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			if (!m_pMain->GetIsExistLineMove() && m_lineEnergy > 0)
			{
				ShotLineMove* pShot = new ShotLineMove;
				// 新しい弾を生成する
				pShot->Init();
				pShot->SetMain(m_pMain);
				pShot->SetPlayer(this);
				pShot->Start(m_pos);
				// 以降更新やメモリの解放はSceneMainに任せる
				m_pMain->AddShot(pShot);
			}
		}

		// 画面内にある場合
		if (m_pMain->GetIsExistLineMove())
		{
			m_lineEnergy -= 0.03f; // エネルギーを減らす
		}
	}

	m_pos += move; // 現在値の更新
	m_colRect.SetCenter(m_pos.x + static_cast<float>(kPlayerWidth) / 2, m_pos.y + static_cast<float>(kPlayerHeight) / 2, kPlayerWidth, kPlayerHeight); // 当たり判定の更新
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

/*地面、壁に当たったときの処理*/
void Player::HitCollision()
{
	Rect mapChipRect = m_pBg->GetColRect((m_pos.x + kPlayerWidth / 2) / kMapWidth, (m_pos.y + kPlayerWidth / 2) / kMapHeight);	// プレイヤーの中心のマップチップの当たり判定
	
	// プレイヤーとマップの当たり判定 矩形
	//if (m_colRect.IsCollision(mapChipRect))
	//{
	//	int mapChipNo = m_pBg->GetChipData((m_pos.x + kPlayerWidth / 2) / kMapWidth, (m_pos.y + kPlayerHeight / 2) / kMapHeight);		// 中心
	//	if (mapChipNo == 1)
	//	{
	//		if (m_colRect.GetCenter().y >= mapChipRect.GetTop()) // 地面に接している場合
	//		{
	//			m_isGround = true;
	//			m_pos.y = mapChipRect.GetTop();	// プレイヤーを地面の上に移動
	//		}
	//	}
	//	else
	//	{
	//		m_isGround = false;
	//	}
	//}
	//if (m_colRect.GetLeft() <= mapChipRect.GetRight()) // 壁よりも左に移動
	//{
	//	m_pos.x = mapChipRect.GetRight();
	//}
	//else if (m_colRect.GetRight() >= mapChipRect.GetLeft()) // 壁よりも右に移動
	//{
	//	m_pos.x = mapChipRect.GetLeft();
	//}

	// プレイヤーの現在地のマップチップ番号を取得する
	// プレイヤーの現在地 / マップチップのサイズ
	int mapChipNo = m_pBg->GetChipData((m_pos.x + kPlayerWidth / 2) / kMapWidth, (m_pos.y + kPlayerHeight / 2) / kMapHeight);	// プレイヤーの中心
	int TLChipNo = m_pBg->GetChipData(m_pos.x / kMapWidth, m_pos.y / kMapHeight);										// プレイヤーの左上のチップ番号を取得
	int TRChipNo = m_pBg->GetChipData((m_pos.x + kPlayerWidth) / kMapWidth, m_pos.y / kMapHeight);						// プレイヤーの右上のチップ番号を取得
	int BLChipNo = m_pBg->GetChipData(m_pos.x / kMapWidth, (m_pos.y + kPlayerHeight) / kMapHeight);						// プレイヤーの左下のチップ番号を取得
	int BRChipNo = m_pBg->GetChipData((m_pos.x + kPlayerWidth) / kMapWidth, (m_pos.y + kPlayerHeight) / kMapHeight);	// プレイヤーの右下のチップ番号を取得

	// プレイヤーとマップの当たり判定
	if (BLChipNo == 1 || BRChipNo == 1) // 地面に接している場合
	{
		m_isGround = true;
		m_pos.y = mapChipRect.GetTop();    // プレイヤーを地面の上に移動
	}
	else
	{
		m_isGround = false;
	}

	if (TLChipNo == 1 || TRChipNo == 1) // 天井に接した場合
	{
		m_pos.y = mapChipRect.GetBottom();
	}

}

/*弾の選択状態を更新*/
void Player::ChangeShot(bool isBuster, bool isMetal, bool isFire, bool isLineMove)
{
	// バスターの選択状態を更新
	m_isBuster = isBuster;

	// メタルの選択状態を更新
	m_isMetal = isMetal;

	// ファイアの選択状態を更新
	m_isFire = isFire;

	// 2号の選択状態を更新
	m_isLineMove = isLineMove;
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

/*E缶取得*/
void Player::GetHpFullRecovery()
{
	m_fullHpRecovery += 1;
}

/*回復*/
void Player::HpSmallRecovery() // HP小回復
{
	m_hp += kSmallRecovery;
	if (m_hp > kMaxHp) // 最大HPを超えた場合
	{
		m_hp = kMaxHp;
	}
}

void Player::HpGreatRecovery() // HP大回復
{
	m_hp += kGreatRecovery;
	if (m_hp > kMaxHp) // 最大HPを超えた場合
	{
		m_hp = kMaxHp;
	}
}

void Player::ShotSmallRecovery() // 弾小回復
{
	if (m_isMetal) // メタル
	{
		m_metalEnergy += kSmallRecovery;
		if (m_metalEnergy > kMaxShot)
		{
			m_metalEnergy = kMaxShot;
		}
	}
	else if (m_isFire) // ファイア
	{
		m_fireEnergy += kSmallRecovery;
		if (m_fireEnergy > kMaxShot)
		{
			m_fireEnergy = kMaxShot;
		}
	}
	else if (m_isLineMove) // 2号
	{
		m_isLineMove += kSmallRecovery;
		if (m_isLineMove > kMaxShot)
		{
			m_isLineMove = kMaxShot;
		}
	}
}

void Player::ShotGreatRecovery() // 弾大回復
{
	if (m_isMetal) // メタル
	{
		m_metalEnergy += kGreatRecovery;
		if (m_metalEnergy > kMaxShot)
		{
			m_metalEnergy = kMaxShot;
		}
	}
	else if (m_isFire) // ファイア
	{
		m_fireEnergy += kGreatRecovery;
		if (m_fireEnergy > kMaxShot)
		{
			m_fireEnergy = kMaxShot;
		}
	}
	else if (m_isLineMove) // 2号
	{
		m_isLineMove += kSmallRecovery;
		if (m_isLineMove > kMaxShot)
		{
			m_isLineMove = kMaxShot;
		}
	}
}

void Player::LifeRecovery() // 残機回復
{
	m_life += 1;	// 残機を1増やす
	if (m_life > 99)
	{
		m_life = 99;
	}
}

void Player::HpFullRecovery() // HP全回復
{
	if (m_fullHpRecovery > 0)
	{
		if (m_hp < kMaxHp) // 現在のHPが最大HP未満
		{
			m_hp += kMaxHp;	// HPを最大まで回復
			if (m_hp > kMaxHp) // 最大HPを超えた場合
			{
				m_hp = kMaxHp;
			}
			m_fullHpRecovery--; // 所持数を1減らす
		}
	}
	else
	{
		m_fullHpRecovery = 0;
	}
}

/*アイテム2号に乗った際の処理*/
void Player::RideLineMove(Rect shotRect)
{
 	Rect lineMoveRect = shotRect; // アイテム2号の当たり判定

	// 上に乗った場合
	if (m_colRect.GetBottom() >= lineMoveRect.GetTop()) 
	{
		m_pos.y = lineMoveRect.GetTop() - kPlayerHeight;
		m_isGround = true;

		// プレイヤーを横に移動
		m_pos.x += lineMoveRect.GetCenter().x - m_colRect.GetCenter().x;

		// ジャンプ
		if (Pad::IsTrigger(PAD_INPUT_10))
		{
			m_isGround = false;
			m_velocity = kVelocity;
		}

		// 当たり判定の更新
		m_colRect.SetCenter(m_pos.x + static_cast<float>(kPlayerWidth) / 2, m_pos.y + static_cast<float>(kPlayerHeight) / 2, kPlayerWidth, kPlayerHeight);
	}
}
