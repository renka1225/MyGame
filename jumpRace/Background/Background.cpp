#include "Background.h"
#include "ManagerModel.h"
#include "WorldSprite.h"
#include <string>

/// <summary>
/// コンストラクタ
/// </summary>
Background::Background(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_bgPos(VGet(0.0f, kBgPosY, kBgPosZ)),
	m_bg2Pos(VGet(0.0f, kBg2PosY, kBg2PosZ))
{
	// 背景画像読み込み
	m_bgHandle.resize(kBgNum);
	for (int i = 0; i < m_bgHandle.size(); i++)
	{
		std::string fileName = "data/Background/" + std::to_string(i + 1) + ".png";
		m_bgHandle[i] = LoadGraph(fileName.c_str());
	}

	m_sprite.resize(kBgNum);
	for (int i = 0; i < m_sprite.size(); i++)
	{
		m_sprite[i] = std::make_shared<WorldSprite>();
	}

	m_pModel->CreateGroundModel();	// 地面の生成
	m_pModel->CreateTreeModel();	// 木の生成
}


/// <summary>
/// デストラクタ
/// </summary>
Background::~Background()
{
	for (int i = 0; i < m_bgHandle.size(); i++)
	{
		DeleteGraph(m_bgHandle[i]);
	}
}


/// <summary>
/// 初期化
/// </summary>
void Background::Init()
{
	// スプライト画像の初期化
	for (int i = 0; i < m_sprite.size(); i++)
	{
		float scale = kBgScale;
		VECTOR pos = m_bgPos;
		if (i == 1)
		{
			scale = kBg2Scale;
			pos = m_bg2Pos;
		}
		m_sprite[i]->Init(m_bgHandle[i], kWidth, kHeight, 0);
		m_sprite[i]->SetTransform(pos, scale);
	}
}


/// <summary>
/// 更新
/// </summary>
void Background::Update()
{
	// 背景の表示位置を更新
	m_bgMove += kBgMove;
}


/// <summary>
/// 描画
/// </summary>
void Background::Draw()
{
	for (int i = 0; i < m_sprite.size(); i++)
	{
		m_sprite[i]->Draw();
	}
}
