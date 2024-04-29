#include "ModelGround.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
ModelGround::ModelGround(int model, VECTOR pos) :
	ModelBase(model)
{
	m_pos = pos;

	// 3D���f���̒���
	MV1SetScale(m_model, VGet(kGroundScaleWidth, kGroundScaleHeight, kGroundScaleDepth));
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ModelGround::~ModelGround()
{
}


/// <summary>
/// �X�V
/// </summary>
void ModelGround::Update()
{
	MV1SetPosition(m_model, m_pos);
}
