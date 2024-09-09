#include "ManagerModel.h"
#include "ModelBase.h"
#include "ModelGround.h"
#include "ModelTree.h"
#include "Player.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
ManagerModel::ManagerModel()
{
	m_pGroundModel.resize(kGroundNum);
	m_pTreeModel.resize(kTreeNum);

	m_playerModel = MV1LoadModel("data/Model/rabbit.mv1");
	m_groundModel = MV1LoadModel("data/Model/tile.mv1");
	m_desertModel = MV1LoadModel("data/Model/tileDesert.mv1");
	m_treeModel = MV1LoadModel("data/Model/tree.mv1");
}


/// <summary>
/// デストラクタ
/// </summary>
ManagerModel::~ManagerModel()
{
	MV1DeleteModel(m_playerModel);
	MV1DeleteModel(m_groundModel);
	MV1DeleteModel(m_desertModel);
	MV1DeleteModel(m_treeModel);
}


/// <summary>
/// 更新
/// </summary>
void ManagerModel::Update()
{
	for (auto& model : m_pGroundModel)
	{
		model->Update();
	}
	for (auto& model : m_pTreeModel)
	{
		model->Update();
	}
}


/// <summary>
/// 描画	
/// </summary>
void ManagerModel::Draw()
{
	// 3Dモデル描画
	for (auto& model : m_pGroundModel)
	{
		model->Draw();
	}
	for (auto& model : m_pTreeModel)
	{
		model->Draw();
	}
}


/// <summary>
/// 地面の生成
/// </summary>
void ManagerModel::CreateGroundModel()
{
	for (int i = 0; i < m_pGroundModel.size(); i++)
	{
		VECTOR pos = VGet(i * kGroundPosX - kGroundPosX, kGroundPosY, kGroundPosZ);
		
		if(i == 1)
		{
			m_pGroundModel[i] = std::make_shared<ModelGround>(m_groundModel, pos);
		}
		else
		{
			pos = VGet(i * kGroundPosX - kGroundPosX, kDesertGroundPosY, kGroundPosZ);
			m_pGroundModel[i] = std::make_shared<ModelGround>(m_desertModel, pos);
		}
	}
}


/// <summary>
/// 木の生成
/// </summary>
void ManagerModel::CreateTreeModel()
{
	for (int i = 0; i < m_pTreeModel.size(); i++)
	{
		VECTOR pos = VGet(0.0f, 0.0f, kTreeInitPosZ);
		if (i < kTreeColNum)
		{
			pos = VAdd(pos, VGet(-kTreePosX, kTreePosY, i * kTreePosZ));
		}
		else
		{
			pos = VAdd(pos, VGet(kTreePosX, kTreePosY, (i - kTreeColNum) * kTreePosZ));
		}
		m_pTreeModel[i] = std::make_shared<ModelTree>(m_treeModel, pos);
	}
}