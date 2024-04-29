#include "Background.h"
#include "ManagerModel.h"
#include "WorldSprite.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Background::Background(std::shared_ptr<ManagerModel> pModel):
	m_pModel(pModel),
	m_backgroundPos(VGet(0.0f, kBackPosY, kBackPosZ))
{
	m_sprite = std::make_shared<WorldSprite>();

	m_background = LoadGraph("data/Background/1.png");
	m_pModel->CreateGroundModel();	// �n�ʂ̐���
	m_pModel->CreateTreeModel();	// �؂̐���
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Background::~Background()
{
	DeleteGraph(m_background);
}


/// <summary>
/// ������
/// </summary>
void Background::Init()
{
	// �X�v���C�g�摜�̏�����
	m_sprite->Init(m_background, kWidth, kHeight, 0);
	m_sprite->SetTransform(m_backgroundPos, kBackScele);
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
	//DrawGraph(0, 0, m_background, true);
	m_sprite->Draw();
}
