#include "ModelGround.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="model">3Dモデル</param>
/// <param name="pos">表示位置</param>
ModelGround::ModelGround(int model, VECTOR pos) :
	ModelBase(model)
{
	m_pos = pos;

	// 3Dモデルの調整
	MV1SetScale(m_model, VGet(kGroundScaleWidth, kGroundScaleHeight, kGroundScaleDepth));
}


/// <summary>
/// デストラクタ
/// </summary>
ModelGround::~ModelGround()
{
}


/// <summary>
/// 更新
/// </summary>
void ModelGround::Update()
{
	MV1SetPosition(m_model, m_pos);
}
