#include "SceneManager.h"
#include "Input.h"
#include "LoadData.h"
#include "SceneBase.h"
#include "SceneTitle.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager():
	m_pScene(nullptr)
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
}


/// <summary>
/// ������
/// </summary>
void SceneManager::Init(LoadData& data)
{
	m_pScene = std::make_shared<SceneTitle>();
	m_pScene->Init(data);
}


/// <summary>
/// �X�V
/// </summary>
void SceneManager::Update(Input& input)
{
	std::shared_ptr<SceneBase> pNext = m_pScene->Update(input);

	// �J�ڐ�̃V�[���̊J�n�������s��
	if (pNext != m_pScene)
	{
		// Update���Ԃ����V�����V�[���̊J�n�������s��
		m_pScene = pNext;
		m_pScene->Init(data);
	}
}


/// <summary>
/// �`��
/// </summary>
void SceneManager::Draw()
{
	m_pScene->Draw();
}
