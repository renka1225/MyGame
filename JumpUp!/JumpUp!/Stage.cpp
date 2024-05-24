#include "DxLib.h"
#include "Stage.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Stage::Stage():
	m_floorPos(VGet(0.0f, 0.0f, 0.0f))
{
	m_floorHandle = MV1LoadModel("data/model/floor.mv1");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Stage::~Stage()
{
	MV1DeleteModel(m_floorHandle);
}

/// <summary>
/// ������
/// </summary>
void Stage::Init()
{
	MV1SetPosition(m_floorHandle, VGet(0.0f, 0.0f, 0.0f));
	MV1SetScale(m_floorHandle, VGet(kFloorScaleX, kFloorScaleY, kFloorScaleZ));
}

/// <summary>
/// �X�V
/// </summary>
void Stage::Update()
{
}

/// <summary>
/// �`��
/// </summary>
void Stage::Draw()
{
	// ����`�悷��
	MV1DrawModel(m_floorHandle);
}
