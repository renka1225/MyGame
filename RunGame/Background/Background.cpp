#include "Background.h"
#include "ManagerModel.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pModel">3Dモデル</param>
Background::Background():
	m_pos(VGet(0.0f, 0.0f, 150.0f)),
	m_pos2(VGet(0.0f, 0.0f, 0.0f))
{
	m_background = LoadGraph("data/background/5.png");
	m_background2 = LoadGraph("data/background/3.png");
}


/// <summary>
/// 初期化
/// </summary>
void Background::Init()
{
}

/// <summary>
/// 更新
/// </summary>
void Background::Update()
{
	m_pos2 = VAdd(m_pos2, VGet(kBgMove, 0.0f, 0.0f));
}

/// <summary>
/// 描画
/// </summary>
void Background::Draw()
{
	// 背景の描画
	DrawGraph3D(m_pos.x, m_pos.y, m_pos.z, m_background, false);

#ifdef _DEBUG
	// MEMO:XYZ軸デバック表示
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0.0f, 0), VGet(lineSize, 0.0f, 0.0f), 0xff0000);
	DrawLine3D(VGet(0.0f, -lineSize, 0.0f), VGet(0.0f, lineSize, 0.0f), 0x00ff00);
	DrawLine3D(VGet(0.0f, 0.0f, -lineSize), VGet(0.0f, 0.0f, lineSize), 0x0000ff);
#endif
}


/// <summary>
/// 終了
/// </summary>
void Background::End()
{
}
