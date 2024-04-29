#include "Player.h"
#include "ManagerModel.h"
#include "Input.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_pos(VGet(kInitPosX, kInitPosY, kInitPosZ))
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
