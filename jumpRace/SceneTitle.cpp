#include "SceneTitle.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle()
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
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
/// �X�V
/// </summary>
/// <param name="input">�{�^������</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	return std::shared_ptr<SceneBase>();
}


/// <summary>
/// �`��
/// </summary>
void SceneTitle::Draw()
{
#ifdef _DEBUG
	// �f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�^�C�g�����");
#endif
}
