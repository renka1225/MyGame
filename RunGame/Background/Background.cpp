#include "Background.h"
#include "ManagerModel.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pModel">3Dモデル</param>
Background::Background(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_pos(VGet(0.0f,-0.0f, 0.0f))
{
	m_background = LoadGraph("data/background/5.png");
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
}

/// <summary>
/// 描画
/// </summary>
void Background::Draw()
{
	// 背景の描画
	//DrawBillboard3D(m_pos, 0.0f, 0.0f, kBackgroundSize, 0.0f, m_background, true);

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
