#include "Background.h"
#include "ManagerModel.h"


Background::Background(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_pos(VGet(0.0f,-5.0f, -20.0f))
{
	m_background = LoadGraph("data/background/5.png");
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
	// �w�i�̕`��
	DrawBillboard3D(m_pos, 0.0f, 0.0f, 1.0f, 0.0f, m_background, true);

#ifdef _DEBUG
	// MEMO:XYZ���f�o�b�N�\��
	DrawLine3D(VGet(-300, 0.0f, 0), VGet(300.0f, 0.0f, 0.0f), 0xff0000);
	DrawLine3D(VGet(0.0f, -300.0f, 0.0f), VGet(0.0f, 300.0f, 0.0f), 0x00ff00);
	DrawLine3D(VGet(0.0f, 0.0f, -300.0f), VGet(0.0f, 0.0f, 300.0f), 0x0000ff);
#endif
}


/// <summary>
/// �I��
/// </summary>
void Background::End()
{
}
