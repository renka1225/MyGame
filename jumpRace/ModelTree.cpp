#include "ModelTree.h"

ModelTree::ModelTree(int model, VECTOR pos):
	ModelBase(model)
{
	m_pos = pos;
}

ModelTree::~ModelTree()
{
}

void ModelTree::Update()
{
	// 3D���f���̈ʒu�ݒ�
	MV1SetPosition(m_model, m_pos);
}
