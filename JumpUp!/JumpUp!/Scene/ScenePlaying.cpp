#include "ScenePlaying.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ScenePlaying::ScenePlaying()
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ScenePlaying::~ScenePlaying()
{
}


/// <summary>
/// ������
/// </summary>
void ScenePlaying::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">����</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	return std::shared_ptr<SceneBase>();
}


/// <summary>
/// �`��
/// </summary>
void ScenePlaying::Draw()
{
#ifdef _DEBUG
	// �f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�v���C���");
#endif

}