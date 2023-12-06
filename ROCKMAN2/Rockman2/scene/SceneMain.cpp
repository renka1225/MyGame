#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "Bg.h"
#include "Player.h"

#include "ShotBase.h"

#include "Matasaburo.h"
#include <cassert>

namespace
{
	// ��ʓ���1�x�ɏo����e��
	constexpr int kShotMax = 3;
	// 1�x�ɓo��ł���G��
	constexpr int kEnemyMax = 3;
}

SceneMain::SceneMain()
{
	// �v���C���[�̃O���t�B�b�N���[�h
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);
	m_bgHandle = LoadGraph("data/image/backGround.png");
	assert(m_bgHandle != -1);
	m_enemyHandle = LoadGraph("data/image/Enemy/matasaburo.png");
	assert(m_bgHandle != -1);

	// �w�i�̃������m��
	m_pBg = new Bg;
	m_pBg->SetHandle(m_bgHandle);

	// �v���C���[�̃������m��
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	// Player�ɃO���t�B�b�N�̃n���h����n��

	// �V���b�g�̃������m��
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr; // ���g�p��Ԃɂ���
	}

	// �G�̃������m��
	m_pEnemy.resize(kEnemyMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pEnemy[i] = nullptr; // ���g�p��Ԃɂ���
	}
}

SceneMain::~SceneMain()
{
	// ����������O���t�B�b�N���폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_enemyHandle);

	// �v���C���[�̃��������
	delete m_pPlayer;
	m_pPlayer = nullptr;

	// �w�i�̃��������
	delete m_pBg;
	m_pBg = nullptr;

	// �V���b�g�̃��������
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])
		{
			// nullptr�łȂ��ꍇ�Anullptr������
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}

	// �G�̃��������
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			// nullptr�łȂ��ꍇ�Anullptr������
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;
		}
	}
}

void SceneMain::Init()
{
	// �v���C���[�̏�����
	assert(m_pPlayer);	// m_pPlayer == nullptr�̏ꍇ�~�܂�
	m_pPlayer->Init();

	// �w�i�̏�����
	m_pBg->Init();
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	// �w�i�̍X�V
	m_pBg->Update();

	// �v���C���[�̍X�V
	m_pPlayer->Update();
	Rect playerRect = m_pPlayer->GetColRect(); // �v���C���[�̓����蔻��

<<<<<<< HEAD
	Vec2 playerPos = m_pPlayer->GetPos(); // �v���C���[�̌��ݒn���擾

	// �v���C���[����ʒ������E�Ɉړ�������G��o�ꂳ����
	if (playerPos.x > Game::kScreenWidth / 2)
	{
		CreateMatasaburo();
	}

	// �e�̍X�V
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

=======
>>>>>>> b7e625657adb768e3ac97a47834cb71cb76e3f7e
	// �G�̍X�V
	CreateMatasaburo();
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
<<<<<<< HEAD
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pEnemy[i]) continue;
		m_pEnemy[i]->Update();

		// �g�p�ς݂̓G�L�����N�^�[���폜
		if (!m_pEnemy[i]->IsExist())
		{
			// ���������������
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;	// nullptr������
		}
		else
		{
			// �G�ƃv���C���[�̓����蔻��
			Rect enemyRect = m_pEnemy[i]->GetColRect();
			if (playerRect.IsCollision(enemyRect))
=======
		if (m_pEnemy[i])	// nullptr�łȂ��ꍇ
		{
			m_pEnemy[i]->Update();

			Rect enemyRect = m_pEnemy[i]->GetColRect(); // �G�̓����蔻����擾

			// �e�Ƃ̓����蔻��
			for (int j = 0; j < m_pShot.size(); j++)
			{
				if (m_pShot[j])
				{
					Rect shotRect = m_pShot[j]->GetColRect();	// �e�̓����蔻����擾
					if (shotRect.IsCollision(enemyRect))
					{
						m_pEnemy[i]->OnDamage(1);	// �G��HP�����炷
					}
				}
			}
			// �v���C���[�Ƃ̓����蔻��
			if (playerRect.IsCollision(enemyRect))
			{
				m_pPlayer->OnDamage();
			}

			// �g�p�ς݂̓G�L�����N�^�[���폜
			if (!m_pEnemy[i]->IsExist())
>>>>>>> b7e625657adb768e3ac97a47834cb71cb76e3f7e
			{
				m_pPlayer->OnDamage();
			}
<<<<<<< HEAD

			for (int j = 0; j < m_pShot.size(); j++)
			{
				// nullptr�Ȃ珈���͍s��Ȃ�
				if (!m_pShot[j]) continue;

				// �G�ƒe�̓����蔻��
				Rect shotRect = m_pShot[j]->GetColRect(); // �e�̓����蔻��
				if (shotRect.IsCollision(enemyRect))
				{
					m_pEnemy[i]->OnDamage();
				}
				if (enemyRect.IsCollision(shotRect))
				{
					// �e���폜
					delete m_pShot[j];
					m_pShot[j] = nullptr;
				}
			}
=======
		}
	}

	// �e�̍X�V
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pShot[i]) continue;

		m_pShot[i]->Update();

		Rect enemyRect = m_pEnemy[i]->GetColRect(); // �G�̓����蔻��
		Rect shotRect = m_pShot[i]->GetColRect();	// �e�̓����蔻��

		// �e���G�ɓ��������A�܂��͒e����ʊO�ɏo���烁�������������
		if (enemyRect.IsCollision(shotRect) || !m_pShot[i]->IsExist())
		{
			// �e���폜
			delete m_pShot[i];
			m_pShot[i] = nullptr;
>>>>>>> b7e625657adb768e3ac97a47834cb71cb76e3f7e
		}
	}
}

void SceneMain::Draw()
{
	// �`���X�N���[�����N���A����
	ClearDrawScreen();

	// �w�i�̕`��
	m_pBg->Draw();

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// �e�̕`��
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pShot[i])continue;
		m_pShot[i]->Draw();
	}

<<<<<<< HEAD
	// �G�̕`��
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pEnemy[i])continue;
		m_pEnemy[i]->Draw();
=======
	// nullptr�ł͂Ȃ����`�F�b�N
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			m_pEnemy[i]->Draw();
		}
>>>>>>> b7e625657adb768e3ac97a47834cb71cb76e3f7e
	}

	// ���݂�HP��\��
	DrawFormatString(8, 8, 0xffffff, "HP:%.2f", m_pPlayer->GetHp());
	// ���݂̒e�G�l���M�[����\��
	DrawFormatString(8, 28, 0xffffff, "���^��: %.2f", m_pPlayer->GetMetalEnergy());
	DrawFormatString(8, 48, 0xffffff, "�t�@�C���[: %.2f", m_pPlayer->GetFireEnergy());
	DrawFormatString(8, 68, 0xffffff, "�A�C�e��2��: %.2f", m_pPlayer->GetLineEnergy());
	// ���������Ԃ�\��
	DrawFormatString(8, 88, 0xffffff, "����������:%d", m_pPlayer->GetPressTime());
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

void SceneMain::CreateMatasaburo()
{
	//�g���Ă��Ȃ��ꏊ�ɃA�h���X��ۑ�����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	// nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			m_pEnemy[i] = new Matasaburo;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	// 1�̕����������m�ۂł����炻�̎��_�ŏI��
		}
	}
}
