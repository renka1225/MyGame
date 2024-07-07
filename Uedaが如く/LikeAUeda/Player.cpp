#include "DxLib.h"
#include "Camera.h"
#include "Stage.h"
#include "Input.h"
#include "Player.h"

// 定数
namespace
{
	// プレイヤー情報
	constexpr float kScale = 0.3f;						// プレイヤーモデルの拡大率
	constexpr float kMaxSpeed = 3.0f;					// プレイヤーの最大移動速度
	constexpr float kAcceleration = 0.2f;				// プレイヤーの加速度
	constexpr float kDeceleration = 0.2f;				// プレイヤーの減速度
	constexpr float kAngleSpeed = 0.2f;					// プレイヤー角度の変化速度
	constexpr float kVelocity = 6.0f;					// ジャンプの高さ
	constexpr float kGravity = -0.25f;					// 重力
	const VECTOR kInitDir = VGet(0.0f, 0.0f, 0.0f);		// 初期方向
	const VECTOR kInitPos = VGet(0.0f, 0.0f, 0.0f);		// 初期位置
}


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player():
	m_pos(kInitPos),
	m_isMove(false),
	m_targetMoveDir(kInitDir),
	m_angle(0.0f),
	m_jumpPower(0.0f),
	m_moveSpeed(0.0f),
	m_currentState(State::kStand),
	m_modelHandle(-1)
{
	m_modelHandle = MV1LoadModel("data/Model/player.mv1");
}


/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
/// 初期化
/// </summary>
void Player::Init()
{
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力コマンド</param>
/// <param name="stage">ステージ情報参照</param>
void Player::Update(const Input& input, const Camera& camera, Stage& stage)
{
	/*パッド入力によって移動パラメータを設定する*/
	VECTOR	upMoveVec;		// 上ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	leftMoveVec;	// 左ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	moveVec;		// このフレームの移動ベクトル

	// プレイヤーの状態を更新
	State prevState = m_currentState;
	m_currentState = UpdateMoveParameter(input, camera, upMoveVec, leftMoveVec, moveVec);

	// プレイヤーの移動方向を設定
	UpdateAngle();

	// 移動ベクトルを元にプレイヤーを移動させる
	Move(moveVec, stage);
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG	// デバッグ表示
	DrawFormatString(0, 20, 0xffffff, "プレイヤー座標(%2f,%2f,%2f)", m_pos.x, m_pos.y, m_pos.z);
#endif
}


/// <summary>
/// 床に当たったとき
/// </summary>
void Player::OnHitFloor()
{
	m_jumpPower = 0.0f;

	// 移動中の場合
	if (m_isMove)
	{
		// 移動状態にする
		m_currentState = State::kRun;
	}
	else
	{
		// 待機状態にする
		m_currentState = State::kStand;
	}
}


/// <summary>
/// プレイヤーの移動処理
/// </summary>
void Player::Move(const VECTOR& MoveVector, Stage& stage)
{
	if (fabs(MoveVector.x) > 0.0f || fabs(MoveVector.z) > 0.0f)
	{
		m_isMove = true;
	}
	else
	{
		m_isMove = false;
	}

	// 当たり判定を行って座標を保存する
	m_pos = stage.CheckCollision(*this, MoveVector);

	// プレイヤーの座標を更新する
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// 移動パラメータを設定する
/// </summary>
/// <returns></returns>
Player::State Player::UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec)
{
	State nextState = m_currentState;

	/*プレイヤーの移動方向ベクトルを求める*/
	// 上ボタンを押したとき
	upMoveVec = VSub(camera.GetAngle(), camera.GetPos());
	upMoveVec.y = 0.0f;

	// 左ボタンを押したとき
	leftMoveVec = VCross(upMoveVec, VGet(0.0f, 1.0f, 0.0f));

	// ベクトルの正規化
	upMoveVec = VNorm(upMoveVec);
	leftMoveVec = VNorm(leftMoveVec);

	// このフレームでの移動ベクトルを初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// 移動したか(true:移動した)
	bool isPressMove = false;

	// ボタンを押したら移動
	if (input.IsPressing("up"))
	{
		moveVec = VAdd(moveVec, upMoveVec);
		isPressMove = true;
	}
	if (input.IsPressing("down"))
	{
		moveVec = VAdd(moveVec, VScale(upMoveVec, -1.0f));
		isPressMove = true;
	}
	if (input.IsPressing("left"))
	{
		moveVec = VAdd(moveVec, leftMoveVec);
		isPressMove = true;
	}
	if (input.IsPressing("right"))
	{
		moveVec = VAdd(moveVec, VScale(leftMoveVec, -1.0f));
		isPressMove = true;

	}


	// 移動ボタンが押されている場合
	if (isPressMove)
	{
		// 待機状態だった場合
		if (m_currentState == State::kStand)
		{
			// 移動状態にする
			nextState = State::kRun;
		}

		// プレイヤーが向く方向を設定する
		m_targetMoveDir = VNorm(moveVec);

		// プレイヤーの加速度を設定する
		if (m_moveSpeed < kMaxSpeed)
		{
			m_moveSpeed += kAcceleration;
			m_moveSpeed = (std::min)(m_moveSpeed, kMaxSpeed);
		}
		// プレイヤーの移動ベクトルを設定する
		moveVec = VScale(m_targetMoveDir, m_moveSpeed);
	}
	// 移動しない場合
	else
	{
		// 移動状態だったら
		if (m_currentState == State::kRun)
		{
			// 待機状態にする
			nextState = State::kStand;
			m_moveSpeed = 0.0f;
		}

		// プレイヤーを減速させる
		if (m_moveSpeed > 0.0f)
		{
			m_moveSpeed -= kDeceleration;
			m_moveSpeed = (std::max)(0.0f, m_moveSpeed);
		}
		moveVec = VScale(m_targetMoveDir, m_moveSpeed);
	}

	return nextState;
}


/// <summary>
/// プレイヤーの回転を制御する
/// </summary>
void Player::UpdateAngle()
{
	// プレイヤーの角度を更新
	m_angle = atan2f(m_targetMoveDir.x, m_targetMoveDir.z);
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle + DX_PI_F, 0.0f));
}