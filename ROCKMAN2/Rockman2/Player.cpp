#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "BgTutorial.h"
#include "BgStage1.h"
#include "SceneTutorial.h"
#include "SceneStage1.h"
#include "ShotBuster.h"
#include "ShotMetal.h"
#include "ShotFire.h"
#include "ShotLineMove.h"
#include "RecoveryBase.h"
#include <cassert>

/// <summary>
/// 定数
/// </summary>
namespace
{
	/*プレイヤーの情報*/
	// 移動速度
	constexpr float kSpeed = 8.0f;
	// 重力
	constexpr float kGravity = 0.5f;
	// 初速度
	constexpr float kVelocity = -12.5f;
	// 最大HP
	constexpr int kMaxHp = 10;
	// 初期の残機数
	constexpr int kLife = 3;
	// 最大残機数
	constexpr int kMaxLife = 99;

	// プレイヤーのサイズ
	constexpr float kScale = 0.3f;
	constexpr int kPlayerWidth = 200;
	constexpr int kPlayerHeight = 296;
	// プレイヤーの当たり判定のサイズ
	constexpr int kPlayerColX = static_cast<int>(kPlayerWidth * kScale - 40);	// 横幅
	constexpr int kPlayerColY = static_cast<int>(kPlayerHeight * kScale);		// 高さ
	// 当たり判定サイズの調節
	constexpr float kColAdjustment = 0.5f;
	// マップチップとの当たり判定の調整
	constexpr int kColChipAdjustment = 15;

	// ダメージ時のノックバック量
	constexpr float kDamageMove = 50.0f;
	// ジャンプの長押し時間
	constexpr int kPressShortJumpFrame = 10;	// 10フレーム
	constexpr int kPressMediumJumpFrame = 30;	// 30フレーム
	// ジャンプの高さ調整
	constexpr float kLittleJumpHeight = 0.5f;	// 小ジャンプ
	constexpr float kInJumpHeight = 0.8f;		// 中ジャンプ
	constexpr float kBigJumpHeight = 1.0f;		// 大ジャンプ

	// 死亡エフェクトのサイズ
	constexpr int kEffectWidth = 32;
	constexpr int kEffectHeight = 32;
	// エフェクトの拡大率
	constexpr float kEffectScale = 3.0f;

	//アニメーション
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
	constexpr int kDamageAnimFrame = 3;
	// ダメージ演出のフレーム数
	constexpr int kDamageFrame = 60;
	// 死亡時のアニメーション
	constexpr int kdamageFrame[] = { 0, 1, 2, 3 };
	constexpr int kDeadFrame = 60;

	/*弾の情報*/
	constexpr float kMaxShot = 10.0f;		// 最大弾エネルギー
	constexpr float kMaxMetalShot = 5.0f;	// メタルの最大エネルギー

	// メタルのエネルギー減少量
	constexpr float kMetalDecrease = 0.25f;
	// ファイアのエネルギー減少量
	constexpr float kMiddleFireDecrease = 3.0f;	// 中
	constexpr float kBigFireDecrease = 5.0f;	// 大
	// 2号のエネルギー減少量
	constexpr float kLineMoveDecrease = 0.03f;

	// ファイアの溜め時間
	constexpr int kSmallFirePressTime = 2000;
	constexpr int kMiddleFirePressTime = 4000;
	// ファイアの大きさ
	constexpr int kFireWidth = 32;
	constexpr int kFireHeight = 32;
	// ファイアの拡大率
	constexpr float kSmallScale = 0.5f;		// 小
	constexpr float kMiddleScale = 0.8f;	// 中
	constexpr float kBigScale = 1.2f;		// 大
	// ファイアパーティクルのサイズ
	constexpr int kFireParticleSize = 256;
	// ファイアパーティクルの拡大率
	constexpr float kFireParticleScale = 0.6f;
	// ファイアパーティクルの表示位置調整
	constexpr int kFireParticlePositioningX = 40;
	constexpr int kFireParticlePositioningY = 20;
	// ファイアパーティクルの表示フレーム
	constexpr int kFireParticleFrame = 30;
	// 2号のサイズ
	constexpr int kShotWidth = 52;
	// 2号の待機時間
	constexpr int kLineMoveStand = 150;
	// 2号に乗った際の移動量
	constexpr float kLineMoveMovement = 10.0f;

	/*アイテムの回復量*/
	constexpr int kSmallRecovery = 2;	// 小アイテム
	constexpr int kGreatRecovery = 5;	// 大アイテム

