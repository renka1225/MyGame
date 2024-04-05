#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "ManagerFont.h"
#include "ManagerModel.h"
#include "Background.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Input.h"
#include "Rect.h"
#include "Game.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>


/// <summary>
/// �R���X�g���N�^
/// </summary>
ScenePlaying::ScenePlaying():
	m_time(0),
	m_noticeDisPlayFrame(0)
{
	m_pModel = std::make_shared<ManagerModel>();
	m_pCamera = std::make_shared<Camera>();
	m_pMap = std::make_shared<Map>();
	m_pBackground = std::make_shared<Background>();
	m_pPlayer = std::make_shared<Player>(m_pModel, m_pMap);

	m_pEnemy.resize(kEnemyNum);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = std::make_shared<Enemy>(m_pModel);
	}
}


/// <summary>
/// ������
/// </summary>
void ScenePlaying::Init()
{
	// �}�b�v�f�[�^�ǂݍ���
	m_pMap->Init("data/file/map.fmf");
	// �G��csv�t�@�C���ǂݍ���
	LoadEnemy();
	
	m_enemyPos.resize(kEnemyNum);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i]->Init(m_enemyPos[i]);
	}
}


/// <summary>
/// �X�V
/// </summary>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	// �^�C���X�V
	m_time++;
	// 20�b���ƂɎ��Ԍo�߂̒ʒm��\������
	UpdateNotice();

	// �N���A��ʂɑJ��
	if (m_time >= kClearTime)
	{
		return std::make_shared<SceneClear>();
	}

	// �w�i�̍X�V
	m_pBackground->Update();
	// �v���C���[�̍X�V
	m_pPlayer->Update(input);
	// �J�����̍X�V
	m_pCamera->Update(m_pPlayer);
	// �G�̍X�V
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// �G�̍X�V
		if (m_pEnemy[i])
		{
			m_pEnemy[i]->Update();
		}

		// �v���C���[�̓����蔻��
		Rect playerRect = m_pPlayer->GetColRect();
		// �G�̓����蔻��
		Rect enemyRect = m_pEnemy[i]->GetColRect();
		if (playerRect.IsCollision(enemyRect))
		{
			// TODO:�Q�[���I�[�o�[��ʂɑJ��
			//return std::make_shared<SceneGameover>();

#ifdef _DEBUG
			DrawString(0, 80, "��������", 0xff0000);
#endif
		}
	}

#if _DEBUG
	// MEMO:�f�o�b�N�p�R�}���h
	if (input.IsTriggered("debug"))
	{
		return std::make_shared<SceneClear>();
	}
	else if (input.IsTriggered("debug2"))
	{
		return std::make_shared<SceneGameover>();
	}
#endif

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePlaying::Draw()
{
	// �w�i�̕`��
	m_pBackground->Draw();

	// �}�b�v�̕`��
	m_pMap->Draw(m_pCamera);

	// �G�̕`��
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if(m_pEnemy[i])
		{
			m_pEnemy[i]->Draw();
		}
	}

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// �o�ߎ��Ԃ̕`��
	int milliSec = m_time * 1000 / 60;
	int sec = (milliSec / 1000) % 90;
	milliSec %= 1000;
	DrawFormatStringToHandle(kTimePosX, kTimePosY, 0xffd700, m_pFont->GetTimeFont(), "�o�ߎ��� %02d:%03d", sec, milliSec);

	DrawNotice();

#if _DEBUG
	DrawFormatString(0, 0, 0xffffff, "�v���C���");
#endif
}


/// <summary>
/// �I��
/// </summary>
void ScenePlaying::End()
{
}


/// <summary>
/// csv�t�@�C���ǂݍ���
/// </summary>
void ScenePlaying::LoadEnemy()
{
	std::ifstream file;
	file.open("data/file/enemy.csv");
	if (!file.is_open())	// �t�@�C���ǂݍ��ݎ��s��
	{
		printfDx("�t�@�C���ǂݍ��ݎ��s\n");
	}
	else
	{
		std::string path;	// �ǂݎ�茳
		while (std::getline(file, path))
		{
			std::istringstream istream(path);
			std::string line;
			VECTOR pos = VGet(0.0f, 0.0f, 0.0f);

			if (std::getline(istream, line, ',') &&
				std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &pos.x) &&
				std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &pos.y) &&
				std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &pos.z))
			{
				m_enemyPos.push_back(pos);
			}
		}
	}
	file.close();
}


/// <summary>
/// ���Ԍo�߂̒ʒm���s��
/// </summary>
void ScenePlaying::UpdateNotice()
{
	m_noticeDisPlayFrame--;
	if (m_noticeDisPlayFrame < 0)
	{
		m_noticeDisPlayFrame = 0;
	}
	if (m_time == kNoticeTime1)
	{
		m_noticeDisPlayFrame = kNoticeDisPlayFrame;
	}
	if (m_time == kNoticeTime2)
	{
		m_noticeDisPlayFrame = kNoticeDisPlayFrame;
	}
	if (m_time == kNoticeTime3)
	{
		m_noticeDisPlayFrame = kNoticeDisPlayFrame;
	}
	if (m_time == kNoticeTime4)
	{
		m_noticeDisPlayFrame = kNoticeDisPlayFrame;
	}
}


/// <summary>
/// ���Ԍo�߂̒ʒm��\��
/// </summary>
void ScenePlaying::DrawNotice()
{
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime1 && m_time < kNoticeTime2)
	{
		DrawFormatStringToHandle(kNoticeTimePosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "20�b�o�߁I");
	}
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime2 && m_time < kNoticeTime3)
	{
		DrawFormatStringToHandle(kNoticeTimePosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "40�b�o�߁I");
	}
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime3 && m_time < kNoticeTime4)
	{
		DrawFormatStringToHandle(kNoticeTimePosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "60�b�o�߁I");
	}
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime4)
	{
		DrawFormatStringToHandle(kNoticeTimePosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "80�b�o�߁I");
	}
}
