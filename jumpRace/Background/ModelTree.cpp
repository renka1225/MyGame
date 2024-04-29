#include "ModelTree.h"

ModelTree::ModelTree(int model, VECTOR pos):
	ModelBase(model)
{
	m_pos = pos;

	// 3D���f���̒���
	MV1SetScale(m_model, VGet(kScale, kScale, kScale));
}

ModelTree::~ModelTree()
{
}

void ModelTree::Update()
{
	MV1SetPosition(m_model, m_pos);
}