	/*マップチップのサイズ*/
	constexpr int kMapWidth = 32;
	constexpr int kMapHeight = 32;
}

Player::Player() :
	m_pBg(nullptr),
	m_pMain(nullptr),
	m_move(0.0f, 0.0f),
	m_isRight(true),
	m_isGround(false),
	m_isJump(false),
	m_jumpFrame(0),
	m_hp(kMaxHp),
	m_life(kLife),
	m_fullHpRecovery(0),
	m_damageFrame(0),
	m_deadFrame(0),
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
	m_fireParticleFrame(0),
	m_isSmallFire(false),
	m_isMiddleFire(false),
	m_isBigFire(false),
	m_lineTime(kLineMoveStand),
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
	m_deadEffect = LoadGraph("data/image/Effect/playerDead.png");
	m_fire1Handle = LoadGraph("data/image/Shot/shotFire.png");
	m_fire2Handle = LoadGraph("data/image/Shot/shotFire2.png");
	m_fire3Handle = LoadGraph("data/image/Shot/shotFire3.png");
	m_fireParticle = LoadGraph("data/image/Shot/fire.png");

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
	DeleteGraph(m_deadEffect);
	DeleteGraph(m_fire1Handle);
	DeleteGraph(m_fire2Handle);
	DeleteGraph(m_fire3Handle);
	DeleteGraph(m_fireParticle);
	DeleteSoundMem(m_shotSE);
	DeleteSoundMem(m_shotFireSE);
	DeleteSoundMem(m_damageSE);
	DeleteSoundMem(m_deadSE);
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pBg">背景クラスのポインタ</param>
/// <param name="pMain">ステージクラスのポインタ</param>
/// <param name="initPos">プレイヤーの初期位置</param>
void Player::Init(Bg* pBg, SceneMain* pMain, Vec2 initPos)
{
	m_pBg = pBg;
	m_pMain = pMain;
	// HP
	m_hp = kMaxHp;
	// 現在位置
	m_pos.x = initPos.x;
	m_pos.y = initPos.y;
	// 向き
	m_isRight = true;
	// ジャンプフラグ
	m_isGround = false;
	m_isJump = false;
	// 加速度
	m_move.y = 0.0f;
	// 開始時はバスターを打てるようにする
	m_isBuster = true;
	m_isMetal = false;
	m_isFire = false;
	m_isLineMove = false;
	// ファイアの状態
	m_pressTime = 0;
	m_nowPressTime = 0;
	m_isSmallFire = false;
	m_isMiddleFire = false;
	m_isBigFire = false;
	// アイテム2号の待機時間
	m_lineTime = kLineMoveStand;
	// 待機状態にする
	m_animation = Anim::kIdle;
	m_idleAnimFrame = 0;
	m_walkAnimFrame = 0;
	m_shotAnimFrame = 0;
	m_damageFrame = 0;
	m_fireParticleFrame = 0;
	m_deadFrame = 0;

	// 再プレイ時
	if (m_life < 0 || m_pMain->IsSceneGameOver() || m_pMain->IsSceneClear() || m_pMain->IsSceneTitle() || m_pMain->IsSceneEnd())
	{
		// 残機数
		m_life = kLife;
		// 弾エネルギー
		m_metalEnergy = kMaxMetalShot;
		m_fireEnergy = kMaxShot;
		m_lineEnergy = kMaxShot;
		// E缶数
		m_fullHpRecovery = 0;
	}
}


