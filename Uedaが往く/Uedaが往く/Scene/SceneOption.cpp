#include "DxLib.h"
#include "Input.h"
#include "SceneOption.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneOption::SceneOption()
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
/// <returns></returns>
std::shared_ptr<SceneBase> SceneOption::Update(Input& input)
{
	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneOption::Draw()
{
#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�I�v�V�������", 0xffffff);
#endif
}
