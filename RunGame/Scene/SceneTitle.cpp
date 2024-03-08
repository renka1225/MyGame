#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "DxLib.h"

SceneTitle::SceneTitle()
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
	DrawFormatString(0, 0, 0xffffff, "�^�C�g�����");
#endif
}


/// <summary>
/// �I������
/// </summary>
void SceneTitle::End()
{
}