/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
	/*死亡時演出*/
	m_deadFrame--;
	if (m_deadFrame < 0) m_deadFrame = 0;

	/*プレイヤーが穴に落下した場合*/
	if ((m_pos.y - kPlayerHeight * 0.5f) > Stage1::kMapHeight)
	{
		// HPを0にする
		m_hp -= kMaxHp;
		m_life--;

		// SEを鳴らす
		PlaySoundMem(m_deadSE, DX_PLAYTYPE_BACK, true);
		if (m_hp <= 0) m_hp = 0;
		
		return;
	}

	/*プレイヤーのHPが0以下になった場合*/
	if (m_hp <= 0) return;

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

	/*地面に接している*/
	if (m_isGround)
	{
		m_jumpFrame = 0;
		m_isJump = false;

		/*ZキーorAボタンでジャンプ*/
		if (Pad::IsTrigger(PAD_INPUT_A) && !m_pMain->GetIsExistMenu())
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
			// ジャンプ中処理
			UpdateJump();
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

	/*弾発射処理*/
	//バスター発射
	if (m_isBuster) UpdateShotBuster();
	//メタル発射
	if (m_isMetal) UpdateShotMetal();
	//ファイヤー発射
	if (m_isFire) UpdateShotFire();
	else StopSoundMem(m_shotFireSE);
	//アイテム2号発射
	if (m_isLineMove) UpdateShotLineMove();

	/*ダメージ演出*/
	m_damageFrame--;
	if (m_damageFrame < 0) m_damageFrame = 0;

	/*アニメーション*/
	UpdatePlayerAnim();
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// ダメージ演出
	// 2フレーム間隔で表示非表示を切り替える
	if (m_damageFrame % 10 >= 8) return;

	// スクロール量を反映する
	int x = static_cast<int>(m_pos.x);
	int y = static_cast<int>(m_pos.y);
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// プレイヤーの描画
	if (m_deadFrame <= 0)
	{
		DrawPlayer(x, y);
	}

	// ファイア溜め中の表示
	DrawFire(x, y);

	// 死亡演出
	// 画像の切り出し座標
	int effectFrame = m_damageFrame / kIdleAnimFrameNum;
	int effectSrcX = kUseFrame[effectFrame] * kEffectWidth;
	int effectSrcY = 0;
	if (m_deadFrame > 0)
	{
		DrawRectRotaGraph(x, y, 
			effectSrcX, effectSrcY, 
			kEffectWidth, kEffectHeight, 
			kEffectScale, 0.0f,
			m_deadEffect, true);
	}

#ifdef _DEBUG
	// MEMO:スクロールが反映されないためコメントアウト
	// 当たり判定の表示
	// m_colRect.Draw(0x0000ff, false);
#endif
}


/// <summary>
/// プレイヤーのダメージ演出
/// </summary>
void Player::OnDamage()
{
	// 演出フレーム数を設定する
	m_damageAnimFrame = kDamageAnimFrame;
	m_animation = Anim::kDamage;

	// ダメージ演出中は無敵状態になる
	if (m_damageFrame > 0) return;

	m_hp--;
	m_damageFrame = kDamageFrame;

	// 死亡演出
	if (m_hp <= 0)
	{
		UpdateDead();
	}

	// ノックバックさせる
	if (m_isRight)
	{
		m_pos.x -= kDamageMove;
	}
	else
	{
		m_pos.x += kDamageMove;
	}

	// ダメージSEを鳴らす
	PlaySoundMem(m_damageSE, DX_PLAYTYPE_BACK, true);
	return;
}


/// <summary>
/// E缶取得
/// </summary>
void Player::GetHpFullRecovery()
{
	m_fullHpRecovery++;
}


/// <summary>
/// 回復
/// </summary>

/*HP小回復*/
void Player::HpSmallRecovery()
{
	m_hp += kSmallRecovery;
	if (m_hp > kMaxHp)
	{
		m_hp = kMaxHp;
	}
}

/*HP大回復*/
void Player::HpGreatRecovery()
{
	m_hp += kGreatRecovery;
	if (m_hp > kMaxHp) // 最大HPを超えた場合
	{
		m_hp = kMaxHp;
	}
}

/*弾小回復*/
void Player::ShotSmallRecovery()
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
		m_lineEnergy += kSmallRecovery;
		if (m_lineEnergy > kMaxShot)
		{
			m_lineEnergy = kMaxShot;
		}
	}
}

/*弾大回復*/
void Player::ShotGreatRecovery()
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
	else if (m_lineEnergy) // 2号
	{
		m_lineEnergy += kSmallRecovery;
		if (m_lineEnergy > kMaxShot)
		{
			m_lineEnergy = kMaxShot;
		}
	}
}

/*残機回復*/
void Player::LifeRecovery()
{
	m_life++;	// 残機を1増やす
	if (m_life > kMaxLife)
	{
		m_life = kMaxLife;
	}
}

