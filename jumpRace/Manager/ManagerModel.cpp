#include "ManagerModel.h"
#include "ModelBase.h"
#include "ModelTree.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
ManagerModel::ManagerModel()
{
	m_model.resize(kTreeNum);

	m_playerModel = MV1LoadModel("data/Model/rabbit.mv1");
	m_groundModel = MV1LoadModel("data/model/tile.mv1");
	m_treeModel = MV1LoadModel("data/model/tree.mv1");
}


/// <summary>
/// デストラクタ
/// </summary>
ManagerModel::~ManagerModel()
{
	MV1DeleteModel(m_playerModel);
	MV1DeleteModel(m_groundModel);
	MV1DeleteModel(m_treeModel);
}


/// <summary>
/// 更新
/// </summary>
void ManagerModel::Update()
{
	for (auto& model : m_model)
	{
		model->Update();
	}
}


/// <summary>
/// 描画	
/// </summary>
void ManagerModel::Draw()
{
	for (auto& model : m_model)
	{
		model->Draw();
	}
}

/// <summary>
/// 木の生成
/// </summary>
void ManagerModel::GreateTreeModel()
{
	for (int i = 0; i < m_model.size(); i++)
	{
		VECTOR pos = VGet(0.0f, 0.0f, i * -30.0f);
		m_model[i] = std::make_shared<ModelTree>(m_treeModel, pos);
	}
}
