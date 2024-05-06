#include "Background.h"
#include "ManagerModel.h"
#include "WorldSprite.h"
#include <string>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Background::Background(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_bgPos(VGet(0.0f, kBgPosY, kBgPosZ)),
	m_bg2Pos(VGet(0.0f, kBg2PosY, kBg2PosZ))
{
	// �w�i�摜�ǂݍ���
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

	m_pModel->CreateGroundModel();	// �n�ʂ̐���
	m_pModel->CreateTreeModel();	// �؂̐���
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Background::~Background()
{
	for (int i = 0; i < m_bgHandle.size(); i++)
	{
		DeleteGraph(m_bgHandle[i]);
	}
}


/// <summary>
/// ������
/// </summary>
void Background::Init()
{
	// �X�v���C�g�摜�̏�����
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
/// �X�V
/// </summary>
void Background::Update()
{
	// �w�i�̕\���ʒu���X�V
	m_bgMove += kBgMove;
}


/// <summary>
/// �`��
/// </summary>
void Background::Draw()
{
	for (int i = 0; i < m_sprite.size(); i++)
	{
		m_sprite[i]->Draw();
	}
}
