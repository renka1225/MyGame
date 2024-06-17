#include "DxLib.h"
#include "Stage.h"
#include "Camera.h"
#include "Input.h"
#include "DrawDebug.h"
#include "Player.h"

// 定数
namespace
{
	constexpr float kScale = 0.1f;		// プレイヤーモデルの拡大率
	constexpr float kMove = 1.3f;		// プレイヤー移動量
	constexpr float kAngleSpeed = 0.2f;	// プレイヤー角度の変化速度
	constexpr float kVelocity = 6.0f;	// ジャンプの高さ
	constexpr float kGravity = -0.25f;	// 重力
	const VECTOR kInitPos = VGet(100.0f, 20.0f, -79.0f); // 初期位置

	constexpr float kAnimBlendMax = 1.0f;	// アニメーションブレンドの最大値
	constexpr float kAnimBlendSpeed = 0.1f;	// アニメーションブレンドの変化速度
}


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player():
	m_pos(kInitPos),
	m_isMove(false),
	m_targetMoveDir(VGet(0.0f, 0.0f, 0.0f)),
	m_angle(0.0f),
	m_jumpPower(0.0f),
	m_modelHandle(-1),
	m_currentState(State::kStand),
	m_currentPlayAnim(-1),
	m_currentAnimCount(0.0f),
	m_prevPlayAnim(-1),
	m_prevAnimCount(0.0f),
	m_animBlendRate(1.0f)
{
	m_modelHandle = MV1LoadModel("data/model/player.mv1");
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
	// パッド入力によって移動パラメータを設定する
	VECTOR	upMoveVec;		// 上ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	leftMoveVec;	// 左ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	moveVec;		// このフレームの移動ベクトル
	State prevState = m_currentState;
	m_currentState = UpdateMoveParameter(input, camera, upMoveVec, leftMoveVec, moveVec);

	// アニメーション状態の更新
	UpdateAnimState(prevState);

	// プレイヤーの移動方向を設定
	UpdateAngle();

	// 移動ベクトルを元にプレイヤーを移動させる
	Move(moveVec, stage);

	// アニメーション処理
	UpdateAnim();
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw(DrawDebug& drawDebug)
{
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG	// デバッグ表示
	// プレイヤー位置表示
	drawDebug.DrawPlayerInfo(m_pos);
#endif
}


/// <summary>
/// 天井に当たった時
/// </summary>
void Player::OnHitRoof()
{
	// Y軸方向の速度を反転する
	m_jumpPower *= -1;
}


/// <summary>
/// 床に当たったとき
/// </summary>
void Player::OnHitFloor()
{
	m_jumpPower = 0.0f;

	// ジャンプ中の場合
	if (m_currentState == State::kJump)
	{
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
}


/// <summary>
/// 落下中
/// </summary>
void Player::OnFall()
{
	if (m_currentState != State::kJump)
	{
		// ジャンプ中(落下中)にする
		m_currentState = State::kJump;
	}
}


/// <summary>
/// プレイヤーの移動処理
/// </summary>
void Player::Move(const VECTOR& MoveVector, Stage& stage)
{
	if (fabs(MoveVector.x) > 0.01f || fabs(MoveVector.z) > 0.01f)
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

	// プレイヤーの移動方向ベクトルを求める

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

	// プレイヤーがジャンプ中でなく、ボタンが押されたらジャンプする
	if (m_currentState != State::kJump && input.IsTriggered("jump"))
	{
		// Y軸方向の速度をセット
		m_jumpPower = kVelocity;

		// 状態を「ジャンプ」にする
		nextState = State::kJump;
	}

	// ジャンプ中は重力を反映する
	if (m_currentState == State::kJump)
	{
		m_jumpPower += kGravity;
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
		// プレイヤーの移動ベクトルを設定する
		moveVec = VScale(m_targetMoveDir, kMove);
	}
	// 移動しない場合
	else
	{
		// 移動状態だったら
		if (m_currentState == State::kRun)
		{
			// 待機状態にする
			nextState = State::kStand;
		}
	}

	// 移動ベクトルのY成分をY軸方向の速度にする
	moveVec.y = m_jumpPower;

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


/// <summary>
/// アニメーション状態の更新
/// </summary>
/// <param name="prevState">現在の状態</param>
void Player::UpdateAnimState(State prevState)
{
	// 待機状態から移動に変わった場合
	if (prevState == State::kStand && m_currentState == State::kRun)
	{
		// 移動アニメーションを再生する
		PlayAnim(State::kRun);
	}
	// 移動から待機状態に変わった場合
	else if (prevState == State::kRun && m_currentState == State::kStand)
	{
		// 待機アニメーションを再生する
		PlayAnim(State::kStand);
	}
	// ジャンプ中の場合
	else if (m_currentState == State::kJump)
	{
		// 落下していて、再生中のアニメーションが上昇中用だった場合
		if (m_jumpPower < 0.0f)
		{
			// 落下アニメーションを再生する
			if (MV1GetAttachAnim(m_modelHandle, m_currentPlayAnim) == static_cast<int>(State::kJump))
			{
				PlayAnim(State::kFall);
			}
		}
		else
		{
			PlayAnim(State::kJump);
		}
	}
}


/// <summary>
/// TODO:アニメーション処理
/// </summary>
void Player::UpdateAnim()
{
	float animTotalTime; // 再生中のアニメーション時間

	// ブレンド率が1以下の場合
	if (m_animBlendRate < kAnimBlendMax)
	{
		m_animBlendRate += kAnimBlendSpeed;
		if (m_animBlendRate > kAnimBlendMax)
		{
			m_animBlendRate = kAnimBlendMax;
		}
	}

	// 現在再生中のアニメーションの処理
	if (m_currentPlayAnim != -1)
	{
	}

	// 1つ前に再生していたアニメーションの処理
	if (m_prevPlayAnim != -1)
	{
	}
}


/// <summary>
/// アニメーションを再生する
/// </summary>
/// <param name="playAnim">再生するアニメーション状態</param>
void Player::PlayAnim(State playAnim)
{
	// 1つ前のアニメーションがある場合削除する
	if (m_prevPlayAnim != -1)
	{
		MV1DetachAnim(m_modelHandle, m_prevPlayAnim);
		m_prevPlayAnim = -1;
	}

	// 再生中だったアニメーションを1つ前に移動する
	m_prevPlayAnim = m_currentPlayAnim;
	m_prevAnimCount = m_currentAnimCount;

	// 新たにアニメーションをアタッチする
	m_currentPlayAnim = MV1AttachAnim(m_modelHandle, static_cast<int>(playAnim));
	m_currentAnimCount = 0.0f;

	// ブレンド率はPrevが有効でない場合、1.0にする
	if (m_prevPlayAnim == -1)
	{
		m_animBlendRate = kAnimBlendMax;
	}
	else
	{
		m_animBlendRate = 0.0f;
	}
}
