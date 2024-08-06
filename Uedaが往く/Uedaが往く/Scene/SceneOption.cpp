#include "DxLib.h"
#include "Input.h"
#include "SceneOption.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneOption::SceneOption(std::shared_ptr<SceneBase> pScene):
	m_pPrevScene(pScene)
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneOption::~SceneOption()
{
}


/// <summary>
/// ������
/// </summary>
void SceneOption::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input"></param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneOption::Update(Input& input)
{
	if (input.IsTriggered("back"))
	{
		return m_pPrevScene;	// �O�̉�ʂɂ��ǂ�
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneOption::Draw()
{
	// �I�����ڕ\��
	DrawString(200, 300, "�T�E���h", 0xffffff);
	DrawString(200, 500, "���邳", 0xffffff);
	DrawString(200, 700, "�{�^���z�u", 0xffffff);

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�I�v�V�������", 0xffffff);
#endif
}
