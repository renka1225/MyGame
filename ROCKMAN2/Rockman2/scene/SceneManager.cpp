#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneGameOver.h"
#include "Pad.h"

SceneManager::SceneManager() :
	m_runScene(kSceneKindTitle)
{
	// �N���X�̃��������m�ۂ���
	m_pTitle = new SceneTitle;
	m_pMain = new SceneMain;
	m_pGameOver = new SceneGameOver;
}

SceneManager::~SceneManager()
{
	// �N���X�̃��������������
	delete m_pTitle;
	m_pTitle = nullptr;

	delete m_pMain;
	m_pMain = nullptr;

	delete m_pGameOver;
	m_pGameOver = nullptr;
}

void SceneManager::Init()
{
	// ���s����V�[���̏��������s��
	switch (m_runScene)
	{
	case kSceneKindTitle: // �^�C�g���V�[���̏ꍇ
		m_pTitle->Init();
		break;
	case kSceneKindMain: // �Q�[���V�[���̏ꍇ
		m_pMain->Init();
		break;
	case kSceneKindGameOver: // �Q�[���I�[�o�[�̏ꍇ
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
	case kSceneKindTitle: // �^�C�g���V�[���̏ꍇ
		m_pTitle->End();
		break;
	case kSceneKindMain: // �Q�[���V�[���̏ꍇ
		m_pMain->End();
		break;
	case kSceneKindGameOver: // �Q�[���I�[�o�[�̏ꍇ
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
	case kSceneKindTitle: // �^�C�g���V�[���̏ꍇ
		// �^�C�g����ʂ��I�����ꂽ��
		if (m_pTitle->IsSceneEnd())
		{
			m_pTitle->End();			 // �^�C�g���̏I���������s��
			m_runScene = kSceneKindMain; // �Q�[����ʂɐ؂�ւ���
			m_pMain->Init();			 // �Q�[����ʂ̏�����
		}
		break;
	case kSceneKindMain: // �Q�[���V�[���̏ꍇ
		// �Q�[����ʂ��I�����ꂽ��
		if (m_pMain->IsSceneEnd())
		{
			m_pMain->End();					 // �Q�[���V�[���̏I���������s��
			m_runScene = kSceneKindGameOver; // �Q�[���I�[�o�[��ʂɐ؂�ւ���
			m_pGameOver->Init();			 // �Q�[���I�[�o�[��ʂ̏�����
		}
		break;
	case kSceneKindGameOver: // �Q�[���I�[�o�[�V�[���̏ꍇ
		// �Q�[���I�[�o�[��ʂ��I�����ꂽ��
		if (m_pGameOver->IsSceneEnd())
		{
			m_pGameOver->End();				// �Q�[���I�[�o�[�̏I���������s��
			m_runScene = kSceneKindTitle;	// �^�C�g����ʂɐ؂�ւ���
			m_pTitle->Init();				// �^�C�g����ʂ̏�����
		}
		break;
	}

	// ���s����V�[���̍X�V���s��
	switch (m_runScene)
	{
	case kSceneKindTitle: // �^�C�g���V�[���̏ꍇ
		m_pTitle->Update();
		break;
	case kSceneKindMain: // �Q�[���V�[���̏ꍇ
		m_pMain->Update();
		break;
	case kSceneKindGameOver: // �Q�[���I�[�o�[�̏ꍇ
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
	case kSceneKindTitle: // �^�C�g���V�[���̏ꍇ
		m_pTitle->Draw();
		break;
	case kSceneKindMain: // �Q�[���V�[���̏ꍇ
		m_pMain->Draw();
		break;
	case kSceneKindGameOver: // �Q�[���I�[�o�[�̏ꍇ
		m_pGameOver->Draw();
		break;
	default:
		break;
	}
}
