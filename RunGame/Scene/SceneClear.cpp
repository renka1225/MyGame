#include "SceneClear.h"
#include "SceneTitle.h"
#include "Input.h"
#include "ManagerFont.h"
#include "DxLib.h"

SceneClear::SceneClear():
	m_textFrame(0)
{
}


SceneClear::~SceneClear()
{
}


/// <summary>
/// ������
/// </summary>
void SceneClear::Init()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	m_textFrame++;

#if _DEBUG
	// MEMO:�f�o�b�N�p
	if (input.IsTriggered("debug"))
	{
		return std::make_shared<SceneTitle>();
	}
#endif

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneClear::Draw()
{
#if _DEBUG
	DrawFormatString(0, 0, 0xffffff, "�N���A���");
#endif

	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "�^�C�g���ɂ��ǂ�");
	if (m_textFrame % 60 >= 30) return;
	DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "����1��V��");
}


/// <summary>
/// �I��
/// </summary>
void SceneClear::End()
{
}
