#include "DxLib.h"
#include "Input.h"
#include "ScenePause.h"
#include "SceneStage1.h"
#include "SceneSelectStage.h"


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
	if (input.IsTriggered("OK"))
	{
		if (m_select == Select::kBack)
		{
			return m_pPrevScene;
		}
		else if (m_select == Select::kRetry)
		{
			return std::make_shared<SceneStage1>();
		}
		else if (m_select == Select::kStageSelect)
		{
			return std::make_shared<SceneSelectStage>();
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePause::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	m_pPrevScene->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�|�[�Y���", 0xffffff);
#endif
}
