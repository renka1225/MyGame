#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "ManagerFont.h"
#include "DxLib.h"

SceneTitle::SceneTitle():
	m_textFrame(0)
{
}


SceneTitle::~SceneTitle()
{
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

#if _DEBUG
	// MEMO:�f�o�b�N�p
	if (input.IsTriggered("debug"))
	{
		return std::make_shared<ScenePlaying>();
	}
#endif

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneTitle::Draw()
{
#if _DEBUG
	// MEMO:�f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�^�C�g�����");
#endif

	// �e�L�X�g�\��
	if (m_textFrame % 60 >= 30) return;
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "Press A");
}


/// <summary>
/// �I������
/// </summary>
void SceneTitle::End()
{
}
