#include "SceneManager.h"
#include "SceneOpening.h"
#include "SceneTitle.h"
#include "SceneOption.h"
#include "SceneStageSelect.h"
#include "SceneTutorial.h"
#include "SceneStage1.h"
#include "SceneClear.h"
#include "SceneGameOver.h"
#include "Pad.h"

SceneManager::SceneManager() :
	m_runScene(kSceneOpening)
{
	// �N���X�̃��������m�ۂ���
	m_pOpening = new SceneOpening;
	m_pTitle = new SceneTitle;
	m_pOption = new SceneOption;
	m_pStageSelect = new SceneStageSelect;
	m_pTutorial = new SceneTutorial;
	m_pStage1 = new SceneStage1;
	m_pClear = new SceneClear;
	m_pGameOver = new SceneGameOver;
}

SceneManager::~SceneManager()
{
	// �N���X�̃��������������
	delete m_pOpening;
	m_pOpening = nullptr;

	delete m_pTitle;
	m_pTitle = nullptr;

	delete m_pOption;
	m_pOption = nullptr;

	delete m_pStageSelect;
	m_pStageSelect = nullptr;

	delete m_pTutorial;
	m_pTutorial = nullptr;

	delete m_pStage1;
	m_pStage1 = nullptr;

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
		// Op�V�[��
	case kSceneOpening:
		m_pOpening->Init();
		break;
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->Init();
		break;
		// �������
	case kSceneOption:
		m_pOption->Init();
		break;
		// �X�e�[�W�I���V�[��
	case kSceneStageSelect:
		m_pStageSelect->Init();
		break;
		// �`���[�g���A��
	case kSceneTutorial:
		m_pTutorial->Init();
		break;
		// �X�e�[�W1
	case kSceneStage1:
		m_pStage1->Init();
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

void SceneManager::Update()
{
	Pad::Update();

	// ���s����V�[���̐؂�ւ����s��
	switch (m_runScene)
	{
		// �I�[�v�j���O�V�[��
	case kSceneOpening:
		if (m_pOpening->IsSceneStart())
		{
			m_runScene = kSceneTitle;
			m_pOpening->Init();
		}
		break;
		// �^�C�g���V�[��
	case kSceneTitle:
		if (m_pTitle->IsSceneOpening())
		{
			m_runScene = kSceneOpening;
			m_pOpening->Init();
		}
		 else if (m_pTitle->IsSceneStart())
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

		// �������
	case kSceneOption:
		if (m_pOption->IsSceneTitle())
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

		// �X�e�[�W�I���V�[��
	case kSceneStageSelect:
		if (m_pStageSelect->IsSceneTutorial())		// �`���[�g���A��
		{
			m_runScene = kSceneTutorial;
			m_pTutorial->Init();
		}
		else if (m_pStageSelect->IsSceneStage1())	// �X�e�[�W1
		{
			m_runScene = kSceneStage1;
			m_pStage1->Init();
		}
		else if (m_pStageSelect->IsSceneTitle())	// �^�C�g��
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

		// �`���[�g���A��
	case kSceneTutorial:
		if (m_pTutorial->IsSceneGameOver())		// �Q�[���I�[�o�[
		{
			m_runScene = kSceneGameOver;
			m_pGameOver->Init();
		}
		else if (m_pTutorial->IsSceneClear())	// �Q�[���N���A
		{
			m_runScene = kSceneClear;
			m_pClear->Init();
		}
		else if (m_pTutorial->IsSceneTitle())	// �^�C�g��
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
			m_pTutorial->Init();
		}
		else if (m_pTutorial->IsSceneEnd())		// ���g���C
		{
			m_runScene = kSceneTutorial;
			m_pTutorial->Init();
		}
		break;


		// �X�e�[�W1
	case kSceneStage1:
		if (m_pStage1->IsSceneGameOver())		// �Q�[���I�[�o�[
		{
			m_runScene = kSceneGameOver;
			m_pGameOver->Init();
		}
		else if (m_pStage1->IsSceneClear())		// �N���A
		{
			m_runScene = kSceneClear;
			m_pClear->Init();
		}
		else if (m_pStage1->IsSceneTitle())		// �^�C�g��
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
			m_pStage1->Init();
		}
		else if (m_pStage1->IsSceneEnd())		// ���g���C
		{
			m_runScene = kSceneStage1;
			m_pStage1->Init();
		}
		break;

		// �Q�[���N���A
	case kSceneClear:
		if (m_pClear->IsSceneStageSelect())		// ���g���C
		{
			m_runScene = kSceneStageSelect;
			m_pStageSelect->Init();
		}
		else if (m_pClear->IsSceneTitle())		// �^�C�g��
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
		}
		break;

		// �Q�[���I�[�o�[
	case kSceneGameOver:
		if (m_pGameOver->IsSeneRetry())			 // ���g���C
		{
			if (m_pTutorial->IsSceneGameOver())
			{
				m_runScene = kSceneTutorial;
				m_pTutorial->Init();
			}
			if (m_pStage1->IsSceneGameOver())
			{
				m_runScene = kSceneStage1;
				m_pStage1->Init();
			}
		}
		else if (m_pGameOver->IsSceneSelect())
		{
			m_runScene = kSceneStageSelect;
			m_pStageSelect->Init();
		}
		else if (m_pGameOver->IsSceneTitle())	// �^�C�g��
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
		// Op�V�[��
	case kSceneOpening:
		m_pOpening->Update();
		break;
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->Update();
		break;
		// �������
	case kSceneOption:
		m_pOption->Update();
		break;
		// �X�e�[�W�I���V�[��
	case kSceneStageSelect:
		m_pStageSelect->Update();
		break;
		// �`���[�g���A��
	case kSceneTutorial:
		m_pTutorial->Update();
		break;
		// �X�e�[�W1
	case kSceneStage1:
		m_pStage1->Update();
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
		// �I�[�v�j���O�V�[��
	case kSceneOpening:
		break;
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->Draw();
		break;
		// �������
	case kSceneOption:
		m_pOption->Draw();
		break;
		// �X�e�[�W�I���V�[��
	case kSceneStageSelect:
		m_pStageSelect->Draw();
		break;
		// �`���[�g���A��
	case kSceneTutorial:
		m_pTutorial->Draw();
		break;
		// �Q�[���V�[��
	case kSceneStage1:
		m_pStage1->Draw();
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
