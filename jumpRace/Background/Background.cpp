#include "Background.h"
#include "ManagerModel.h"
#include "WorldSprite.h"

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
Background::~Background()
{
	DeleteGraph(m_background);
	MV1DeleteModel(m_groundModel);
	MV1DeleteModel(m_treeModel);
}


/// <summary>
/// ������
/// </summary>
void Background::Init()
{
	// �X�v���C�g�摜�̏�����
	m_sprite->Init(m_background, kWidth, kHeight, 0);
	m_sprite->SetGroundTransform(m_backgroundPos, kBackScele);

	// �n�ʂ̒���
	MV1SetScale(m_groundModel, VGet(kGroundScaleWidth, kGroundScaleHeight, kGroundScaleDepth));
	MV1SetPosition(m_groundModel, VGet(0.0f, -kGroundPosY, kGroundPosZ));

	// �؂̒���
	MV1SetScale(m_treeModel, VGet(50.0f, 50.0f, 50.0f));
	for (int i = 0; i < 10; i++)
	{
		MV1SetPosition(m_treeModel, VGet(-100.0f, -50.0f, -30.0f * i));
	}
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
	DrawGraph(0, 0, m_background, true);
	//m_sprite->Draw();

	MV1DrawModel(m_groundModel);
	MV1DrawModel(m_treeModel);
}
