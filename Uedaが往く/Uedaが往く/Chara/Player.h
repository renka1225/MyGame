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
	Player();
	~Player();
	virtual void Init() override;
	void Update(const Input& input, const Camera& camera, EnemyBase& enemy, Stage& stage);
	virtual void Draw() override;

	// ダメージを受けた際の処理
	virtual void OnDamage(float damage) override;
	// 回復処理
	void Recovery();
	// エネミーとの当たり判定をチェックする
	void CheckHitEnemyCol(EnemyBase& enemy, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);

	bool GetIsMove() const { return m_isMove; }			// 移動中かどうか取得
	VECTOR GetDir() const { return m_targetMoveDir; }	// プレイヤーの向きベクトルを取得

private:
	// 移動処理
	void Move(const VECTOR& moveVec, Stage& stage);
	// パンチ攻撃処理
	void Punch(const Input& input);
	// キック攻撃処理
	void Kick(const Input& input);
	// 回避処理
	void Avoidance(const Input& input, VECTOR& moveVec);
	// 構え処理
	void Fighting(const Input& input);
	// ガード処理
	void Guard(const Input& input);
	// ガード状態を解除する
	void OffGuard();
	// 移動パラメータを設定する
	CharacterBase::State UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// プレイヤーの回転を制御する
	void UpdateAngle(EnemyBase& enemy);
	// アニメーション処理
	virtual void UpdateAnim() override;

private:
	// プレイヤー情報
	float m_gauge;				// ゲージ量
	int m_punchCount;			// 現在のパンチのコンボ数
	int m_punchComboTime;		// コンボ入力受付時間
	int m_punchCoolTime;		// パンチできない時間
	int m_avoidCoolTime;		// 回避できない時間
	int m_avoidCount;			// 回避した回数
	bool m_isMove;				// 移動したかどうか(true:移動した)
	bool m_isFighting;			// 構え中かどうか(true:構え中)
	VECTOR m_targetMoveDir;		// 向くべき方向のベクトル
};
