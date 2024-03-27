#include "Background.h"
#include "ManagerModel.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pModel">3D���f��</param>
Background::Background(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_pos(VGet(0.0f,-0.0f, 0.0f))
{
	m_background = LoadGraph("data/background/5.png");
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
	DrawBillboard3D(m_pos, 0.0f, 0.0f, kBackgroundSize, 0.0f, m_background, true);

	// �g�̕`��
	//for (int x = 0; x < kWaveRange; x++)
	//{
	//	int y = static_cast<int>(kWaveAmplitude * sin(DX_PI_F * x / kWaveFrequency) + kDrawWaveY);
	//	DrawPixel(x, y, 0xffffff);
	//}

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
