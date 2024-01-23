#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneOption.h"
#include "SceneStageSelect.h"
#include "SceneMain.h"
#include "SceneStage2.h"
#include "SceneStage3.h"
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
	m_pStage2 = new SceneStage2;
	m_pStage3 = new SceneStage3;
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

	delete m_pStage2;
	m_pStage2 = nullptr;

	delete m_pStage3;
	m_pStage3 = nullptr;

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
		// �X�e�[�W2
	case kSceneStage2:
		m_pStage2->Init();
		break;
		// �X�e�[�W3
	case kSceneStage3:
		m_pStage3->Init();
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
		// �X�e�[�W2
	case kSceneStage2:
		m_pStage2->End();
		break;
		// �X�e�[�W3
	case kSceneStage3:
		m_pStage3->End();
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
		m_pOption->End();
		if (m_pOption->IsSceneTitle())
		{
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
		else if (m_pStageSelect->IsSceneStage2())
		{
			m_runScene = kSceneStage2;
			m_pStage2->Init();
		}
		else if (m_pStageSelect->IsSceneStage3())
		{
			m_runScene = kSceneStage3;
			m_pStage3->Init();
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

		// �X�e�[�W2
	case kSceneStage2:
		m_pStage2->End();
		if (m_pStage2->IsSceneGameOver())
		{
			m_runScene = kSceneGameOver;
			m_pGameOver->Init();
		}
		else if (m_pStage2->IsSceneClear())
		{
			m_runScene = kSceneClear;
			m_pClear->Init();
		}
		break;

		// �X�e�[�W3
	case kSceneStage3:
		m_pStage3->End();
		if (m_pStage3->IsSceneGameOver())
		{
			m_runScene = kSceneGameOver;
			m_pGameOver->Init();
		}
		else if (m_pStage3->IsSceneClear())
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
		m_pGameOver->End();
		if (m_pGameOver->IsSceneSelect())
		{
			m_runScene = kSceneStageSelect;
			m_pStageSelect->Init();
		}
		else if (m_pGameOver->IsSceneTitle())
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

	default:
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
		// �X�e�[�W2
	case kSceneStage2:
		m_pStage2->Update();
		break;
		// �X�e�[�W3
	case kSceneStage3:
		m_pStage3->Update();
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
		// �X�e�[�W2
	case kSceneStage2:
		m_pStage2->Draw();
		break;
		// �X�e�[�W3
	case kSceneStage3:
		m_pStage3->Draw();
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
