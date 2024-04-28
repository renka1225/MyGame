#include "ModelBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
ModelBase::ModelBase(int model)
{
	m_model = MV1DuplicateModel(model);
}


/// <summary>
/// 描画
/// </summary>
void ModelBase::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(m_model);
}
