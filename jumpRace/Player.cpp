#include "Player.h"
#include "ManagerModel.h"
#include "WorldSprite.h"
#include "Input.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player(std::shared_ptr<ManagerModel> pModel) :
	m_pModel(pModel),
	m_pos(VGet(kInitPosX, kInitPosY, kInitPosZ)),
	m_move(VGet(0.0f, 0.0f, 0.0f)),
	m_isClear(false),
	m_clearStagingTime(0),
	m_angle(0.0f)
{
	m_model = MV1DuplicateModel(m_pModel->GetPlayerModel());

	// 3Dモデルのサイズ決定
	MV1SetScale(m_model, VGet(kScale, kScale, kScale));
}


/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	MV1DeleteModel(m_model);
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">ボタン入力</param>
void Player::Update(Input& input)
{
	// クリア時
	if (m_isClear)
	{
		m_clearStagingTime++;
	}

	// 重力を足す
	m_move = VGet(0.0f, kGravity, 0.0f);
	m_pos = VAdd(m_pos, m_move);

	// 地面に着地させる
	if (m_pos.y < kInitPosX)
	{
		m_pos = VGet(0.0f, 0.0f, m_pos.z);
	}

	// ポジション設定
	MV1SetPosition(m_model, m_pos);
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// プレイ中、プレイヤーの下に影を描画する
	if (!m_isClear)
	{
		int shadowColor;
		if (m_pos.y > 0.0f)	// プレイヤーの高さによって影色を変える
		{
			shadowColor = 0x7dbd7d;
		}
		else
		{
			shadowColor = 0x008080;
		}
		SetDrawBlendMode(DX_BLENDMODE_MULA, 255);
		DrawCircle(kShadowPosX, kShadowPosY, kShadowRadius, shadowColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	// モデルの描画
	MV1DrawModel(m_model);

#ifdef _DEBUG
	// MEMO:プレイヤー座標描画
	DrawFormatString(0, 60, 0xffffff, "プレイヤー座標(x:%f,y:%f,z:%f)\n", m_pos.x, m_pos.y, m_pos.z);
#endif
}


/// <summary>
/// プレイヤーを移動させる
/// </summary>
void Player::Move()
{
	m_move = VGet(0.0f, kJumpHeight, kMoveZ);
	m_pos = VAdd(m_pos, m_move);
}


/// <summary>
/// クリア時の演出
/// </summary>
void Player::ClearStaging()
{
	if (!m_isClear)
	{
		m_pos = VGet(kClearInitPosX, 0.0f, kClearInitPosZ);	// プレイヤーを移動させる
		m_isClear = true;
	}
	else if(m_clearStagingTime >= kClearStagingStartTime)
	{
		// プレイヤーを回転させる
		m_angle += kRotRad;
		MV1SetRotationXYZ(m_model, VGet(0.0f, m_angle * DX_PI_F / 180.0f, 0.0f));

		// 数フレームごとにジャンプさせる
		int jumpFrame = m_clearStagingTime % 40;
		if (jumpFrame == kJumpFrame)
		{
			m_pos = VAdd(m_pos, VGet(0.0f, kJumpHeight, 0.0f));
		}
	}
}
