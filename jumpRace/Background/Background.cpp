#include "Background.h"
#include "ManagerModel.h"
#include "WorldSprite.h"

/// <summary>
/// コンストラクタ
/// </summary>
Background::Background(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_backgroundPos(VGet(0.0f, 0.0f, 10.0f))
{
	m_sprite = std::make_shared<WorldSprite>();

	m_background = LoadGraph("data/Background/5.png");
	m_groundModel = MV1DuplicateModel(m_pModel->GetGroundModel());
	m_treeModel = MV1DuplicateModel(m_pModel->GetTreeModel());
}


/// <summary>
/// デストラクタ
/// </summary>
Background::~Background()
{
	DeleteGraph(m_background);
	MV1DeleteModel(m_groundModel);
	MV1DeleteModel(m_treeModel);
}


/// <summary>
/// 初期化
/// </summary>
void Background::Init()
{
	// スプライト画像の初期化
	m_sprite->Init(m_background, kWidth, kHeight, 0);
	m_sprite->SetGroundTransform(m_backgroundPos, kBackScele);

	// 地面の調整
	MV1SetScale(m_groundModel, VGet(kGroundScaleWidth, kGroundScaleHeight, kGroundScaleDepth));
	MV1SetPosition(m_groundModel, VGet(0.0f, -kGroundPosY, kGroundPosZ));

	// 木の調整
	MV1SetScale(m_treeModel, VGet(50.0f, 50.0f, 50.0f));
	for (int i = 0; i < 10; i++)
	{
		MV1SetPosition(m_treeModel, VGet(-100.0f, -50.0f, -30.0f * i));
	}
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
	DrawGraph(0, 0, m_background, true);
	//m_sprite->Draw();

	MV1DrawModel(m_groundModel);
	MV1DrawModel(m_treeModel);
}
