#include "ManagerModel.h"
#include "ModelBase.h"
#include "ModelTree.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
ManagerModel::ManagerModel()
{
	m_model.resize(kTreeNum);

	m_playerModel = MV1LoadModel("data/Model/rabbit.mv1");
	m_groundModel = MV1LoadModel("data/model/tile.mv1");
	m_treeModel = MV1LoadModel("data/model/tree.mv1");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ManagerModel::~ManagerModel()
{
	MV1DeleteModel(m_playerModel);
	MV1DeleteModel(m_groundModel);
	MV1DeleteModel(m_treeModel);
}


/// <summary>
/// �X�V
/// </summary>
void ManagerModel::Update()
{
	for (auto& model : m_model)
	{
		model->Update();
	}
}


/// <summary>
/// �`��	
/// </summary>
void ManagerModel::Draw()
{
	for (auto& model : m_model)
	{
		model->Draw();
	}
}

/// <summary>
/// �؂̐���
/// </summary>
void ManagerModel::GreateTreeModel()
{
	for (int i = 0; i < m_model.size(); i++)
	{
		VECTOR pos = VGet(0.0f, 0.0f, i * -30.0f);
		m_model[i] = std::make_shared<ModelTree>(m_treeModel, pos);
	}
}