/*HP、エネルギー全回復*/
void Player::HpFullRecovery()
{
	if (m_fullHpRecovery > 0)
	{
		// HP全回復
		if (m_hp < kMaxHp) // 現在のHPが最大HP未満
		{
			m_hp += kMaxHp;	// HPを最大まで回復
			if (m_hp > kMaxHp) // 最大HPを超えた場合
			{
				m_hp = kMaxHp;
			}
		}

		// エネルギー全回復
		m_metalEnergy += kMaxMetalShot;
		if (m_metalEnergy > kMaxMetalShot)
		{
			m_metalEnergy = kMaxMetalShot;
		}
		
		m_fireEnergy += kMaxShot;
		if (m_fireEnergy > kMaxShot)
		{
			m_fireEnergy = kMaxShot;
		}
		
		m_lineEnergy += kMaxShot;
		if (m_lineEnergy > kMaxShot)
		{
			m_lineEnergy = kMaxShot;
		}
		m_fullHpRecovery--; // 所持数を1減らす
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
				m_pos.x += kLineMoveMovement;
			}
			else
			{
				m_pos.x -= kLineMoveMovement;
			}
		}
		m_pos.y = lineMoveRect.GetTop() - kPlayerHeight * kScale * kColAdjustment;
		m_isGround = true;
		m_animation = Anim::kIdle;
	}
}


/// <summary>
/// 弾の選択状態を更新
/// </summary>
/// <param name="isBuster">バスター</param>
/// <param name="isMetal">メタル</param>
/// <param name="isFire">ファイア</param>
/// <param name="isLineMove">2号</param>
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
/// マップチップと当たったときの処理
/// </summary>
/// <param name="chipRect">マップチップの当たり判定</param>
void Player::CheckHitMap(Rect chipRect)
{
	// 横から当たったかチェックする
	m_pos.x += m_move.x;
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kPlayerColX), static_cast<float>(kPlayerColY));
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_move.x > 0.0f)
		{
			m_pos.x = chipRect.GetLeft() - kPlayerWidth * kScale * 0.5f + kColChipAdjustment;
		}
		else if (m_move.x < 0.0f)
		{
			m_pos.x = chipRect.GetRight() + kPlayerWidth * kScale * 0.5f - kColChipAdjustment;
		}
	}

	// 縦から当たったかチェックする
	m_pos.y += m_move.y;
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kPlayerColX), static_cast<float>(kPlayerColY));
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_move.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kPlayerHeight * kScale * 0.5f;
			m_isGround = true;
		}
		else if (m_move.y < 0.0f)
		{
			m_pos.y = chipRect.GetBottom() + kPlayerHeight * kScale * 0.5f;
			m_move.y *= -1.0f;
		}
	}
}


/// <summary>
/// ジャンプ処理
/// </summary>
void Player::UpdateJump()
{
	m_jumpFrame++;

	//ボタンを離した瞬間にジャンプする
	if (Pad::IsRelease(PAD_INPUT_A))
	{
		// ジャンプの高さを決める
		float jumpHeight;

		if (m_jumpFrame < kPressShortJumpFrame)
		{
			jumpHeight = kLittleJumpHeight;
		}
		else if (m_jumpFrame < kPressMediumJumpFrame)
		{
			jumpHeight = kInJumpHeight;
		}
		else
		{
			jumpHeight = kLittleJumpHeight;
		}
		m_move.y *= jumpHeight;
	}
}


/// <summary>
/// バスター発射時処理
/// </summary>
void Player::UpdateShotBuster()
{
	if (Pad::IsTrigger(PAD_INPUT_B))
	{
		m_animation = Anim::kShot;
		m_shotAnimFrame = kShotAnimFrame;

		// 新しい弾を生成
		ShotBuster* pShot = new ShotBuster;
		pShot->Init();
		pShot->SetMain(m_pMain);
		pShot->SetPlayer(this);
		pShot->Start(m_pos);
		// 更新、メモリの解放はSceneMainで行う
		m_pMain->AddShot(pShot);

		// 弾発射のSEを鳴らす
		PlaySoundMem(m_shotSE, DX_PLAYTYPE_BACK, true);
	}
}


/// <summary>
/// メタル発射時処理
/// </summary>
void Player::UpdateShotMetal()
{
	if (Pad::IsTrigger(PAD_INPUT_B))
	{
		m_animation = Anim::kShot;
		m_shotAnimFrame = kShotAnimFrame;

		if (m_metalEnergy > 0)
		{
			// 新しい弾を生成
			ShotMetal* pShot = new ShotMetal;
			pShot->Init();
			pShot->SetMain(m_pMain);
			pShot->SetPlayer(this);
			pShot->Start(m_pos);
			// 更新、メモリの解放はSceneMainで行う
			m_pMain->AddShot(pShot);

			// 弾発射のSEを鳴らす
			PlaySoundMem(m_shotSE, DX_PLAYTYPE_BACK, true);

			if (pShot->IsExist())
			{
				m_metalEnergy -= kMetalDecrease;
			}
		}
		else
		{
			m_metalEnergy = 0;
		}
	}
}


