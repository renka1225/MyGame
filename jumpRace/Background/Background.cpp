#include "Background.h"
#include "ManagerModel.h"
#include "WorldSprite.h"

/// <summary>
/// コンストラクタ
/// </summary>
Background::Background(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_backgroundPos(VGet(0.0f, kBackPosY, kBackPosZ))
{
	m_sprite = std::make_shared<WorldSprite>();

	m_background = LoadGraph("data/Background/1.png");
	m_pModel->CreateGroundModel();	// 地面の生成
	m_pModel->CreateTreeModel();	// 木の生成
}


/// <summary>
/// デストラクタ
/// </summary>
Background::~Background()
{
	DeleteGraph(m_background);
}


/// <summary>
/// 初期化
/// </summary>
void Background::Init()
{
	// スプライト画像の初期化
	m_sprite->Init(m_background, kWidth, kHeight, 0);
	m_sprite->SetTransform(m_backgroundPos, kBackScele);
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
	//DrawGraph(0, 0, m_background, true);
	m_sprite->Draw();
}
