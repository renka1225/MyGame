#include "Player.h"
#include "Map.h"
#include "Input.h"
#include "ManagerModel.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pModel">3Dモデル</param>
Player::Player(std::shared_ptr<ManagerModel> pModel, std::shared_ptr<Map> pMap):
	m_pModel(pModel),
	m_pMap(pMap),
	m_pos(VGet(kInitPosX, kGroundHeight, 0.0f)),
	m_move(VGet(0.0f, 0.0f, 0.0f)),
	m_isJump(false),
	m_jumpFrame(0)
{
	m_modelHandle = MV1DuplicateModel(m_pModel->GetPlayerHandle());
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
}


/// <summary>
/// 更新
/// </summary>
void Player::Update(Input& input)
{
	// 3Dモデルのサイズを決定
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	// 3DモデルをY軸方向に回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, kDirY, 0.0f));

	// 右に移動
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

	// 3Dモデルの位置を更新
	m_pos = VAdd(m_pos, m_move);
	MV1SetPosition(m_modelHandle, m_pos);

	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y + kColPosAdjustment, m_pos.z, kWidth, kHeight);

	// マップチップとの当たり判定
	Rect chipRect;	// 当たったマップチップの矩形
	CheckHitMap(chipRect);
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG
	// MEMO:プレイヤー座標描画
	DrawFormatString(0, 20, 0xffffff, "プレイヤー座標(x:%f,y:%f,z:%f)\n", m_pos.x, m_pos.y, m_pos.z);
	// MEMO:当たり判定の表示
	m_colRect.Draw(0x00fffff, false);
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
		if (m_jumpFrame < kLittleJumpFrame)
		{
			jumpHeight = kLittleJumpHeight;
		}
		else if(m_jumpFrame < kMediumJumpFrame)
		{
			jumpHeight = kMediumJumpHeight;
		}
		else
		{
			jumpHeight = kBigJumpHeight;
		}
		m_move.y = VDot(m_move, VGet(0.0f,jumpHeight, 0.0f));
	}

	m_move = VSub(m_move, VGet(0.0f, kGravity, 0.0f));
}

/// <summary>
/// マップチップとの当たり判定の処理
/// </summary>
/// <param name="chipRect">マップチップの当たり判定</param>
void Player::CheckHitMap(Rect chipRect)
{
	if (m_pMap->IsCollision(m_colRect, chipRect))
	{
#ifdef _DEBUG
		DrawFormatString(0, 100, 0x0ff0ff, "当たった\n");
#endif
	}
}
