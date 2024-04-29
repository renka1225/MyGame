#include "ModelBase.h"


/// <summary>
/// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
/// </summary>
ModelBase::ModelBase(int model)
{
	m_model = MV1DuplicateModel(model);
}


/// <summary>
/// •`‰æ
/// </summary>
void ModelBase::Draw()
{
	// ‚R‚cƒ‚ƒfƒ‹‚Ì•`‰æ
	MV1DrawModel(m_model);
}
