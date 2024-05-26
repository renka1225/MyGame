#include "Player.h"
#include "Stage.h"
#include "DrawDebug.h"
#include "Input.h"


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player():
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_move(VGet(0.0f, 0.0f, 0.0f)),
	m_angle(0.0f),
	m_jumpFrame(0),
	m_isJump(false),
	m_cameraAngle(0.0f)
{
	m_modelHandle = MV1LoadModel("data/model/player.mv1");
}


/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	MV1DeleteModel(m_modelHandle);
	m_modelHandle = -1;
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
void Player::Update(Input& input, std::shared_ptr<Stage> stage)
{
	m_stage = stage;

	// プレイヤーの移動処理
	Move(input);

	// ジャンプ処理
	if (m_isJump)	// ジャンプ中の場合
	{
		Jump(input);
	}
	else // 地面に接地している場合
	{
		m_jumpFrame = 0;
		m_pos = VGet(m_pos.x, GroundHeight(), m_pos.z);

		// ボタンを押したらジャンプ状態にする
		if (input.IsTriggered("jump"))
		{
			// 初速度を足す
			m_move = VAdd(m_move, VGet(0.0f, kVelocity, 0.0f));
			m_isJump = true;
		}
	}
	
	// 着地処理
	if (m_pos.y + m_move.y < GroundHeight())
	{
		m_pos.y = GroundHeight();
		m_isJump = false;
	}

	// プレイヤー位置、角度を更新
	m_pos = VAdd(m_pos, m_move);
	MV1SetPosition(m_modelHandle, m_pos);
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angle, 0.0f));

	// プレイヤーの傾きを調整する
	UpdateAngle();
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw(DrawDebug& drawDebug)
{
#ifdef _DEBUG	// デバッグ表示
	// プレイヤー位置表示
	drawDebug.DrawPlayerInfo(m_pos);
	// 当たり判定描画
	drawDebug.DrawCubeCol(VGet(m_pos.x, m_pos.y + kCenterPosY, m_pos.z), kWidth, kHeight, kDepth, 0x00ffff);
#endif

	// 3Dモデル表示
	MV1DrawModel(m_modelHandle);
}


/// <summary>
/// 移動処理
/// </summary>
/// <param name="input">入力</param>
void Player::Move(Input& input)
{
	m_move = VGet(0.0f, 0.0f, 0.0f);

	// ボタンを押したら移動
	if (input.IsPressing("up"))
	{
		m_move = VAdd(m_move, VGet(0.0f, 0.0f, kMove));
	}
	if (input.IsPressing("down"))
	{
		m_move = VAdd(m_move, VGet(0.0f, 0.0f, -kMove));
	}
	if (input.IsPressing("left"))
	{
		m_move = VAdd(m_move, VGet(-kMove, 0.0f, 0.0f));
	}
	if (input.IsPressing("right"))
	{
		m_move = VAdd(m_move, VGet(kMove, 0.0f, 0.0f));
	}

	// 斜めの移動速度を一定にする
	if (VSize(m_move) > 0.0f)
	{
		m_move = VNorm(m_move);
		m_move = VScale(m_move, kMove);
	}

	// 移動方向を決定する
	MATRIX mtx = MGetRotY(-m_cameraAngle - DX_PI_F / 2);
	m_move = VTransform(m_move, mtx);

	// 移動方向からプレイヤーの向く方向を決定する
	if (VSquareSize(m_move) > 0.0f)
	{
		m_angle = -atan2f(m_move.z, m_move.x) - DX_PI_F;
	}
}


/// <summary>
/// ジャンプ処理
/// </summary>
/// <param name="input">入力</param>
void Player::Jump(Input& input)
{
	// ジャンプフレームを増やす
	m_jumpFrame++;

	// ボタンを離した瞬間ジャンプ
	if (input.IsReleased("jump"))
	{
		// ジャンプの高さを決める
		float jumpHeight = 0.0f;
		if (m_jumpFrame < kLittleJumpFrame)
		{
			jumpHeight = kLittleJumpHeight;
		}
		else if (m_jumpFrame < kMediumJumpFrame)
		{
   			jumpHeight = kMediumJumpHeight;
		}
		else
		{
			jumpHeight = kBigJumpHeight;
		}
		m_move = VScale(VGet(0.0f, m_move.y, 0.0f), jumpHeight);
	}

	// 重力を足す
	m_move = VAdd(m_move, VGet(0.0f, kGravity, 0.0f));
}


/// <summary>
/// プレイヤーの傾きを調整する
/// </summary>
void Player::UpdateAngle()
{
	// プレイヤーを地面に沿って傾ける
	// 基底ベクトルを作成
	// y軸
	VECTOR v3Up = VCross(m_stage->GetV3Vec1(), m_stage->GetV3Vec2());
	v3Up = VNorm(v3Up);
	// 上下反転させる
	v3Up = VScale(v3Up, -1);

	// z軸
	VECTOR v3Forward = VGet(cosf(-m_angle), 0.0f, sinf(-m_angle));

	// x軸
	VECTOR v3Side = VCross(v3Up, v3Forward);
	v3Side = VNorm(v3Side);

	// ベクトルを直交させる
	v3Forward = VCross(v3Side, v3Up);
	v3Forward = VNorm(v3Forward);

	// z軸とy軸の方向をセットする
	MV1SetRotationZYAxis(m_modelHandle, v3Forward, v3Up, 0.0f);
}


/// <summary>
/// 地面の高さからプレイヤーのY座標を求める
/// </summary>
/// <returns>地面の高さ</returns>
float Player::GroundHeight()
{
	// 地面の傾斜の外積を計算する
	VECTOR v3Normal = VCross(m_stage->GetV3Vec1(), m_stage->GetV3Vec2());
	// y座標を求める
	return (-v3Normal.x * m_pos.x - v3Normal.z * m_pos.z) / v3Normal.y;
}
