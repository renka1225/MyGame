#include "Player.h"
#include "Input.h"


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player():
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_move(VGet(0.0f, 0.0f, 0.0f)),
	m_jumpFrame(0),
	m_isJump(false)
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
	MV1SetPosition(m_modelHandle, m_pos);
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
}


/// <summary>
/// 更新
/// </summary>
void Player::Update(Input& input)
{
	// プレイヤーの移動処理
	Move(input);

	// ジャンプ処理
	if (m_isJump)	// ジャンプ中
	{
		Jump(input);
	}
	else
	{
		m_jumpFrame = 0;
		m_isJump = false;

		// ボタンを押したらジャンプ状態にする
		if (input.IsTriggered("jump"))
		{
			// 初速度を足す
			m_move = VAdd(m_move, VGet(0.0f, kVelocity, 0.0f));
			m_isJump = true;
		}
	}
	
	// 着地処理
	if (m_pos.y < 0.0f)
	{
		m_isJump = false;
		m_pos = VGet(m_pos.x, 0.0f, m_pos.z);
		m_move = VGet(m_move.x, 0.0f, m_move.z);
	}

	// プレイヤー位置を更新
	m_pos = VAdd(m_pos, m_move);
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	MV1DrawModel(m_modelHandle);
}


/// <summary>
/// 移動処理
/// </summary>
/// <param name="input">入力</param>
void Player::Move(Input& input)
{
	m_move = VGet(0.0f, 0.0f, 0.0f);

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
