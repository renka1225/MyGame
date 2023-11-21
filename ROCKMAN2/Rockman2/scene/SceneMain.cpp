#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Player.h"
#include "ShotBuster.h"
#include <cassert>

namespace
{
	// ��ʓ���1�x�ɏo����e��
	constexpr int kShotMax = 3;
}

SceneMain::SceneMain()
{
	// �O���t�B�b�N�̃��[�h
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);
	m_shotBusterHandle = LoadGraph("data/image/shotBuster.png");
	assert(m_shotBusterHandle != -1);

	// �v���C���[�̃������m��
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	// Player�ɃO���t�B�b�N�̃n���h����n��

	// �V���b�g�̏���
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr; // ���g�p��Ԃɂ���
	}
}

SceneMain::~SceneMain()
{
	// ����������O���t�B�b�N���폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_shotBusterHandle);

	// �������̉��
	delete m_pPlayer;
	m_pPlayer = nullptr;

	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])
		{
			// nullptr�łȂ��ꍇ�Anullptr������
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}
}

void SceneMain::Init()
{
	assert(m_pPlayer);	// m_pPlayer == nullptr�̏ꍇ�~�܂�
	m_pPlayer->Init();
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	m_pPlayer->Update();

	Rect playerRect = m_pPlayer->GetColRect();

	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pShot[i]) continue;

		m_pShot[i]->Update();
		// ��ʊO�ɏo���烁�������������
		if (!m_pShot[i]->IsExist())
		{
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}
}

void SceneMain::Draw()
{
	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// �e�̕`��
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pShot[i])continue;
		m_pShot[i]->Draw();
	}


	// �v���C���[�̍��W���f�o�b�O�\������
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawFormatString(8, 24, 0xffffff, "�v���C���[�̍��W(%.2f, %.2f)", playerPos.x, playerPos.y);
}

bool SceneMain::AddShot(ShotBase* pShot)
{
	// nullptr��n���ꂽ��~�܂�
	assert(pShot);

	for (int i = 0; i < m_pShot.size(); i++)
	{
		// �g�p���Ȃ玟�̃`�F�b�N���s��
		if (m_pShot[i])continue;

		// m_pShot[i] == nullptr�Ȃ̂ŐV�����o�^����
		m_pShot[i] = pShot;
		// �o�^������I��
		return true;
	}

	// m_pShot�Ƀ|�C���^��o�^�ł��Ȃ�����
	delete pShot;
	return false;
}
