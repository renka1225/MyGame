#include "ModelBase.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
ModelBase::ModelBase(int model):
	m_pos(VGet(0.0f, 0.0f, 0.0f))
{
	m_model = MV1DuplicateModel(model);
}


/// <summary>
/// �`��
/// </summary>
void ModelBase::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(m_model);
}
