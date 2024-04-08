#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "ManagerFont.h"
#include "DxLib.h"

SceneTitle::SceneTitle():
	m_textFrame(0)
{
	m_titleLogo = LoadGraph("data/title_test.png");
}


SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogo);
}


/// <summary>
/// ������
/// </summary>
void SceneTitle::Init()
{
}


/// <summary>
///	�X�V
/// </summary>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	m_textFrame++;

	// �v���C��ʂɑJ��
	if (input.IsTriggered("OK"))
	{
		return std::make_shared<ScenePlaying>();
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneTitle::Draw()
{
	// �^�C�g�����S�\��
	DrawGraph(0, 0, m_titleLogo, false);

#if _DEBUG
	// MEMO:�f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�^�C�g�����");
#endif

	// �e�L�X�g�\��
	if (m_textFrame % 60 >= 30) return;
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "Press Enter");
}