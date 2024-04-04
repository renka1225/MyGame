#include "Background.h"
#include "ManagerModel.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pModel">3D���f��</param>
Background::Background():
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_pos2(VGet(0.0f, 0.0f, 0.0f))
{
	m_background = LoadGraph("data/background/2.png");
	m_background2 = LoadGraph("data/background/3.png");
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
	m_pos2 = VAdd(m_pos2, VGet(kBgMove, 0.0f, 0.0f));
}

/// <summary>
/// �`��
/// </summary>
void Background::Draw()
{
	// �w�i�̕`��
	DrawBillboard3D(m_pos, 0.0f, 0.0f, kBgSize, 0.0f, m_background, true);
	DrawBillboard3D(m_pos2, 0.0f, 0.0f, kBgSize, 0.0f, m_background, true);

#ifdef _DEBUG
	// MEMO:XYZ���f�o�b�N�\��
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0.0f, 0), VGet(lineSize, 0.0f, 0.0f), 0xff0000);
	DrawLine3D(VGet(0.0f, -lineSize, 0.0f), VGet(0.0f, lineSize, 0.0f), 0x00ff00);
	DrawLine3D(VGet(0.0f, 0.0f, -lineSize), VGet(0.0f, 0.0f, lineSize), 0x0000ff);
#endif
}


/// <summary>
/// �I��
/// </summary>
void Background::End()
{
}
