#include "DxLib.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneClear::SceneClear():
	m_select(Select::kStart)
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
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
/// <param name="input">����</param>
/// <returns>�J�ڐ�̃V�[��</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	// �I����Ԃ��X�V
	UpdateSelect(input);

	// �V�[���؂�ւ�
	if (input.IsTriggered("OK"))
	{
		if (m_select == Select::kStart)
		{
			return std::make_shared<ScenePlaying>(); // �Q�[���V�[���Ɉړ�
		}
		else if (m_select == Select::kTitle)
		{
			return std::make_shared<SceneTitle>();	// �^�C�g����ʂɈړ�
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneClear::Draw()
{
#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�N���A���", 0xffffff);
#endif
}


/// <summary>
/// �I����Ԃ��X�V
/// </summary>
/// <param name="input">����</param>
void SceneClear::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1������
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select - 1) % kSelectNum;	// �I����Ԃ�1�グ��
	}
}
