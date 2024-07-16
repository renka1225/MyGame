#pragma once
#include "CharacterBase.h"
#include <memory>

class Stage;
class EnemyBase;
class Camera;
class Input;
class UIGauge;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public CharacterBase 
{
public:
	// プレイヤーの状態
	enum class PlayerState
	{
		kAvoid = 0,		// 回避
		kDown = 1,		// 倒れる
		kFightIdle = 2, // 構え
		kGettingUp = 3, // 起き上がる
		kGrab = 4,		// 掴み
		kGuard = 5,		// ガード
		kKick = 6,		// キック
		kPunch = 7,		// パンチ
		kComboPunch = 8,// コンボパンチ
		kReceive = 9,	// 攻撃を受ける
		kRun = 10,		// 移動
		kStand = 11,	// 待機
		kStumble,		// 掴み失敗
	};

	// アニメーション種別
	enum class AnimKind
	{
		kNone = -1,		// なし
		kAvoid = 0,		// 回避
		kDown = 1,		// 倒れる
		kFightIdle = 2, // 構え
		kGettingUp = 3, // 起き上がる
		kGrab = 4,		// 掴み
		kGuard = 5,		// ガード
		kKick = 6,		// キック
		kPunch = 7,		// パンチ
		kComboPunch = 8,// コンボパンチ
		kReceive = 9,	// 攻撃を受ける
		kRun = 10,		// 移動
		kStand = 11,	// 待機
		kStumble,		// 掴み失敗
	};

	Player();
	~Player();

	virtual void Init() override;
	void Update(const Input& input, const Camera& camera, Stage& stage);
	virtual void Draw() override;

	// 攻撃を受けた際の処理
	virtual void OnDamage(float damage) override;
	// 当たり判定をチェックする
	void CheckHitEnemyCol(EnemyBase& enemy, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);

	const VECTOR GetPos() const { return m_pos; }	// 現在地取得
	float GetHp() const { return m_hp; }			// 現在のHPを取得
	bool GetIsMove() const { return m_isMove; }		// 移動中かどうか取得

private:
	// 当たり判定の位置更新
	void UpdateCol();
	// 移動処理
	void Move(const VECTOR& moveVec, Stage& stage);
	// 回避処理
	PlayerState Avoidance(const Input& input, VECTOR& moveVec);
	// 移動パラメータを設定する
	PlayerState UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// 攻撃処理
	PlayerState Attack(const Input& input);
	// プレイヤーの回転を制御する
	void UpdateAngle();
	// アニメーションステートの更新
	void UpdateAnimState(PlayerState prevState);
	// アニメーション処理
	void UpdateAnim();
	// アニメーションを再生する
	void PlayAnim(AnimKind PlayAnimIndex);

private:
	// プレイヤー情報
	float m_gauge;				// ゲージ量
	bool m_isMove;				// 移動したかどうか(true:移動した)
	bool m_isAttack;			// 攻撃中かどうか(ture:攻撃中)
	VECTOR m_targetMoveDir;		// 向くべき方向のベクトル
	PlayerState m_currentState;	// 現在の状態

};
