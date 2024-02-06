#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "Bg.h"
#include "SceneStage1.h"
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
	constexpr float kSpeed = 8.0f;
	// 重力
	constexpr float kGravity = 0.5f;
	// 初速度
	constexpr float kVelocity = -12.5f;

	// プレイヤーの初期位置
	constexpr float kPosX = 350.0f;
	constexpr float kPosY = 450.0f;

	// プレイヤーの最大HP
	constexpr int kMaxHp = 10;
	// 最大弾エネルギー
	constexpr float kMaxShot = 10;
	// メタルの最大エネルギー
	constexpr float kMaxMetalShot = 5;
	// 残機
	constexpr int kLife = 3;

	// アイテムの回復量
	constexpr float kSmallRecovery = 2;	// 小アイテム
	constexpr float kGreatRecovery = 5;	// 大アイテム

	// アイテム2号のサイズ
	constexpr int kShotWidth = 52;

	// マップチップのサイズ
	constexpr int kMapWidth = 32;
	constexpr int kMapHeight = 32;

	// プレイヤーのサイズ
	constexpr float kScale = 0.3f;
	constexpr int kPlayerWidth = 200;
	constexpr int kPlayerHeight = 296;

	// プレイヤーの当たり判定のサイズ
	constexpr int kPlayerColX = kPlayerWidth * kScale - 40;
	constexpr int kPlayerColY = kPlayerHeight * kScale;

	// キャラクターのアニメーション
	constexpr int kUseFrame[] = { 0, 1, 2, 1 };
	// 待機アニメーション1コマのフレーム数
	constexpr int kIdleAnimFrameNum = 32;
	// 待機アニメーション1サイクルのフレーム数
	constexpr int kIdleAnimFrameCycle = _countof(kUseFrame) * kIdleAnimFrameNum;
	// 移動アニメーション1コマのフレーム数
	constexpr int kWalkAnimFrameNum = 8;
	// 移動アニメーション1サイクルのフレーム数
	constexpr int kWalkAnimFrameCycle = _countof(kUseFrame) * kWalkAnimFrameNum;
	// ショットのアニメーション表示時間
	constexpr int kShotAnimFrame = 30;
	// ダメージのアニメーション表示時間
	constexpr int kDamageAnimFrame = 5;

	// ダメージ演出のフレーム数
	constexpr int kDamageFrame = 60;
}


Player::Player() :
	m_pStage1(nullptr),
	m_pBg(nullptr),
	m_pos(kPosX, kPosY),
	m_move(0.0f, 0.0f),
	m_isRight(true),
	m_isGround(false),
	m_isJump(false),
	m_jumpFrame(0),
	m_hp(kMaxHp),
	m_life(kLife),
	m_fullHpRecovery(0),
	m_damageFrame(0),
	m_metalEnergy(kMaxMetalShot),
	m_fireEnergy(kMaxShot),
	m_lineEnergy(kMaxShot),
	m_isBuster(false),
	m_isMetal(false),
	m_isFire(false),
	m_isLineMove(false),
	m_keyState(0),
	m_pressTime(0),
	m_nowPressTime(0),
	m_isSmallFire(false),
	m_isMiddleFire(false),
	m_isBigFire(false),
	m_lineTime(60),
	m_animation(Anim::kIdle),
	m_idleAnimFrame(0),
	m_walkAnimFrame(0),
	m_shotAnimFrame(0),
	m_damageAnimFrame(0)
{
	// 画像読み込み
	m_idleHandle = LoadGraph("data/image/Player/idle.png");
	m_walkHandle = LoadGraph("data/image/Player/walk.png");
	m_shotHandle = LoadGraph("data/image/Player/shot.png");
	m_jumpHandle = LoadGraph("data/image/Player/jump.png");
	m_damageHandle = LoadGraph("data/image/Player/damage.png");

	// 音読み込み
	m_shotSE = LoadSoundMem("data/sound/SE/shot.mp3");
	m_shotFireSE = LoadSoundMem("data/sound/SE/shotFire.wav");
	m_jumpSE = LoadSoundMem("data/sound/SE/jump.mp3");
	m_damageSE = LoadSoundMem("data/sound/SE/playerDamage.wav");
	m_deadSE = LoadSoundMem("data/sound/SE/playerDead.wav");
}

