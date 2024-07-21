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

	Player();
	~Player();

	virtual void Init() override;
	void Update(const Input& input, const Camera& camera, EnemyBase& enemy, Stage& stage);
	virtual void Draw() override;

	// エネミーとの当たり判定をチェックする
	void CheckHitEnemyCol(EnemyBase& enemy, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);

	bool GetIsMove() const { return m_isMove; }		// 移動中かどうか取得

private:
	// 移動処理
	void Move(const VECTOR& moveVec, Stage& stage);
	// パンチ処理
	PlayerState Punch(const Input& input);
	// キック処理
	PlayerState Kick(const Input& input);
	// 回避処理
	PlayerState Avoidance(const Input& input, VECTOR& moveVec);
	// 移動パラメータを設定する
	PlayerState UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// プレイヤーの回転を制御する
	void UpdateAngle();
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
	VECTOR m_targetMoveDir;		// 向くべき方向のベクトル
	PlayerState m_currentState;	// 現在の状態
};
