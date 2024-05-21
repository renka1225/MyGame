#include "Player.h"
#include "Input.h"


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player():
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_move(VGet(0.0f, 0.0f, 0.0f))
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
void Player::Update()
{
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	MV1DrawModel(m_modelHandle);
}
