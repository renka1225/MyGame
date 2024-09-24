#include "SceneManager.h"
#include "SceneTitle.h"
#include "Input.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager():
	m_pScene(nullptr)
{
}


/// <summary>
/// ������
/// </summary>
void SceneManager::Init()
{
	m_pScene = std::make_shared<SceneTitle>();
	m_pScene->Init();
}


/// <summary>
/// �X�V
/// </summary>
void SceneManager::Update(Input& input)
{
	std::shared_ptr<SceneBase> pNext = m_pScene->Update(input);

	// �J�ڐ�̃V�[���̊J�n�������s��
	if (m_pScene != pNext)
	{
		m_pScene = pNext;
		m_pScene->Init();
	}
}


/// <summary>
/// �`��
/// </summary>
void SceneManager::Draw()
{
	m_pScene->Draw();
}