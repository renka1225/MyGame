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

	// アニメーション種別
	enum class AnimKind
	{
		kNone = -1,		// なし
		kUnKnown = 0,	// 不明
		kStand = 4,		// 待機
		kRun = 3,		// 移動
	};

	Player();
	~Player();

	void Init();
	void Update(const Input& input, const Camera& camera, Stage& stage);
	void Draw();

	void OnHitFloor();	// 床に当たった時

	const VECTOR GetPos() const { return m_pos; }	// プレイヤーの現在地取得
	bool GetIsMove() const { return m_isMove; }		// 移動中かどうか取得

private:
	// 移動処理
	void Move(const VECTOR& MoveVector, Stage& stage);
	// 移動パラメータを設定する
	State UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// プレイヤーの回転を制御する
	void UpdateAngle();
	// アニメーションステートの更新
	void UpdateAnimState(State prevState);
	// アニメーション処理
	void UpdateAnim();
	// アニメーションを再生する
	void PlayAnim(AnimKind PlayAnimIndex);

private:
	// プレイヤー情報
	VECTOR m_pos;				// 位置
	bool m_isMove;				// 移動したかどうか(true:移動した)
	VECTOR m_targetMoveDir;		// 向くべき方向のベクトル
	float m_angle;				// 向いている方向の角度
	float m_jumpPower;			// Y軸方向の速度
	float m_moveSpeed;			// 移動速度
	State m_currentState;		// 現在の状態
	int m_modelHandle;			// プレイヤーの3Dモデル

	// アニメーション情報
	int m_currentPlayAnim;		// 再生中のアニメーションのアタッチ番号
	float m_currentAnimCount;	// 再生中のアニメーションの再生時間
	int m_prevPlayAnim;			// 前の再生アニメーションのアタッチ番号
	float m_prevAnimCount;		// 前の再生アニメーションの再生時間
	float m_animBlendRate;		// 現在と過去のアニメーションのブレンド率
};

