#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneOption.h"
#include "SceneStageSelect.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneGameOver.h"
#include "Pad.h"

SceneManager::SceneManager() :
	m_runScene(kSceneTitle)
{
	// �N���X�̃��������m�ۂ���
	m_pTitle = new SceneTitle;
	m_pOption = new SceneOption;
	m_pStageSelect = new SceneStageSelect;
	m_pMain = new SceneMain;
	m_pClear = new SceneClear;
	m_pGameOver = new SceneGameOver;
}

SceneManager::~SceneManager()
{
	// �N���X�̃��������������
	delete m_pTitle;
	m_pTitle = nullptr;

	delete m_pOption;
	m_pOption = nullptr;

	delete m_pStageSelect;
	m_pStageSelect = nullptr;

	delete m_pMain;
	m_pMain = nullptr;

	delete m_pClear;
	m_pClear = nullptr;

	delete m_pGameOver;
	m_pGameOver = nullptr;
}

void SceneManager::Init()
{
	// ���s����V�[���̏��������s��
	switch (m_runScene)
	{
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->Init();
		break;
		// �I�v�V�����V�[��
	case kSceneOption:
		m_pOption->Init();
		break;
		// �X�e�[�W�I���V�[��
	case kSceneStageSelect:
		m_pStageSelect->Init();
		break;
		// �Q�[���V�[��
	case kSceneMain:
		m_pMain->Init();
		break;
		// �Q�[���N���A
	case kSceneClear:
		m_pClear->Init();
		break;
		// �Q�[���I�[�o�[
	case kSceneGameOver:
		m_pGameOver->Init();
		break;

	default:
		break;
	}
}

void SceneManager::End()
{
	// ���s����V�[�����I������
	switch (m_runScene)
	{
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->End();
		break;
		// �I�v�V�����V�[��
	case kSceneOption:
		m_pOption->End();
		break;
		// �X�e�[�W�I���V�[��
	case kSceneStageSelect: 
		m_pStageSelect->End();
		break;
		// �Q�[���V�[��
	case kSceneMain:
		m_pMain->End();
		break;
		// �Q�[���N���A
	case kSceneClear:
		m_pClear->End();
		break;
		// �Q�[���I�[�o�[
	case kSceneGameOver:
		m_pGameOver->End();
		break;
	default:
		break;
	}
}

void SceneManager::Update()
{
	Pad::Update();

	// ���s����V�[���̐؂�ւ����s��
	switch (m_runScene)
	{
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->End();
		if (m_pTitle->IsSceneStart())
		{
			m_runScene = kSceneStageSelect;
			m_pStageSelect->Init();
		}
		else if (m_pTitle->IsSceneOption())
		{
			m_runScene = kSceneOption;
			m_pOption->Init();
		}
		break;

		// �I�v�V�����V�[��
	case kSceneOption:
		if (m_pOption->IsSceneTitle())
		{
			m_pOption->End();
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

		// �X�e�[�W�I���V�[��
	case kSceneStageSelect:
		m_pStageSelect->End();
		if (m_pStageSelect->IsSceneStage1())
		{
			m_runScene = kSceneMain;
			m_pMain->Init();
		}
		else if (m_pStageSelect->IsSceneTitle())
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

		// �Q�[���V�[��
	case kSceneMain:
		m_pMain->End();
		if (m_pMain->IsSceneGameOver())
		{
			m_runScene = kSceneGameOver;
			m_pGameOver->Init();
		}
		else if (m_pMain->IsSceneClear())
		{
			m_runScene = kSceneClear;
			m_pClear->Init();
		}
		break;

		// �Q�[���N���A
	case kSceneClear:
		m_pClear->End();
		if (m_pClear->IsSceneStageSelect())
		{
			m_runScene = kSceneStageSelect;
			m_pStageSelect->Init();
		}
		else if (m_pClear->IsSceneTitle())
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

		// �Q�[���I�[�o�[
	case kSceneGameOver:
		if (m_pGameOver->IsSceneSelect())
		{
			m_pGameOver->End();
			m_runScene = kSceneStageSelect;
			m_pTitle->Init();
		}
		break;
	}

	// ���s����V�[���̍X�V���s��
	switch (m_runScene)
	{
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->Update();
		break;
		// �I�v�V�����V�[��
	case kSceneOption:
		m_pOption->Update();
		break;
		// �X�e�[�W�I���V�[��
	case kSceneStageSelect:
		m_pStageSelect->Update();
		break;
		// �Q�[���V�[��
	case kSceneMain:
		m_pMain->Update();
		break;
		// �Q�[���N���A
	case kSceneClear:
		m_pClear->Update();
		break;
		// �Q�[���I�[�o�[
	case kSceneGameOver:
		m_pGameOver->Update();
		break;
	default:
		break;
	}
}

void SceneManager::Draw()
{
	// ���s����V�[���̕`����s��
	switch (m_runScene)
	{
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->Draw();
		break;
		// �I�v�V�����V�[��
	case kSceneOption:
		m_pOption->Draw();
		break;
		// �X�e�[�W�I���V�[��
	case kSceneStageSelect:
		m_pStageSelect->Draw();
		break;
		// �Q�[���V�[��
	case kSceneMain:
		m_pMain->Draw();
		break;
		// �Q�[���N���A
	case kSceneClear:
		m_pClear->Draw();
		break;
		// �Q�[���I�[�o�[
	case kSceneGameOver:
		m_pGameOver->Draw();
		break;
	default:
		break;
	}
}
