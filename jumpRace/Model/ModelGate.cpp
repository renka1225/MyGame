#include "ModelGate.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="model">3D���f��</param>
/// <param name="pos">�\���ʒu</param>
ModelGate::ModelGate(int model, VECTOR pos):
	ModelBase(model)
{
	m_pos = pos;
	// 3D���f���̒���
	MV1SetScale(m_model, VGet(kScale, kScale, 0.0f));
	MV1SetPosition(m_model, m_pos);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ModelGate::~ModelGate()
{
}


/// <summary>
/// �X�V
/// </summary>
void ModelGate::Update()
{
}