/// <summary>
/// ファイア発射時処理
/// </summary>
void Player::UpdateShotFire()
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

		if (m_fireEnergy > 0)
		{
			// 長押し中SEを流す
			if (CheckSoundMem(m_shotFireSE) == 0)
			{
				PlaySoundMem(m_shotFireSE, DX_PLAYTYPE_LOOP, true);
			}
			// パーティクルの表示
			m_fireParticleFrame += kFireParticleSize;
			if (m_fireParticleFrame >= kFireParticleSize * kFireParticleFrame)
			{
				m_fireParticleFrame = 0;
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

			// 長押し時間が2秒以下
			if (m_nowPressTime > 0 && m_nowPressTime < kSmallFirePressTime)
			{
				m_fireEnergy--; // 弾エネルギーを1減らす
				m_isSmallFire = true;
				m_isMiddleFire = false;
				m_isBigFire = false;

			}
			// 長押し時間が4秒以下
			else if (m_nowPressTime < kMiddleFirePressTime)
			{
				if (m_fireEnergy - kMiddleFireDecrease < 0) // 弾エネルギーが足りない場合
				{
					m_fireEnergy--; // 弾エネルギーを1減らす
					m_isSmallFire = true;
					m_isMiddleFire = false;
					m_isBigFire = false;
				}
				else
				{
					m_fireEnergy -= kMiddleFireDecrease;
					m_isSmallFire = false;
					m_isMiddleFire = true;
					m_isBigFire = false;
				}
			}
			// 長押し時間が4秒以上
			else if (m_nowPressTime >= kMiddleFirePressTime)
			{
				if (m_fireEnergy - kBigFireDecrease < 0) // 弾エネルギーが足りない場合
				{
					m_fireEnergy--;
					m_isSmallFire = true;
					m_isMiddleFire = false;
					m_isBigFire = false;
				}
				else
				{
					m_fireEnergy -= kBigFireDecrease;
					m_isSmallFire = false;
					m_isMiddleFire = false;
					m_isBigFire = true;
				}
			}
			// 長押しされていない
			else
			{
				m_isSmallFire = true;
				m_isMiddleFire = false;
				m_isBigFire = false;
			}

			// 新しい弾を生成
			ShotFire* pShot = new ShotFire;
			pShot->Init();
			pShot->SetMain(m_pMain);
			pShot->SetPlayer(this);
			pShot->Start(m_pos);
			// 更新、メモリの解放はSceneMainで行う
			m_pMain->AddShot(pShot);
			m_nowPressTime = 0;
		}
		else
		{
			m_fireEnergy = 0;
		}
	}
}


/// <summary>
/// アイテム2号発射時処理
/// </summary>
void Player::UpdateShotLineMove()
{
	// ボタンを押したら発射
	if (Pad::IsTrigger(PAD_INPUT_B))
	{
		m_animation = Anim::kShot;
		m_shotAnimFrame = kShotAnimFrame;

		if (!m_pMain->GetIsExistLineMove() && m_lineEnergy > 0)
		{
			ShotLineMove* pShot = new ShotLineMove;
			// 新しい弾を生成
			pShot->Init();
			pShot->SetMain(m_pMain);
			pShot->SetPlayer(this);
			pShot->Start(m_pos);
			// 更新、メモリの解放はSceneMainで行う
			m_pMain->AddShot(pShot);

			// 弾発射のSEを鳴らす
			PlaySoundMem(m_shotSE, DX_PLAYTYPE_BACK, true);

			m_lineTime = kLineMoveStand;
		}
	}

	// 画面内にある場合
	if (m_pMain->GetIsExistLineMove())
	{
		m_lineTime--;
		if (m_lineTime <= 0)
		{
			m_lineEnergy -= kLineMoveDecrease; // エネルギーを減らす
		}
	}
}


/// <summary>
/// プレイヤーのHPが0以下になった場合
/// </summary>
void Player::UpdateDead()
{
	StopSoundMem(m_shotFireSE);
	StopSoundMem(m_shotSE);
	// 残機が減るごとにSEを鳴らす
	PlaySoundMem(m_deadSE, DX_PLAYTYPE_BACK, true);

	m_life--;
	m_deadFrame = kDeadFrame;
}


