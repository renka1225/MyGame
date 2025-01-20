#pragma once

class Stage;
class Camera;
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
		kStand, // 待機
		kFall,	// 落下中
		kJump,	// ジャンプ中
		kRun	// 移動
	};

	// アニメーション種別
	enum class AnimKind
	{
		kNone = -1,		// なし
		kUnKnown = 0,	// 不明
		kStand = 36,	// 待機
		kFall = 40,		// 落下
		kJump = 42,		// ジャンプ
		kRun = 48,		// 移動
	};

	Player();
	~Player();

	void Init();
	void Update(const Input& input, const Camera& camera, Stage& stage);
	void Draw(DrawDebug& drawDebug);

	void OnHitRoof();	// 天井に当たった時
	void OnHitFloor();	// 床に当たった時
	void OnFall();		// 落下が確定したとき

	const VECTOR GetPos() const { return m_pos; }		// プレイヤーの現在地取得
	bool GetIsMove() const { return m_isMove; }			// 移動中かどうか取得
	State GetState() const { return m_currentState; }	// プレイヤーの現在の状態を取得
	float GetJumpPower() const { return m_jumpPower; }	// プレイヤーのジャンプ量取得
	bool GetIsGoal() const { return m_isGoal; }			// プレイヤーがゴールしたか取得する

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
	bool m_isGoal;				// プレイヤーがゴールしたか
	int m_modelHandle;			// プレイヤーの3Dモデル
	State m_currentState;		// 現在の状態

	// アニメーション情報
	int m_currentPlayAnim;		// 再生中のアニメーションのアタッチ番号
	float m_currentAnimCount;	// 再生中のアニメーションの再生時間
	int m_prevPlayAnim;			// 前の再生アニメーションのアタッチ番号
	float m_prevAnimCount;		// 前の再生アニメーションの再生時間
	float m_animBlendRate;		// 現在と過去のアニメーションのブレンド率
};

