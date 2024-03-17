#include "Background.h"
#include "ManagerModel.h"


Background::Background(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_pos(VGet(0.0f,-5.0f, 0.0f))
{
	m_waterHandle = MV1DuplicateModel(m_pModel->GetWaterHandle());
}


Background::~Background()
{
}


/// <summary>
/// ������
/// </summary>
void Background::Init()
{
}

/// <summary>
/// �X�V
/// </summary>
void Background::Update()
{
}

/// <summary>
/// �`��
/// </summary>
void Background::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(m_waterHandle);
}


/// <summary>
/// �I��
/// </summary>
void Background::End()
{
}
