#pragma once
#include "CharacterBase.h"
#include <memory>

class Player;
class Stage;

/// <summary>
/// 敵の基底クラス
/// </summary>
class EnemyBase : public CharacterBase
{
public:
	// エネミーの状態
	enum class EnemyState
	{
		kAvoid = 0,		// 回避
		kDown = 1,		// 倒れる
		kFightIdle = 2, // 構え(停止中)
		kFightWalk = 3, // 構え(移動中)
		kGettingUp = 4, // 起き上がる
		kGrab = 5,		// 掴み
		kGuard = 6,		// ガード
		kKick = 7,		// キック
		kPunch = 8,		// パンチ
		kComboPunch = 9,// コンボパンチ
		kReceive = 10,	// 攻撃を受ける
		kRun = 11,		// 移動
		kStand = 12,	// 待機
		kStumble = 13,	// 掴み失敗
	};

	EnemyBase();
	virtual ~EnemyBase();
	virtual void Init() = 0;
	virtual void Update(Player& player, Stage& stage) = 0;
	virtual void Draw() = 0;

	// プレイヤーとの当たり判定をチェックする
	void CheckHitPlayerCol(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);

	float GetHp() const { return m_hp; }	// 敵のHPを取得
	VECTOR GetPos() const { return m_pos; } // 敵の座標を取得

protected:
	// 敵の次の行動を決める
	void DecideNextAction();
	// 移動処理
	void Move(const VECTOR& moveVec, Player& player, Stage& stage);
	// 移動パラメータを設定する
	EnemyState UpdateMoveParameter(Player& player, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// 攻撃処理
	EnemyState Attack();
	// 敵の角度を更新
	void UpdateAngle(Player& player);
	// アニメーションステートの更新
	void UpdateAnimState(EnemyState prevState);
	// アニメーション処理
	virtual void UpdateAnim() override;

protected:
	bool m_isMove;				// 移動したかどうか(true:移動した)
	bool m_isAttack;			// 攻撃中かどうか(ture:攻撃中)
	int m_stopFrame;			// 停止するフレーム数
	int m_angleFrame;			// 角度を更新するフレーム数
	EnemyState m_currentState;	// エネミーの現在の状態
};

