#include "SceneManager.h"
#include "SceneTitle.h"
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
	case kSceneTitle:		// �^�C�g���V�[���̏ꍇ
		m_pTitle->Init();
		break;
	case kSceneStageSelect: // �X�e�[�W�I���V�[���̏ꍇ
		m_pStageSelect->Init();
		break;
	case kSceneMain:		// �Q�[���V�[���̏ꍇ
		m_pMain->Init();
		break;
	case kSceneClear:		// �Q�[���N���A�̏ꍇ
		m_pClear->Init();
		break;
	case kSceneGameOver:	// �Q�[���I�[�o�[�̏ꍇ
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
	case kSceneTitle: // �^�C�g���V�[���̏ꍇ
		m_pTitle->End();
		break;
	case kSceneStageSelect: // �X�e�[�W�I���V�[���̏ꍇ
		m_pStageSelect->End();
		break;
	case kSceneMain: // �Q�[���V�[���̏ꍇ
		m_pMain->End();
		break;
	case kSceneClear:		// �Q�[���N���A�̏ꍇ
		m_pClear->End();
		break;
	case kSceneGameOver: // �Q�[���I�[�o�[�̏ꍇ
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
	case kSceneTitle: // �^�C�g���V�[���̏ꍇ
		// �^�C�g����ʂ��I�����ꂽ��
		if (m_pTitle->IsSceneEnd())
		{
			m_pTitle->End();					// �^�C�g���̏I���������s��
			m_runScene = kSceneStageSelect; // �X�e�[�W�I����ʂɐ؂�ւ���
			m_pMain->Init();					// �Q�[����ʂ̏�����
		}
		break;
	case kSceneStageSelect: // �X�e�[�W�I���V�[���̏ꍇ
		if (m_pStageSelect->IsSceneEnd())
			m_runScene = kSceneMain;
		break;
	case kSceneMain: // �Q�[���V�[���̏ꍇ
		// �Q�[����ʂ��I�����ꂽ��
		if (m_pMain->IsSceneEnd())
		{
			m_pMain->End();					 // �Q�[���V�[���̏I���������s��
			m_runScene = kSceneGameOver; // �Q�[���I�[�o�[��ʂɐ؂�ւ���
			m_pGameOver->Init();			 // �Q�[���I�[�o�[��ʂ̏�����
		}
		break;
	case kSceneClear:		// �Q�[���N���A�̏ꍇ
		m_pClear->Init();
		break;
	case kSceneGameOver: // �Q�[���I�[�o�[�V�[���̏ꍇ
		// �Q�[���I�[�o�[��ʂ��I�����ꂽ��
		if (m_pGameOver->IsSceneEnd())
		{
			m_pGameOver->End();				// �Q�[���I�[�o�[�̏I���������s��
			m_runScene = kSceneTitle;	// �^�C�g����ʂɐ؂�ւ���
			m_pTitle->Init();				// �^�C�g����ʂ̏�����
		}
		break;
	}

	// ���s����V�[���̍X�V���s��
	switch (m_runScene)
	{
	case kSceneTitle: // �^�C�g���V�[���̏ꍇ
		m_pTitle->Update();
		break;
	case kSceneStageSelect: // �X�e�[�W�I���V�[���̏ꍇ
		m_pStageSelect->Update();
		break;
	case kSceneMain: // �Q�[���V�[���̏ꍇ
		m_pMain->Update();
		break;
	case kSceneClear:		// �Q�[���N���A�̏ꍇ
		m_pClear->Draw();
		break;
	case kSceneGameOver: // �Q�[���I�[�o�[�̏ꍇ
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
	case kSceneTitle: // �^�C�g���V�[���̏ꍇ
		m_pTitle->Draw();
		break;
	case kSceneStageSelect: // �X�e�[�W�I���V�[���̏ꍇ
		m_pStageSelect->Draw();
		break;
	case kSceneMain: // �Q�[���V�[���̏ꍇ
		m_pMain->Draw();
		break;
	case kSceneClear:		// �Q�[���N���A�̏ꍇ
		m_pClear->Draw();
		break;
	case kSceneGameOver: // �Q�[���I�[�o�[�̏ꍇ
		m_pGameOver->Draw();
		break;
	default:
		break;
	}
}
