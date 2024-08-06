#include "DxLib.h"
#include "Input.h"
#include "Game.h"
#include "ScenePause.h"
#include "SceneOption.h"
#include "SceneSelectStage.h"

// �萔
namespace
{
	constexpr int kAlpha = 200;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pScene">�O�Ɏ��s���Ă����V�[��</param>
ScenePause::ScenePause(std::shared_ptr<SceneBase> pScene)
{
	m_select = Select::kBack;
	m_pPrevScene = pScene;
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ScenePause::~ScenePause()
{
}


/// <summary>
/// ������
/// </summary>
void ScenePause::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePause::Update(Input& input)
{
	UpdateSelect(input, Select::kSelectNum);

	if (input.IsTriggered("OK"))
	{
		if (m_select == Select::kBack)
		{
			return m_pPrevScene;	// �Q�[�����
		}
		else if (m_select == Select::kOption)
		{
			return std::make_shared<SceneOption>(shared_from_this());	// �I�v�V�������
		}
		else if (m_select == Select::kStageSelect)
		{
			return std::make_shared<SceneSelectStage>(); // �X�e�[�W�I�����
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePause::Draw()
{
	// �v���C��ʂ𔖂��\������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAlpha);
	m_pPrevScene->Draw();
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �w�i�ɍ��g��\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAlpha);
	DrawBox(500, 200, 1420, 880, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �J�[�\���\��
	for (int i = 0; i < Select::kSelectNum; i++)
	{
		DrawBox(700, 300 + 200 * i, 1220, 400 + 200 * i, 0xffffff, true);
	}

	// �����\��
	DrawString(750, 320, "�Q�[���ɂ��ǂ�", 0x000000);
	DrawString(750, 520, "�I�v�V����", 0x000000);
	DrawString(750, 720, "�X�e�[�W�I���ɖ߂�", 0x000000);

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�|�[�Y���", 0xffffff);
#endif
}
