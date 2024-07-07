#pragma once

class Stage;
class Camera;
class Input;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	// プレイヤーの状態
	enum class State
	{
		kStand, // 待機
		kRun	// 移動
	};

	Player();
	~Player();

	void Init();
	void Update(const Input& input, const Camera& camera, Stage& stage);
	void Draw();

	void OnHitFloor();	// 床に当たった時

	const VECTOR GetPos() const { return m_pos; }		// プレイヤーの現在地取得
	bool GetIsMove() const { return m_isMove; }			// 移動中かどうか取得

private:
	// 移動処理
	void Move(const VECTOR& MoveVector, Stage& stage);
	// 移動パラメータを設定する
	State UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// プレイヤーの回転を制御する
	void UpdateAngle();

private:
	// プレイヤー情報
	VECTOR m_pos;				// 位置
	bool m_isMove;				// 移動したかどうか(true:移動した)
	VECTOR m_targetMoveDir;		// 向くべき方向のベクトル
	float m_angle;				// 向いている方向の角度
	float m_moveSpeed;			// 移動速度
	State m_currentState;		// 現在の状態
	int m_modelHandle;			// プレイヤーの3Dモデル
};

