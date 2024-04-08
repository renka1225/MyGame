#include "Background.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pModel">3D���f��</param>
Background::Background():
	m_pos(VGet(kBgPosX, kBgPosY, kBgPosZ)),
	m_pos2(VGet(kBg2PosX, kBgPosY, kBg2PosZ)),
	m_pos3(VGet(kBg3PosX, kBg3PosY, kBg3PosZ)),
	m_bgMove(kBgMove)
{
	m_background = LoadGraph("data/background/1.png");
	m_background2 = LoadGraph("data/background/2.png");
	m_background3 = LoadGraph("data/background/3.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Background::~Background()
{
	DeleteGraph(m_background);
	DeleteGraph(m_background2);
	DeleteGraph(m_background3);
}


/// <summary>
/// ������
/// </summary>
void Background::Init()
{
	// �����Ȃ�
}


/// <summary>
/// �X�V
/// </summary>
void Background::Update()
{
	// MEMO:�X�N���[���������J�N������1�b���ƂɃX�N���[�����s��
	int frame  =0;
	frame++;
	if (frame >= 60)
	{
		m_pos = VAdd(m_pos, VGet(kBgMove, 0.0f, 0.0f));
		m_pos3 = VAdd(m_pos3, VGet(kBgMove, 0.0f, 0.0f));
		frame = 0;
	}

}


/// <summary>
/// �`��
/// </summary>
void Background::Draw()
{
	// �摜�T�C�Y���擾
	Size bgSize;
	Size bg3Size;
	GetGraphSize(m_background, &bgSize.width, &bgSize.height);
	GetGraphSize(m_background3, &bg3Size.width, &bg3Size.height);

	// �X�N���[���ʂ��v�Z
	int scrollBg = static_cast<int>(m_pos.x * 0.3f) % static_cast<int>(bgSize.width * kBgScale);
	int scrollBg3 = static_cast<int>(m_pos3.x) % static_cast<int>(bg3Size.width * kBg3Scale);

	// �w�i�̕`��
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph3D(scrollBg + i * bgSize.width * kBgScale,
			m_pos.y,
			m_pos.z,
			kBgScale, 0.0f, 
			m_background, true);
	}
	DrawRotaGraph3D(m_pos2.x, 
		m_pos2.y, 
		m_pos2.z, 
		kBg2Scale, 0.0f, 
		m_background2, true);
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph3D(scrollBg3 + i * bg3Size.width * kBg3Scale,
			m_pos3.y,
			m_pos3.z,
			kBg3Scale, 0.0f,
			m_background3, true);
	}

#ifdef _DEBUG
	// MEMO:XYZ���f�o�b�N�\��
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0.0f, 0), VGet(lineSize, 0.0f, 0.0f), 0xff0000);
	DrawLine3D(VGet(0.0f, -lineSize, 0.0f), VGet(0.0f, lineSize, 0.0f), 0x00ff00);
	DrawLine3D(VGet(0.0f, 0.0f, -lineSize), VGet(0.0f, 0.0f, lineSize), 0x0000ff);
#endif
}
