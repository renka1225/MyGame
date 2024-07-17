#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneStage1.h"
#include "SceneDebug.h"
#include "Input.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneDebug::SceneDebug():
	m_select(Select::kTitle)
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <returns></returns>
std::shared_ptr<SceneBase> SceneDebug::Update(Input& input)
{
	UpdateSelect(input);

	// �J��
	if (input.IsTriggered("debug_enter"))
	{
		if (m_select == Select::kTitle)
		{
			return std::make_shared<SceneTitle>();
		}
		else if (m_select == Select::kStageSelect)
		{
			//return std::make_shared<SceneSelect>();
		}
		else if (m_select == Select::kOption)
		{
			//return std::make_shared<SceneOption>();
		}
		else if (m_select == Select::kStage1)
		{
			return std::make_shared<SceneStage1>();
		}
		else if (m_select == Select::kStage2)
		{
			//return std::make_shared<SceneStage2>();
		}
	}

	return shared_from_this();
}

/// <summary>
/// �`��
/// </summary>
void SceneDebug::Draw()
{
	DrawString(0, 20, "�^�C�g��", 0xffffff);
	DrawString(0, 40, "�X�e�[�W�I��", 0xffffff);
	DrawString(0, 60, "�I�v�V����", 0xffffff);
	DrawString(0, 80, "�X�e�[�W1", 0xffffff);
	DrawString(0, 100, "�X�e�[�W2", 0xffffff);
}


/// <summary>
/// �I����ԍX�V
/// </summary>
/// <param name="input">���͏��</param>
void SceneDebug::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1������
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;	// �I����Ԃ�1�グ��
	}
}
