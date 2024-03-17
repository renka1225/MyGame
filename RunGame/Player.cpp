#include "Player.h"
#include "Input.h"
#include "ManagerModel.h"

/// <summary>
/// 定数
/// </summary>
namespace
{
	// 移動量
	constexpr float kMove = 0.5f;
	// 重力
	constexpr float kGravity = 0.5f;
	// 初速度
	constexpr float kVelocity = 10.0f;
	// Y軸方向の向き
	constexpr float kDirY = -90.0f * DX_PI_F / 180.0f;
	// サイズ
	constexpr float kScale = 0.5f;

	// 地面の高さ
	constexpr float kGroundHeight = 0.0f;
}

/// <summary>
/// ジャンプ関連の定数
/// </summary>
namespace Jump
{
	// ジャンプフレーム
	constexpr int kLittleJumpFrame = 10;		// 小ジャンプ
	constexpr int kMediumJumpFrame = 30;		// 中ジャンプ
	// ジャンプの高さ
	constexpr float kLittleJumpHeight = 0.5f;	// 小ジャンプ
	constexpr float kMediumJumpHeight = 0.8f;	// 中ジャンプ
	constexpr float kBigJumpHeight = 1.0f;		// 大ジャンプ
}

Player::Player(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_pos(VGet(0.0f, kGroundHeight, 0.0f)),
	m_move(VGet(0.0f, 0.0f, 0.0f)),
	m_isJump(false),
	m_jumpFrame(0)
{
	m_modelHandle = MV1DuplicateModel(m_pModel->GetPlayerHandle());
}


/// <summary>
/// 初期化
/// </summary>
void Player::Init()
{
}


/// <summary>
/// 更新
/// </summary>
void Player::Update(Input& input)
{
	// 毎フレーム右に移動
	m_pos = VAdd(m_pos, VGet(kMove, 0.0f, 0.0f));

	if (m_isJump)	// ジャンプ中
	{
		Jump(input);
	}
	else			// 着地中
	{
		m_jumpFrame = 0;
		m_isJump = false;

		// ジャンプ開始
		if (input.IsTriggered("jump"))
		{
			m_isJump = true;
			m_move = VAdd(m_move, VGet(0.0f, kVelocity, 0.0f));
		}
	}

	// 着地処理
	VECTOR rangeGround = VSub(m_pos, VGet(0.0f, kGroundHeight, 0.0f));	// 地面までの距離
	if (rangeGround.y < 0.0f)
	{
		m_pos.y = kGroundHeight;
		m_move.y = 0;
		m_isJump = false;
	}

	// 3Dモデルのサイズを決定
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	// 3DモデルをY軸方向に回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, kDirY, 0.0f));
	// 3Dモデルの位置を更新
	m_pos = VAdd(m_pos, m_move);
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG
	// MEMO:プレイヤーの座標描画
	DrawFormatString(0, 20, 0xffffff, "プレイヤー座標(x:%f,y:%f,z:%f)\n", m_pos.x, m_pos.y, m_pos.z);
	// MEMO:地面位置描画
	DrawLine3D(VGet(-100, kGroundHeight, 0), VGet(10000, kGroundHeight, 0), 0x0000ff);
#endif

}


/// <summary>
/// 終了
/// </summary>
void Player::End()
{
}


/// <summary>
/// ジャンプ処理
/// </summary>
void Player::Jump(Input& input)
{
	m_jumpFrame++;

	// ボタンを離した瞬間ジャンプ
	if (input.IsReleased("jump"))
	{
		// ジャンプの高さを決める
		float jumpHeight;
		if (m_jumpFrame < Jump::kLittleJumpFrame)
		{
			jumpHeight = Jump::kLittleJumpHeight;
		}
		else if(m_jumpFrame < Jump::kMediumJumpFrame)
		{
			jumpHeight = Jump::kMediumJumpHeight;
		}
		else
		{
			jumpHeight = Jump::kBigJumpHeight;
		}
		m_move.y = VDot(m_move, VGet(0.0f,jumpHeight, 0.0f));
	}

	m_move = VSub(m_move, VGet(0.0f, kGravity, 0.0f));
}