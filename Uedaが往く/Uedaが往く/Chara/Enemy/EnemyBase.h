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
	EnemyBase();
	virtual ~EnemyBase();
	virtual void Init() = 0;
	virtual void Update(Player& player, Stage& stage) = 0;
	virtual void Draw() = 0;

	// プレイヤーとの当たり判定をチェックする
	void CheckHitPlayerCol(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);

	float GetHp() const { return m_hp; }	// 敵のHPを取得
	VECTOR GetPos() const { return m_pos; } // 敵の座標を取得

#ifdef _DEBUG
	void DebugDamage(Input& input); // 1ボタンで敵のHPを0にする
#endif


protected:
	// 移動処理
	void Move(const VECTOR& moveVec, Player& player, Stage& stage);
	// 移動パラメータを設定する
	CharacterBase::State UpdateMoveParameter(Player& player, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// パンチ処理
	void Punch();
	// キック処理
	void kick();
	// 回避処理
	void Avoidance(VECTOR& moveVec);
	// 構え処理
	void Fighting();
	// ガード処理
	void Guard();
	// ガード状態を解除する
	void OffGuard();
	// 敵の角度を更新
	void UpdateAngle(Player& player);

protected:
	bool m_isMove;				// 移動したかどうか(true:移動した)
	bool m_isAttack;			// 攻撃中かどうか(ture:攻撃中)
	int m_stopTime;				// 停止する時間
	int m_angleIntervalTime;	// 角度を更新するまでの時間
	int m_intervalTime;			// 次の状態を更新するまでの時間
};

