#include "ModelBase.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
ModelBase::ModelBase(int model)
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