Player::~Player()
{
	DeleteGraph(m_idleHandle);
	DeleteGraph(m_walkHandle);
	DeleteGraph(m_shotHandle);
	DeleteGraph(m_jumpHandle);
	DeleteGraph(m_damageHandle);
	DeleteSoundMem(m_shotSE);
	DeleteSoundMem(m_shotFireSE);
	DeleteSoundMem(m_damageSE);
	DeleteSoundMem(m_deadSE);
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
	m_isJump = false;
	// 加速度
	m_move.y = 0.0f;
	// ダメージのフレーム数
	m_damageFrame = 0;
	// 開始時はバスターを打てるようにする
	m_isBuster = true;
	m_isMetal = false;
	m_isFire = false;
	m_isLineMove = false;
	// ファイアの状態
	m_isSmallFire = false;
	m_isMiddleFire = false;
	m_isBigFire = false;
	// アイテム2号の待機時間
	m_lineTime = 60;
	// 待機状態にする
	m_animation = Anim::kIdle;
	m_idleAnimFrame = 0;
	m_walkAnimFrame = 0;
	m_shotAnimFrame = 0;
	m_damageFrame = 0;

	// 再プレイ時
	if (m_life < 0 || m_pStage1->IsSceneClear() || m_pStage1->IsSceneTitle() || m_pStage1->IsSceneEnd())
	{
		// HP
		m_hp = kMaxHp;
		// 弾エネルギー
		m_metalEnergy = kMaxMetalShot;
		m_fireEnergy = kMaxShot;
		m_lineEnergy = kMaxShot;
		// 残機数
		m_life = kLife;
		// E缶数
		m_fullHpRecovery = 0;
	}
}

/*プレイヤーの更新*/
void Player::Update()
{
	// パッドを使用する
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/*→を押したら右に移動*/
	if (pad & PAD_INPUT_RIGHT)
	{
		m_isRight = true;
		m_move.x = kSpeed;
		m_animation = Anim::kWalk;
	}
	/*←を押したら左に移動*/
	else if (pad & PAD_INPUT_LEFT)
	{
		m_isRight = false;
		m_move.x = -kSpeed;
		m_animation = Anim::kWalk;
	}
	else
	{
		m_move.x = 0;
		m_animation = Anim::kIdle;
	}

	/*プレイヤーが穴に落下した場合*/
	if ((m_pos.y - kPlayerHeight * 0.5f) > Stage::kMapHeight)
	{
		// HPを0にする
		m_hp -= kMaxHp;
		if (m_hp <= 0)
		{
			m_hp = 0;
		}
		StopSoundMem(m_shotFireSE);
	}

	/*HPが0以下になったら残機を1減らす*/
	if (m_hp <= 0)
	{
		// 残機が減るごとにSEを鳴らす
		PlaySoundMem(m_deadSE, DX_PLAYTYPE_NORMAL, true);

		// 残機が0以上だったら初期化する
		if (m_life >= 0)
		{
			Init();
		}

		m_life--;
		m_hp = kMaxHp;	// HP全回復
	}

	/*地面に接している*/
	if (m_isGround)
	{
		m_jumpFrame = 0;
		m_isJump = false;

		/*ZキーorAボタンでジャンプ*/
		if (Pad::IsTrigger(PAD_INPUT_A))
		{
			m_isGround = false;
			m_isJump = true;
			m_move.y = kVelocity;

			// ジャンプSEを鳴らす
			PlaySoundMem(m_jumpSE, DX_PLAYTYPE_BACK, true);
		}

		/*マップチップとの当たり判定*/
		Rect chipRect; // 当たったマップチップの矩形
		CheckHitMap(chipRect);
		// 穴などに落ちているとき落下中にしたい
		if(!(m_pBg->IsCollision(m_colRect, chipRect)))
		{
			m_isGround = false;
		}
	}
	/*地面に接地していない*/
	else
	{
		// ジャンプ状態にする
		m_animation = Anim::kJump;

		if (m_isJump)
		{
			m_jumpFrame++;	// ジャンプフレームの更新

			//ボタンを離した瞬間にジャンプする
			if (Pad::IsRelease(PAD_INPUT_B))
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
				m_move.y *= jumpHeight;
			}
		}
		m_move.y += kGravity; // 初速度に重力を足す

		/*マップチップとの当たり判定*/
		Rect chipRect; // 当たったマップチップの矩形
		CheckHitMap(chipRect);
	}

#ifdef  _DEBUG
	// MEMO:移動量確認
	// printfDx("moveY:(%f)\n", m_move.y);
