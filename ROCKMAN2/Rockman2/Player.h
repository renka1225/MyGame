#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneStage1;
class Bg;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	~Player();

	// マップのポインタを設定する
	void SetBg(Bg* pBg) { m_pBg = pBg; }
	void SetStage(SceneStage1* pStage1) { m_pStage1 = pStage1; }

	void Init();
	void Update();
	void Draw();

	// プレイヤーの表示
	void DrawPlayer();
	// マップチップとの当たり判定の処理
	void CheckHitMap(Rect chipRect);

	// プレイヤーがダメージを受けた時の処理
	void OnDamage();
	// プレイヤーがE缶取得処理
	void GetHpFullRecovery();
	// プレイヤーの回復処理
	void HpSmallRecovery();		// HP小回復
	void HpGreatRecovery();		// HP大回復
	void ShotSmallRecovery();	// 弾小回復
	void ShotGreatRecovery();	// 弾大回復
	void LifeRecovery();		// 残機回復
	void HpFullRecovery();		// HP全回復

	// アイテム2号に乗った際の処理
	void RideLineMove(Rect shotRect);

	// 現在の武器選択状態を更新する
	void ChangeShot(bool isBuster, bool isMetal, bool isFire, bool isLineMove);

public:
	// 現在位置を更新する
	void SetPos(Vec2 pos) { m_pos = pos; }
	// プレイヤーの現在の向きを取得する
	bool GetDir() const { return m_isRight; }
	// プレイヤーの現在座標を取得する
	Vec2 GetPos() const { return m_pos; }
	// プレイヤーの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

	// 現在のHPを取得する
	int GetHp() const { return m_hp; }
	// 現在の残機数を取得する
	int GetLife() const { return m_life; }
	// 現在のE缶数を取得
	int GetFullHpRecovery() const { return m_fullHpRecovery; }

	// 現在の弾エネルギー数を取得する
	float GetMetalEnergy() const { return m_metalEnergy; }
	float GetFireEnergy() const { return m_fireEnergy; }
	float GetLineEnergy() const { return m_lineEnergy; }

	// ファイアの状態を取得
	bool IsSmallFire() const { return m_isSmallFire; }
	bool IsMiddleFire() const { return m_isMiddleFire; }
	bool IsBigFire() const { return m_isBigFire; }

public:
	// 武器が選択中か取得する
	bool IsBuster() const { return m_isBuster; }	// バスター
	bool IsMetal() const { return m_isMetal; }		// メタル
	bool IsFire() const { return m_isFire; }		// ファイア
	bool IsLineMove() const { return m_isLineMove; }// 2号

private:
	// 背景
	Bg* m_pBg;
	SceneStage1* m_pStage1;

	// 表示位置
	Vec2 m_pos;
	// 移動量
	Vec2 m_move;
	// 当たり判定用の矩形
	Rect m_colRect;

	// 向いている方向
	bool m_isRight;
	// 地面と接しているか
	bool m_isGround;	// true:接している
	// ジャンプ中か
	bool m_isJump;
	// ジャンプ中のフレーム数
	int m_jumpFrame;

	// HP
	int m_hp;
	// 残機
	int m_life;
	// E缶
	int m_fullHpRecovery;

	// ダメージを受けてからのフレーム数
	int m_damageFrame;

	// メタルの弾エネルギー数
	float m_metalEnergy;
	// ファイヤーの弾エネルギー数
	float m_fireEnergy;
	// アイテム2号の弾エネルギー数
	float m_lineEnergy;

	// 武器を装備しているか
	bool m_isBuster; // バスター
	bool m_isMetal;	 // メタル
	bool m_isFire;	 // ファイア
	bool m_isLineMove; // 2号(直線移動する足場)

	// ボタンの状態を取得する
	int m_keyState;
	// ボタンが長押しされた時間
	int m_pressTime;
	// ボタンを押して離すまでの時間
	int m_nowPressTime;
	// ファイアのサイズ
	bool m_isSmallFire;		// 小
	bool m_isMiddleFire;	// 中
	bool m_isBigFire;		// 大
	// アイテム2号の待機時間
	int m_lineTime;

	// 音
	int m_shotSE;		// ショット時のSE
	int m_shotFireSE;	// ファイア溜め時のSE
	int m_jumpSE;		// ジャンプ時のSE
	int m_damageSE;		// ダメージ時のSE
	int m_deadSE;		// 死亡時のSE

	// 画像
	int m_idleHandle;	// 待機状態
	int m_walkHandle;	// 歩き
	int m_shotHandle;	// 攻撃
	int m_jumpHandle;	// ジャンプ
	int m_damageHandle;	// ダメージ

	// 画像のアニメーション
	enum Anim
	{
		kIdle,
		kWalk,
		kShot,
		kJump,
		kDamage
	};
	// 現在のアニメーション状態
	Anim m_animation;
	// 待機アニメーション
	int m_idleAnimFrame;
	// 移動アニメーション
	int m_walkAnimFrame;
	// 弾アニメーション
	int m_shotAnimFrame;
	// ダメージアニメーション
	int m_damageAnimFrame;
};