#include "SceneManager.h"
#include "SceneMain.h"

SceneManager::SceneManager()
{
	// �N���X�̃��������m�ۂ���
	m_pMain = new SceneMain;
}

SceneManager::~SceneManager()
{
	// �N���X�̃��������������
	delete m_pMain;
	m_pMain = nullptr;
}

void SceneManager::Init()
{
	m_pMain->Init();
}

void SceneManager::End()
{
	m_pMain->End();
}

void SceneManager::Update()
{
	m_pMain->Update();
}

void SceneManager::Draw()
{
	m_pMain->Draw();
}
