#include "DxLib.h"
#include "Input.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "SceneTitle.h"
#include "SceneSelectStage.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneSelectStage::SceneSelectStage()
{
	m_select = SelectScene::kStage1;
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneSelectStage::~SceneSelectStage()
{
}


/// <summary>
/// ������
/// </summary>
void SceneSelectStage::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏���</param>
/// <returns>�J�ڐ�̃V�[��</returns>
std::shared_ptr<SceneBase> SceneSelectStage::Update(Input& input)
{
	//�I����ԍX�V
	UpdateSelect(input, kSelectNum);

	// �V�[���J��
	if (input.IsTriggered("OK"))
	{
		std::shared_ptr<Player> pPlayer = std::make_shared<Player>();
		std::shared_ptr<Camera> pCamera = std::make_shared<Camera>();
		std::shared_ptr<Stage> pStage = std::make_shared<Stage>();

		if (m_select == SelectScene::kStage1)
		{
			return std::make_shared<SceneStage1>(pPlayer, pCamera, pStage);
		}
		else if (m_select == SelectScene::kStage2)
		{
			return std::make_shared<SceneStage2>(pPlayer, pCamera, pStage);
		}
		else if (m_select == kTitle)
		{
			return std::make_shared<SceneTitle>();
		}
	}

	return shared_from_this();
}


/// <summary>
/// �`��
/// </summary>
void SceneSelectStage::Draw()
{
#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�X�e�[�W�I�����", 0xffffff);

	int stage1Color = 0xffffff;
	int stage2Color = 0xffffff;
	int titleColor = 0xffffff;
	if(m_select == SelectScene::kStage1) stage1Color = 0xff0000;
	if (m_select == SelectScene::kStage2) stage2Color = 0xff0000;
	if (m_select == SelectScene::kTitle) titleColor = 0xff0000;
	DrawString(0, 20, "�X�e�[�W1", stage1Color);
	DrawString(0, 40, "�X�e�[�W2", stage2Color);
	DrawString(0, 60, "�^�C�g��", titleColor);
#endif
}