/// <summary>
///プレイヤーのアニメーション 
/// </summary>
void Player::UpdatePlayerAnim()
{
	//待機状態
	if (m_animation == Anim::kIdle)
	{
		m_idleAnimFrame++;
		if (m_idleAnimFrame >= kIdleAnimFrameCycle) m_idleAnimFrame = 0;
	}

	//移動状態
	else if (m_animation == Anim::kWalk)
	{
		m_walkAnimFrame++;
		if (m_walkAnimFrame >= kWalkAnimFrameCycle) m_walkAnimFrame = 0;
	}

	// ショット
	m_shotAnimFrame--;
	if (m_shotAnimFrame < 0) m_shotAnimFrame = 0;

	// ダメージ
	m_damageAnimFrame--;
	if (m_damageAnimFrame < 0) m_damageAnimFrame = 0;
}


/// <summary>
/// プレイヤーの描画
/// </summary>
void Player::DrawPlayer(int x, int y)
{
	/*画像切り出し位置を計算*/
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

	/*表示*/
	// 待機状態
	if (m_animation == Anim::kIdle && m_shotAnimFrame <= 0 && m_damageAnimFrame <= 0)
	{
		if (m_isRight)
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
		if (m_isRight)
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
		if (m_isRight)
		{
			if (m_isGround)
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
			if (m_isGround)
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
		if (m_isRight)
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
		if (m_isRight)
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
/// ファイア溜めの演出描画
/// </summary>
/// <param name="x">表示位置のX座標</param>
/// <param name="y">表示位置のY座標</param>
void Player::DrawFire(int x, int y)
{
	if (m_fireEnergy > 0 && m_nowPressTime > 0)
	{
		/*ファイアの見た目を大きくする*/
		if (m_nowPressTime < kSmallFirePressTime || m_fireEnergy < kMiddleFireDecrease)
		{
			if (m_isRight)
			{
				DrawRectRotaGraph(x + kFireParticlePositioningX, y - kFireParticlePositioningY, 
					0, 0, 
					kFireWidth, kFireHeight,
					kSmallScale, 0.0f, 
					m_fire1Handle, true);
			}
			else
			{
				DrawRectRotaGraph(x - kFireParticlePositioningX, y - kFireParticlePositioningY,
					0, 0,
					kFireWidth, kFireHeight, 
					kSmallScale, 0.0f, 
					m_fire1Handle, true);
			}
		}
		else if (m_nowPressTime < kMiddleFirePressTime && m_fireEnergy >= kMiddleFireDecrease)
		{
			if (m_isRight)
			{
				DrawRectRotaGraph(x + kFireParticlePositioningX, y - kFireParticlePositioningY, 
					0, 0, 
					kFireWidth, kFireHeight, 
					kMiddleScale, 0.0f, 
					m_fire2Handle, true);
			}
			else
			{
				DrawRectRotaGraph(x - kFireParticlePositioningX, y - kFireParticlePositioningY,
					0, 0,
					kFireWidth, kFireHeight, 
					kMiddleScale, 0.0f, 
					m_fire2Handle, true);
			}
		}
		else
		{
			if (m_isRight)
			{
				DrawRectRotaGraph(x + kFireParticlePositioningX, y - kFireParticlePositioningY,
					0, 0, 
					kFireWidth, kFireHeight,
					kBigScale, 0.0f, 
					m_fire3Handle, true);
			}
			else
			{
				DrawRectRotaGraph(x - kFireParticlePositioningX, y - kFireParticlePositioningY,
					0, 0, 
					kFireWidth, kFireHeight,
					kBigScale, 0.0f,
					m_fire3Handle, true);
			}
		}

		/*パーティクルの表示*/
		SetDrawBlendMode(DX_BLENDMODE_ADD, 100);
		if (m_isRight)
		{
			DrawRectRotaGraph(x + kFireParticlePositioningX, y - kFireParticlePositioningY, 
				m_fireParticleFrame, 0, 
				kFireParticleSize, kFireParticleSize, 
				kFireParticleScale, 0.0f, 
				m_fireParticle, true);
		}
		else
		{
			DrawRectRotaGraph(x - kFireParticlePositioningX, y - kFireParticlePositioningY, 
				m_fireParticleFrame, 0, 
				kFireParticleSize, kFireParticleSize, 
				kFireParticleScale, 0.0f, 
				m_fireParticle, true);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