#endif

	/*バスター発射*/
	if (m_isBuster)
	{
		if (Pad::IsTrigger(PAD_INPUT_B))
		{
			m_animation = Anim::kShot;
			m_shotAnimFrame = kShotAnimFrame;

			ShotBuster* pShot = new ShotBuster;
			// 新しい弾を生成する
			pShot->Init();
			pShot->SetMain(m_pStage1);
			pShot->SetPlayer(this);
			pShot->Start(m_pos);
			// 以降更新やメモリの解放はSceneMainに任せる
			m_pStage1->AddShot(pShot);

			// 弾発射のSEを鳴らす
			PlaySoundMem(m_shotSE, DX_PLAYTYPE_BACK, true);
		}
	}

	/*メタル発射*/
	if (m_isMetal)
	{
		if (Pad::IsTrigger(PAD_INPUT_B))
		{
			m_animation = Anim::kShot;
			m_shotAnimFrame = kShotAnimFrame;

			if (m_metalEnergy > 0)
			{
				ShotMetal* pShot = new ShotMetal;
				// 新しい弾を生成する
				pShot->Init();
				pShot->SetMain(m_pStage1);
				pShot->SetPlayer(this);
				pShot->Start(m_pos);
				// 以降更新やメモリの解放はSceneMainに任せる
				m_pStage1->AddShot(pShot);

				// 弾発射のSEを鳴らす
				PlaySoundMem(m_shotSE, DX_PLAYTYPE_BACK, true);

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
		if (Pad::IsTrigger(PAD_INPUT_B))
		{
			m_pressTime = GetNowCount();
		}
		// キーが押されているか判定
		if (Pad::IsPress(PAD_INPUT_B))
		{
			m_animation = Anim::kShot;
			m_shotAnimFrame = kShotAnimFrame;

			if (m_fireEnergy >= 0)
			{
				// 長押し中SEを流す
				if (CheckSoundMem(m_shotFireSE) == 0)
				{
					PlaySoundMem(m_shotFireSE, DX_PLAYTYPE_LOOP, true);
				}
			}

			m_nowPressTime = GetNowCount() - m_pressTime; // ボタンを押して離すまでの時間
		}
		// キーが離された瞬間を判定
		if (Pad::IsRelease(PAD_INPUT_B))
		{
			// SE停止
			StopSoundMem(m_shotFireSE);

			if (m_fireEnergy > 0) // 弾エネルギーが0以上
			{
				// 弾発射のSEを鳴らす
				PlaySoundMem(m_shotSE, DX_PLAYTYPE_BACK, true);

				if (m_nowPressTime < 2000) // 長押し時間が2秒以下
				{
					m_fireEnergy--; // 弾エネルギーを1減らす
					m_isSmallFire = true;
					m_isMiddleFire = false;
					m_isBigFire = false;
					
				}
				else if (m_nowPressTime < 5000) // 長押し時間が5秒以下
				{
					if (m_fireEnergy - 3 < 0) // 弾エネルギーが足りない場合
					{
						m_fireEnergy--; // 弾エネルギーを1減らす
						m_isSmallFire = true;
						m_isMiddleFire = false;
						m_isBigFire = false;
					}
					else
					{
						m_fireEnergy -= 3; // 弾エネルギーを3減らす
						m_isSmallFire = false;
						m_isMiddleFire = true;
						m_isBigFire = false;
					}
				}
				else // 長押し時間が5秒以上
				{
					if (m_fireEnergy - 5 < 0) // 弾エネルギーが足りない場合
					{
						m_fireEnergy--; // 弾エネルギーを1減らす
						m_isSmallFire = true;
						m_isMiddleFire = false;
						m_isBigFire = false;
					}
					else
					{
						m_fireEnergy -= 5; // 弾エネルギーを5減らす
						m_isSmallFire = false;
						m_isMiddleFire = false;
						m_isBigFire = true;
					}
				}

				// 新しい弾を生成する
				ShotFire* pShot = new ShotFire;
				pShot->Init();
				pShot->SetMain(m_pStage1);
				pShot->SetPlayer(this);
				pShot->Start(m_pos);
				// 以降更新やメモリの解放はSceneMainに任せる
				m_pStage1->AddShot(pShot);
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
		if (Pad::IsTrigger(PAD_INPUT_B))
		{
			m_animation = Anim::kShot;
			m_shotAnimFrame = kShotAnimFrame;

			if (!m_pStage1->GetIsExistLineMove() && m_lineEnergy > 0)
			{
				ShotLineMove* pShot = new ShotLineMove;
				// 新しい弾を生成する
				pShot->Init();
				pShot->SetMain(m_pStage1);
				pShot->SetPlayer(this);
				pShot->Start(m_pos);
				// 以降更新やメモリの解放はSceneMainに任せる
				m_pStage1->AddShot(pShot);

				// 弾発射のSEを鳴らす
				PlaySoundMem(m_shotSE, DX_PLAYTYPE_BACK, true);

				m_lineTime = 60;
			}
		}

		// 画面内にある場合
		if (m_pStage1->GetIsExistLineMove())
		{
			m_lineTime--;
			m_lineEnergy -= 0.03f; // エネルギーを減らす
		}
	}

	/*ダメージ演出*/
	m_damageFrame--;
	if (m_damageFrame < 0)
	{
		m_damageFrame = 0;
	}

	/*アニメーション*/
	//待機状態
	if(m_animation == Anim::kIdle)
	{
		m_idleAnimFrame++;
		if (m_idleAnimFrame >= kIdleAnimFrameCycle)
		{
			m_idleAnimFrame = 0;
		}
	}
	//移動状態
	else if (m_animation == Anim::kWalk)
	{
		m_walkAnimFrame++;
		if (m_walkAnimFrame >= kWalkAnimFrameCycle)
		{
			m_walkAnimFrame = 0;
		}
	}
	// ショット
	m_shotAnimFrame--;
	if (m_shotAnimFrame < 0)
	{
		m_shotAnimFrame = 0;
	}

	// ダメージ
	m_damageAnimFrame--;
	if (m_damageAnimFrame < 0)
	{
		m_damageAnimFrame = 0;
	}
}

void Player::Draw()
{
// ダメージ演出
// 2フレーム間隔で表示非表示を切り替える
	if (m_damageFrame % 10 >= 8) return;

	// プレイヤーの描画
	DrawPlayer();

#ifdef _DEBUG
	// MEMO:スクロールが反映されないためコメントアウト
	// 当たり判定の表示
	// m_colRect.Draw(0x0000ff, false);
#endif
}

/// <summary>
/// プレイヤーの描画
/// </summary>
void Player::DrawPlayer()
{
	// スクロール量を反映する
	int x = m_pos.x;
	int y = m_pos.y;
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// 画像切り出し位置を計算
	// 待機状態
	int idleAnimFrame = m_idleAnimFrame / kIdleAnimFrameNum;
	int idleSrcX = kUseFrame[idleAnimFrame] * kPlayerWidth;
	int idleSrcY = kPlayerHeight;
	// 移動状態
	int walkAnimFrame = m_walkAnimFrame / kWalkAnimFrameNum;
	int walkSrcX = kUseFrame[walkAnimFrame] * kPlayerWidth;
	int walkSrcY = kPlayerHeight;

	if (m_isRight)
	{
		idleSrcY = kPlayerHeight * 0;
		walkSrcY = kPlayerHeight * 0;
	}
	else
	{
		idleSrcY = kPlayerHeight * 1;
		walkSrcY = kPlayerHeight * 1;
	}

	// 待機状態
	if (m_animation == Anim::kIdle && m_shotAnimFrame <= 0 && m_damageAnimFrame <= 0)
	{
		if (m_isRight) // 右を向いている場合
		{
			DrawRectRotaGraph(x, y, idleSrcX, idleSrcY, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_idleHandle, true);
		}
		else
		{
			DrawRectRotaGraph(x, y, idleSrcX, idleSrcY, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_idleHandle, true);
		}
	}
	// 移動状態
	else if (m_animation == Anim::kWalk && m_shotAnimFrame <= 0 && m_damageAnimFrame <= 0)
	{
		if (m_isRight) // 右を向いている場合
		{
			DrawRectRotaGraph(x, y, walkSrcX, walkSrcY, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_walkHandle, true);
		}
		else
		{
			DrawRectRotaGraph(x, y, walkSrcX, walkSrcY, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_walkHandle, true);
		}
	}
	// 弾発射状態
	else if (m_animation == Anim::kShot || m_shotAnimFrame > 0 && m_damageAnimFrame <= 0)
	{
		if (m_isRight) // 右を向いている場合
		{
			if (m_isGround) // 接地中
			{
				DrawRectRotaGraph(x, y, 0, 0, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_shotHandle, true);
			}
			else
			{
				DrawRectRotaGraph(x, y, kPlayerWidth, 0, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_shotHandle, true);
			}
		}
		else
		{
			if (m_isGround) // 接地中
			{
				DrawRectRotaGraph(x, y, 0, kPlayerHeight, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_shotHandle, true);
			}
			else
			{
				DrawRectRotaGraph(x, y, kPlayerWidth, kPlayerHeight, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_shotHandle, true);
			}
		}
	}
	// ジャンプ状態
	else if (m_animation == Anim::kJump && m_shotAnimFrame <= 0 && m_damageAnimFrame <= 0)
	{
		if (m_isRight) // 右を向いている場合
		{
			DrawRectRotaGraph(x, y, 0, 0, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_jumpHandle, true);
		}
		else
		{
			DrawRectRotaGraph(x, y, 0, kPlayerHeight + 1, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_jumpHandle, true);
		}
	}
	// ダメージ状態
	else if (m_animation == Anim::kDamage && m_shotAnimFrame <= 0 && m_damageAnimFrame > 0)
	{
		if (m_isRight) // 右を向いている場合
		{
			DrawRectRotaGraph(x, y, 0, 0, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_damageHandle, true);
		}
		else
		{
			DrawRectRotaGraph(x, y, 0, kPlayerHeight, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_damageHandle, true);
		}
	}
}

/// <summary>
/// マップチップの当たり判定
/// </summary>
/// <param name="chipRect"></param>
void Player::CheckHitMap(Rect chipRect)
{
	// 横から当たったかチェックする
	m_pos.x += m_move.x;
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kPlayerColX), static_cast<float>(kPlayerColY));
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_move.x > 0.0f)
		{
			m_pos.x = chipRect.GetLeft() - kPlayerWidth * kScale * 0.5f + 15 - 1;
		}
		else if (m_move.x < 0.0f)
		{
			m_pos.x = chipRect.GetRight() + kPlayerWidth * kScale * 0.5f - 15 + 1;
		}
	}

	// 縦から当たったかチェックする
	m_pos.y += m_move.y;
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kPlayerColX), static_cast<float>(kPlayerColY));
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_move.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kPlayerHeight * kScale  * 0.5f - 1 ;
			m_isGround = true;
		}
		else if (m_move.y < 0.0f)
		{
			m_pos.y = chipRect.GetBottom() + kPlayerHeight * kScale * 0.5f + 1;
			m_move.y *= -1.0f;
		}
	}
}

