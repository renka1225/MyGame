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
	enum class State
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

	void Init();
	void Update(const Input& input, const Camera& camera, Stage& stage);
	void Draw();

	// 攻撃を受けた際の処理
	void OnDamage();
	// 当たり判定をチェックする
	void CheckHitEnemyCol(EnemyBase& enemy, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);

	const VECTOR GetPos() const { return m_pos; }	// 現在地取得
	float GetHp() const { return m_hp; }			// 現在のHPを取得
	bool GetIsMove() const { return m_isMove; }		// 移動中かどうか取得

private:
	// 当たり判定の位置更新
	void UpdateCol();
	// 移動処理
	void Move(const VECTOR& MoveVector, Stage& stage);
	// 回避処理
	State Avoidance(const Input& input, VECTOR& moveVec);
	// 移動パラメータを設定する
	State UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// 攻撃処理
	State Attack(const Input& input);
	// プレイヤーの回転を制御する
	void UpdateAngle();
	// アニメーションステートの更新
	void UpdateAnimState(State prevState);
	// アニメーション処理
	void UpdateAnim();
	// アニメーションを再生する
	void PlayAnim(AnimKind PlayAnimIndex);

private:
	std::shared_ptr<UIGauge> m_pUIGauge;

	// プレイヤー情報
	float m_gauge;				// ゲージ量
	VECTOR m_pos;				// 位置
	bool m_isMove;				// 移動したかどうか(true:移動した)
	bool m_isAttack;			// 攻撃中かどうか(ture:攻撃中)
	VECTOR m_targetMoveDir;		// 向くべき方向のベクトル
	float m_angle;				// 向いている方向の角度
	float m_moveSpeed;			// 移動速度
	State m_currentState;		// 現在の状態
	int m_modelHandle;			// プレイヤーの3Dモデル

	// アニメーション情報
	int m_currentPlayAnim;		// 再生中のアニメーションのアタッチ番号
	float m_currentAnimCount;	// 再生中のアニメーションの再生時間
	int m_prevPlayAnim;			// 前の再生アニメーションのアタッチ番号
	float m_prevAnimCount;		// 前の再生アニメーションの再生時間
	float m_animBlendRate;		// 現在と過去のアニメーションのブレンド率

	// プレイヤーの当たり判定情報
	struct CollisionInfo
	{
		VECTOR hitTopPos;		// プレイヤー全体の当たり判定の上部分
		VECTOR hitBottomPos;	// プレイヤー全体の当たり判定の下部分
		VECTOR armTopPos;		// プレイヤーの腕の先端位置
		VECTOR armStartPos;		// プレイヤーの腕の位置
		VECTOR armEndPos;		// プレイヤーの腕の位置
		VECTOR legStartPos;		// プレイヤーの脚の位置
		VECTOR legEndPos;		// プレイヤーの脚の位置
	};
	CollisionInfo m_col;
};

