#include "SceneClear.h"
#include "SceneTitle.h"
#include "Input.h"
#include "DxLib.h"

SceneClear::SceneClear()
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
}


/// <summary>
/// �I��
/// </summary>
void SceneClear::End()
{
}
