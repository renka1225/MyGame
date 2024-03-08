#include "SceneManager.h"
#include "SceneTitle.h"
#include "Input.h"

SceneManager::SceneManager():
	m_pScene(nullptr)
{
}


SceneManager::~SceneManager()
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

	// ���݂̃V�[���̏I������
	m_pScene->End();

	// �J�ڐ�̃V�[���̊J�n�������s��
	m_pScene = pNext;
	m_pScene->Init();
}


/// <summary>
/// �`��
/// </summary>
void SceneManager::Draw()
{
	m_pScene->Draw();
}


/// <summary>
/// �I������
/// </summary>
void SceneManager::End()
{
	m_pScene->End();
}
