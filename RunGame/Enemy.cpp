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
	m_pModel(pModel)
{
	m_pos.resize(kEnemyNum);
	m_modelHandle = MV1DuplicateModel(m_pModel->GetEnemyHandle());

	// 3Dモデルのサイズを小さくする
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
void Enemy::Init()
{
	// TODO:敵データ読み込み
	std::fstream file;
	file.open("data/file/enemy.csv", std::ios::in | std::ios::binary);
	
	if (!file.is_open())	// ファイル読み込み失敗時
	{
		printfDx("ファイル読み込み失敗\n");
	}
	else 					// 成功時
	{
		// ファイルの中身をメモリ上にコピーする
		file.read(reinterpret_cast<char*>(&m_pos), sizeof(kEnemyNum));
		file.close();
	}
}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update()
{
	// TODO:複数配置
	for (int i = 0; i < m_pos.size(); i++)
	{
		MV1SetPosition(m_modelHandle, m_pos[i]);
	}
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
