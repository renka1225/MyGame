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

	Player();
	~Player();

	virtual void Init() override;
	void Update(const Input& input, const Camera& camera, EnemyBase& enemy, Stage& stage);
	virtual void Draw() override;

	// エネミーとの当たり判定をチェックする
	void CheckHitEnemyCol(EnemyBase& enemy, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);

	bool GetIsMove() const { return m_isMove; }			// 移動中かどうか取得
	VECTOR GetDir() const { return m_targetMoveDir; }	// プレイヤーの向きベクトルを取得

private:
	// 移動処理
	void Move(const VECTOR& moveVec, Stage& stage);
	// パンチ攻撃処理
	PlayerState Punch(const Input& input);
	// キック攻撃処理
	PlayerState Kick(const Input& input);
	// 回避処理
	PlayerState Avoidance(const Input& input, VECTOR& moveVec);
	// 構え処理
	PlayerState Fighting(const Input& input);
	// ガード処理
	PlayerState Guard(const Input& input);
	// 移動パラメータを設定する
	PlayerState UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// プレイヤーの回転を制御する
	void UpdateAngle(EnemyBase& enemy);
	// アニメーションステートの更新
	void UpdateAnimState(PlayerState prevState);
	// アニメーション処理
	virtual void UpdateAnim() override;

private:
	// プレイヤー情報
	float m_gauge;				// ゲージ量
	int m_punchCount;			// 現在のパンチのコンボ数
	int m_punchComboTime;		// コンボ入力受付時間
	int m_punchCoolTime;		// パンチできない時間
	int m_avoidCount;			// 回避した回数
	int m_avoidCoolTime;		// 回避できない時間
	bool m_isMove;				// 移動したかどうか(true:移動した)
	bool m_isFighting;			// 構え中かどうか(true:構え中)
	VECTOR m_targetMoveDir;		// 向くべき方向のベクトル
	PlayerState m_currentState;	// 現在の状態
};
