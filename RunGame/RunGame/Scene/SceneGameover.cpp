#include "SceneGameover.h"
#include "SceneTitle.h"
#include "Input.h"
#include "DxLib.h"

SceneGameover::SceneGameover()
{
}


SceneGameover::~SceneGameover()
{
}


/// <summary>
/// ������
/// </summary>
void SceneGameover::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneGameover::Update(Input& input)
{
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
void SceneGameover::Draw()
{
#if _DEBUG
	DrawFormatString(0, 0, 0xffffff, "�Q�[���I�[�o�[���");
#endif
}


/// <summary>
/// �I��
/// </summary>
void SceneGameover::End()
{
}
