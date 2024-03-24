#include "Enemy.h"
#include "ManagerModel.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pModel">3Dモデル</param>
Enemy::Enemy(std::shared_ptr<ManagerModel> pModel) :
	m_pModel(pModel),
	m_pos(VGet(0.0f, 0.0f, 0.0f))
{
	m_modelHandle = MV1DuplicateModel(m_pModel->GetEnemyHandle());

	// 3Dモデルの縮小
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	// 3DモデルをY軸方向に回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, kDirY, 0.0f));
}


/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
/// 初期化
/// </summary>
void Enemy::Init(VECTOR pos)
{
	m_pos = pos;
}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update()
{
	// 敵配置
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
