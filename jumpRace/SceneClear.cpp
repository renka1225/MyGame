#include "SceneClear.h"
#include "SceneTitle.h"
#include "ManagerResult.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneClear::SceneClear(int time):
	m_clearTime(time)
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
	// �N���A�^�C���\��
	int milliSec = m_clearTime * 1000 / 60;
	int sec = (milliSec / 1000) % 90;
	milliSec %= 1000;
	DrawFormatString(Game::kScreenWidth * 0.5f, 100, 0xffffff, "�N���A�^�C��:%02d:%03d", sec, milliSec);

#ifdef _DEBUG
	// �f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�N���A���");
#endif
}
