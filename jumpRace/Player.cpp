#include "Player.h"
#include "Input.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player():
	m_pos(VGet(kInitPosX, kInitPosY, kInitPosZ)),
	m_model(-1)
{
	m_model = MV1LoadModel("data/Model/duck.mv1");

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
	m_pos = VAdd(m_pos, VGet(0.0f, 0.0f, kMove));
}
