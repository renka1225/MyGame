#include "SceneGameover.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "ManagerFont.h"
#include "DxLib.h"

SceneGameover::SceneGameover():
	m_textFrame(0)
{
}


SceneGameover::~SceneGameover()
{
}


/// <summary>
/// ������
/// </summary>
void SceneGameover::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneGameover::Update(Input& input)
{
	m_textFrame++;

	//�@�v���C��ʂɑJ��
	if (input.IsTriggered("Enter"))
	{
		return std::make_shared<ScenePlaying>();
	}
	// �^�C�g����ʂɑJ��
	else if (input.IsTriggered("debug"))
	{
		return std::make_shared<SceneTitle>();
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneGameover::Draw()
{
#if _DEBUG
	DrawFormatString(0, 0, 0xffffff, "�Q�[���I�[�o�[���");
#endif

	if (m_textFrame % 60 >= 30) return;
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "����1��V��");
	DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "�^�C�g���ɂ��ǂ�");
}


/// <summary>
/// �I��
/// </summary>
void SceneGameover::End()
{
}
