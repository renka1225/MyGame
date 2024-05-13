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
	m_angle(0.0f),
	m_cameraAngle(0.0f),
	m_isClear(false)
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
/// 初期化
/// </summary>
void Player::Init()
{
	// 処理なし
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">ボタン入力</param>
void Player::Update(Input& input)
{
//#ifdef _DEBUG
//	// MEMO:デバッグ移動用
//	if (input.IsPressing("down"))
//	{
//		m_pos.z -= 1.0f;
//	}
//	if (input.IsPressing("up"))
//	{
//		m_pos.z += 1.0f;
//	}
//#endif

	m_pos = VAdd(m_pos, VGet(0.0f, kGravity, 0.0f));

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

	// ３Ｄモデルの描画
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
	m_pos = VAdd(m_pos, VGet(0.0f, kJumpHeight, kMoveZ));
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
	else
	{
		// プレイヤーを回転させる
		m_angle += kRotRad;
		MATRIX scaleMtx = MGetScale(VGet(kScale, kScale, kScale));	// プレイヤーのサイズを調整
		MATRIX transMxt = MGetTranslate(VGet(kClearInitPosX, 0.0f, kClearInitPosZ));
		m_rotMtx = MGetRotY(m_angle);

		m_modelMtx = MMult(scaleMtx, transMxt);
		m_modelMtx = MMult(m_modelMtx, m_rotMtx);

		MATRIX mtx = MGetRotY(-m_cameraAngle - DX_PI_F / 2);
		m_move = VTransform(m_move, mtx);

		// 一定の位置でプレイヤーを移動させる
		if (m_pos.z <= kClearInitPosZ && m_pos.z >= kClearEndPosZ)
		{
			m_move = VGet(0.0f, 0.0f, -kClearMove);
		}
		if (m_pos.z <= -kClearEndPosZ)
		{
			m_move.z *= -1;
		}
		if (m_pos.x >= -kClearInitPosX && m_pos.x <= kClearEndPosX)
		{
			m_move = VGet(kClearMove, 0.0f, 0.0f);
		}
		else
		{
			m_move.x *= -1;
		}

		m_angle = -atan2f(m_move.z, m_move.x) - DX_PI_F / 2;
		MV1SetMatrix(m_model, m_modelMtx);

		m_pos = VAdd(m_pos, m_move);
	}
}
