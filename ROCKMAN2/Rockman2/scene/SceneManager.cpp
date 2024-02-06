#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneStage1.h"
#include "SceneClear.h"
#include "SceneGameOver.h"
#include "Pad.h"

SceneManager::SceneManager() :
	m_runScene(kSceneTitle)
{
	// �N���X�̃��������m�ۂ���
	m_pTitle = new SceneTitle;
	//m_pOption = new SceneOption;
	m_pStage1 = new SceneStage1;
	m_pClear = new SceneClear;
	m_pGameOver = new SceneGameOver;
}

SceneManager::~SceneManager()
{
	// �N���X�̃��������������
	delete m_pTitle;
	m_pTitle = nullptr;

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
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->Init();
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

void SceneManager::End()
{
	// ���s����V�[�����I������
	switch (m_runScene)
	{
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->End();
		break;
		// �X�e�[�W1
	case kSceneStage1:
		m_pStage1->End();
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
			m_runScene = kSceneStage1;
			m_pStage1->Init();
		}
		break;
		// �X�e�[�W1
	case kSceneStage1:
		m_pStage1->End();
		if (m_pStage1->IsSceneGameOver())
		{
			m_runScene = kSceneGameOver;
			m_pGameOver->Init();
		}
		else if (m_pStage1->IsSceneClear())
		{
			m_runScene = kSceneClear;
			m_pClear->Init();
		}
		else if (m_pStage1->IsSceneTitle())
		{
			m_runScene = kSceneTitle;
			m_pTitle->Init();
			m_pStage1->Init();
		}
		else if (m_pStage1->IsSceneEnd()) // ���g���C
		{
			m_runScene = kSceneStage1;
			m_pStage1->Init();
		}
		break;

		// �Q�[���N���A
	case kSceneClear:
		m_pClear->End();
		if (m_pClear->IsSceneStageSelect())
		{
			m_runScene = kSceneStage1;
			m_pStage1->Init();
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
		if (m_pGameOver->IsSeneRetry()) // ���g���C
		{
			m_runScene = kSceneStage1;
			m_pStage1->Init();
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
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->Update();
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
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->Draw();
		break;
		// �X�e�[�W1
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