/// <summary>
/// 弾の選択状態を更新
/// </summary>
/// <param name="isBuster"></param>
/// <param name="isMetal"></param>
/// <param name="isFire"></param>
/// <param name="isLineMove"></param>
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

/// <summary>
/// プレイヤーのダメージ演出
/// </summary>
void Player::OnDamage()
{
	// ダメージ演出中は無敵状態になる
	if (m_damageFrame > 0) return;

	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;
	m_damageAnimFrame = kDamageAnimFrame;
	m_animation = Anim::kDamage;

	// ダメージSEを鳴らす
	PlaySoundMem(m_damageSE, DX_PLAYTYPE_BACK, true);

	// HPを減らす
	m_hp--;
	if (m_hp <= 0)
	{
		m_life--;		// 残機を1減らす
		m_hp = kMaxHp;	// HP全回復
	}

	// TODO:ノックバック
	/*m_pos.y -= 50;
	if (m_isRight)
	{
		m_pos.x -= 50;
	}
	else
	{
		m_pos.x += 50;
	}*/
}

/// <summary>
/// E缶取得
/// </summary>
void Player::GetHpFullRecovery()
{
	m_fullHpRecovery += 1;
}

/// <summary>
/// 回復
/// </summary>
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
		if (m_metalEnergy > kMaxMetalShot)
		{
			m_metalEnergy = kMaxMetalShot;
		}
	}
	else if (m_isFire) // ファイア
	{
		m_fireEnergy += kSmallRecovery;
		if (m_fireEnergy > kMaxMetalShot)
		{
			m_fireEnergy = kMaxMetalShot;
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
		if (m_metalEnergy > kMaxMetalShot)
		{
			m_metalEnergy = kMaxMetalShot;
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

/// <summary>
/// アイテム2号に乗った際の処理
/// </summary>
/// <param name="shotRect">アイテム2号の当たり判定</param>
void Player::RideLineMove(Rect shotRect)
{
 	Rect lineMoveRect = shotRect; // アイテム2号の当たり判定

	// 当たり判定更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kPlayerColX), static_cast<float>(kPlayerColY));

	// アイテム2号に乗った場合
	if (m_colRect.IsCollision(lineMoveRect))
	{
		if (m_lineTime <= 0)
		{
			if (m_isRight)
			{
				m_pos.x += 10.0f;
			}
			else
			{
				m_pos.x -= 10.0f;
			}
		}
		m_pos.y = lineMoveRect.GetTop() - kPlayerHeight * kScale * 0.5f;
		m_isGround = true;
		m_animation = Anim::kIdle;
	}
}