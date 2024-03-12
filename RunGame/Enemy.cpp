#include "Enemy.h"
#include "ManagerModel.h"

/// <summary>
/// 定数
/// </summary>
namespace
{
	// 移動量
	constexpr float kMoveX = -1.0f;
	// 拡大率
	constexpr float kScale = 0.25f;
	// Y軸方向の向き
	constexpr float kDirY = 180.0f * DX_PI_F / 180.0f;
}

Enemy::Enemy(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_move(VGet(kMoveX, 0.0f, 0.0f))
{
	m_modelHandle = MV1DuplicateModel(m_pModel->GetEnemyHandle());

	// 3Dモデルのサイズを小さくする
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	// 3DモデルをY軸方向に回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, kDirY, 0.0f));
}


Enemy::~Enemy()
{
}


/// <summary>
/// 初期化
/// </summary>
void Enemy::Init()
{
}


/// <summary>
/// 更新
/// </summary>
void Enemy::Update()
{
	// TODO:位置更新
	//m_pos = VAdd(m_pos, m_move);
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// 描画
/// </summary>
void Enemy::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);
}


/// <summary>
/// 終了
/// </summary>
void Enemy::End()
{
}
