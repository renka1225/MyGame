#include "Background.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pModel">3Dモデル</param>
Background::Background():
	m_pos(VGet(kBgPosX, kBgPosY, kBgPosZ)),
	m_pos2(VGet(kBg2PosX, kBgPosY, kBg2PosZ)),
	m_pos3(VGet(kBg3PosX, kBg3PosY, kBg3PosZ))
{
	m_background = LoadGraph("data/background/1.png");
	m_background2 = LoadGraph("data/background/2.png");
	m_background3 = LoadGraph("data/background/3.png");
	m_bg = LoadGraph("data/background/bg3.png");
}


/// <summary>
/// デストラクタ
/// </summary>
Background::~Background()
{
	DeleteGraph(m_background);
	DeleteGraph(m_background2);
	DeleteGraph(m_background3);
	DeleteGraph(m_bg);
}


/// <summary>
/// 描画
/// </summary>
void Background::Draw()
{
	// 画像サイズを取得
	Size bgSize;
	Size bg3Size;
	GetGraphSize(m_background, &bgSize.width, &bgSize.height);
	GetGraphSize(m_background3, &bg3Size.width, &bg3Size.height);

	// スクロール量を計算
	int scrollBg = static_cast<int>(m_pos.x * 0.3f) % static_cast<int>(bgSize.width * kBgScale);
	int scrollBg3 = static_cast<int>(m_pos3.x) % static_cast<int>(bg3Size.width * kBg3Scale);

	// 背景の描画
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
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph3D(scrollBg3 + i * bg3Size.width * kBg3Scale,
			m_pos3.y,
			m_pos3.z,
			kBg3Scale, 0.0f,
			m_background3, true);
	}

#ifdef _DEBUG
	// MEMO:XYZ軸デバック表示
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0.0f, 0), VGet(lineSize, 0.0f, 0.0f), 0xff0000);
	DrawLine3D(VGet(0.0f, -lineSize, 0.0f), VGet(0.0f, lineSize, 0.0f), 0x00ff00);
	DrawLine3D(VGet(0.0f, 0.0f, -lineSize), VGet(0.0f, 0.0f, lineSize), 0x0000ff);
#endif
}
