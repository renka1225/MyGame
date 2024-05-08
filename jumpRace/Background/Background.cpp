#include "Background.h"
#include "ManagerModel.h"
#include "WorldSprite.h"
#include <string>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Background::Background(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel)
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
	m_pModel->CreateGateModel();	// �Q�[�g�̐���
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
		VECTOR pos = VGet(0.0f, kBgPosY, kBgPosZ);
		if (i == 1)
		{
			scale = kBg2Scale;
			pos = VGet(0.0f, kBg2PosY, kBg2PosZ);
		}
		else if (i == 2)
		{
			scale = kBg3Scale;
			pos = VGet(0.0f, kBg3PosY, kBg3PosZ);
		}
		else if (i == 3)
		{
			scale = kBg4Scale;
			pos = VGet(0.0f, kBg4PosY, kBg4PosZ);
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
	for (auto& sprite : m_sprite)
	{
		sprite->Draw();
	}
}
