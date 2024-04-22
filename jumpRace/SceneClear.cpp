#include "SceneClear.h"
#include "SceneTitle.h"
#include "Input.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneClear::SceneClear()
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
/// <param name="input">�{�^������</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	if (input.IsTriggered("sceneChange"))
	{
		return std::make_shared<SceneTitle>();
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneClear::Draw()
{
#ifdef _DEBUG
	// �f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�N���A���");
#endif
}
