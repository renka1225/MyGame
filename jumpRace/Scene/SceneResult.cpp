#include "SceneResult.h"
#include "SceneTitle.h"
#include "Input.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneResult::SceneResult()
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneResult::~SceneResult()
{
}


/// <summary>
/// ������
/// </summary>
void SceneResult::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">�{�^������</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneResult::Update(Input& input)
{
	if (input.IsTriggered("sceneChange"))
	{
		return std::make_shared<SceneTitle>();		//�^�C�g����ʂɈړ�
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneResult::Draw()
{
#ifdef _DEBUG
	// MEMO:�f�o�b�O�\��
	DrawString(0, 0, "���ʊm�F���", 0xffffff);
#endif

}
