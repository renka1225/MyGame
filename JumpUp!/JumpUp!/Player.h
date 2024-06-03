#pragma once
#include <memory>

class Stage;
class Input;
class DrawDebug;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	// プレイヤーの状態
	enum class State
	{
		Idle,	// 待機
		Run,	// 移動
		Jump,	// ジャンプ中
		Fall,	// 落下中
	};

	Player();
	virtual ~Player();
	void Init();
	void Update(Input& input, Stage& stage);
	void Draw(DrawDebug& drawDebug);
	void OnHit(Stage& stage);	// 衝突したとき

	void SetCameraAngle(float angle) { m_cameraAngle = angle; }

	VECTOR GetPos() const { return m_pos; }				// プレイヤーの現在地取得
	State GetState() const { return m_currentState; }	// プレイヤーの現在の状態を取得
	VECTOR GetMove() const { return m_move; }			// プレイヤーの移動量取得

private:
	void Move(Input& input);				// プレイヤーの移動処理
	void Jump(Input& input, Stage& state);	// プレイヤーのジャンプ処理
	void UpdateAngle(Stage& stage);			// プレイヤーの傾きを調整する
	float OnHitFloor(Stage& stage);			// 地面の位置からプレイヤーのY座標の位置を求める
	bool IsHitStage(Stage& stage);			// ステージとの当たり判定


private:
	// プレイヤー情報
	State m_currentState;		// 現在の状態
	VECTOR m_pos;				// プレイヤー位置
	VECTOR m_move;				// 移動量
	float m_angle;				// 向いている方向
	float m_jumpPower;			// Y軸方向の速度
	int m_jumpFrame;			// ジャンプフレーム
	bool m_isJump;				// ジャンプ中かどうか(true:ジャンプ中)
	int m_modelHandle;			// プレイヤーの3Dモデル

	// カメラ情報
	float m_cameraAngle;		// カメラの角度
};

