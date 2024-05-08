#include "ModelGate.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="model">3Dモデル</param>
/// <param name="pos">表示位置</param>
ModelGate::ModelGate(int model, VECTOR pos):
	ModelBase(model)
{
	m_pos = pos;
	// 3Dモデルの調整
	MV1SetScale(m_model, VGet(kScale, kScale, 0.0f));
	MV1SetPosition(m_model, m_pos);
}


/// <summary>
/// デストラクタ
/// </summary>
ModelGate::~ModelGate()
{
}


/// <summary>
/// 更新
/// </summary>
void ModelGate::Update()
{
}