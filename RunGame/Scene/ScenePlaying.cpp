#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "Player.h"
#include "Camera.h"
#include "Input.h"
#include "DxLib.h"
#include <memory>

ScenePlaying::ScenePlaying()
{
	m_pPlayer = std::make_shared<Player>();
	m_pCamera = std::make_shared<Camera>();
}


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
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	// �v���C���[�̍X�V
	m_pPlayer->Update(input);
	// �J�����̍X�V
	m_pCamera->Update(m_pPlayer);

#if _DEBUG
	// MEMO:�f�o�b�N�p
	if (input.IsTriggered("debug"))
	{
		return std::make_shared<SceneClear>();
	}
	else if (input.IsTriggered("OK"))
	{
		return std::make_shared<SceneGameover>();
	}
#endif

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePlaying::Draw()
{
	// �v���C���[�̕`��
	m_pPlayer->Draw();

#if _DEBUG
	DrawFormatString(0, 0, 0xffffff, "�v���C���");
#endif
}


/// <summary>
/// �I��
/// </summary>
void ScenePlaying::End()
{
}
