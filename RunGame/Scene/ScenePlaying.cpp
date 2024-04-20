#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
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
	m_startTime(kStartTime),
	m_noticeDisPlayFrame(0),
	m_noticePos(VGet(Game::kScreenWidth, 0.0f, 0.0f)),
	m_fadeAlpha(kStartFadeAlpha)
{
	// �G��csv�t�@�C���ǂݍ���
	LoadEnemy();

	m_pModel = std::make_shared<ManagerModel>();
	m_pCamera = std::make_shared<Camera>();
	m_pBackground = std::make_shared<Background>();
	m_pMap = std::make_shared<Map>();
	m_pPlayer = std::make_shared<Player>(m_pModel, m_pSound, m_pMap);

	m_pEnemy.resize(kEnemyNum);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = std::make_shared<Enemy>(m_pModel, m_enemyPos[i]);
	}

	// �X�^�[�gSE
	PlaySoundMem(m_pSound->GetStartCountSE(), DX_PLAYTYPE_BACK);
}


/// <summary>
/// ������
/// </summary>
void ScenePlaying::Init()
{
	// �}�b�v�f�[�^�ǂݍ���
 	m_pMap->Load();
}


/// <summary>
/// �X�V
/// </summary>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	// �t�F�[�h�A�E�g
	m_fadeAlpha -= kFadeFrame;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	// �w�i�̍X�V
	m_pBackground->Update();
	// �v���C���[�̍X�V
	m_pPlayer->Update(input);
	// �J�����̍X�V
	m_pCamera->Update(m_pPlayer);

	// �X�^�[�g���o���s��
	if (m_startTime > 0)
	{
		m_startTime--;
		return shared_from_this();
	}

	// �G�̍X�V
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	// nullptr�ł͂Ȃ��`�F�b�N
		{
 			m_pEnemy[i]->Update();

			// �v���C���[�̓����蔻��
			Rect playerRect = m_pPlayer->GetColRect();
			// �G�̓����蔻��
			Rect enemyRect = m_pEnemy[i]->GetColRect();
			if (playerRect.IsCollision(enemyRect))
			{
				PlaySoundMem(m_pSound->GetDamageSE(), DX_PLAYTYPE_BACK);
				//�Q�[���I�[�o�[��ʂɑJ��
				return std::make_shared<SceneGameover>();
			}
		}
	}

	// BGM��炷
	if (!CheckSoundMem(m_pSound->GetPlayBgm()))
	{
		PlaySoundMem(m_pSound->GetPlayBgm(), DX_PLAYTYPE_BACK);
	}

	// �^�C���X�V
	m_time++;
	// 20�b���ƂɎ��Ԍo�߂̒ʒm��\������
	UpdateNotice();

	// �N���A��ʂɑJ��
	if (m_time >= kClearTime)
	{
		return std::make_shared<SceneClear>();
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

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// �}�b�v�̕`��
	m_pMap->Draw();

	// �G�̕`��
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			m_pEnemy[i]->Draw();
		}
	}

	// ��������̕\��
	DrawFormatStringToHandle(kNoticeStartPosX, kStartCountPosY, 0xffd700, m_pFont->GetStartCountFont(), "");

	if (m_startTime > 0)
	{
		// �t�F�[�h�C���A�E�g
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x20b2aa, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		// �X�^�[�g���o�̕\��
		StartStaging();
	}
	else
	{
		// �o�ߎ��Ԃ̕`��
		int milliSec = m_time * 1000 / 60;
		int sec = (milliSec / 1000) % 90;
		milliSec %= 1000;
		DrawFormatStringToHandle(kTimePosX, kTimePosY, 0xffd700, m_pFont->GetTimeFont(), "�o�ߎ��� %02d:%03d", sec, milliSec);
		// ���Ԍo�߂̒ʒm��\��
		DrawNotice();
	}

#if _DEBUG
	// MEMO:�f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�v���C���");
	// MEMO:���S��
	//DrawLine(Game::kScreenWidth * 0.5f, 0, Game::kScreenWidth * 0.5f, Game::kScreenHeight, 0x0000000, 1);
#endif
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
/// �X�^�[�g���o
/// </summary>
void ScenePlaying::StartStaging()
{
	DrawFormatStringToHandle(kTimePosX, kExPosY, 0xffffff, m_pFont->GetTimeFont(), "SPACE�ŃW�����v�I");	// �������

	if (m_startTime >= kStartCount1)
	{
		DrawFormatStringToHandle(kStartCountPosX, kStartCountPosY, 0xffd700, m_pFont->GetStartCountFont(), "3");
	}
	if (m_startTime < kStartCount1 && m_startTime >= kStartCount2)
	{
		DrawFormatStringToHandle(kStartCountPosX, kStartCountPosY, 0xffd700, m_pFont->GetStartCountFont(), "2");
	}
	if (m_startTime <= kStartCount2 && m_startTime > kStartCount3)
	{
		DrawFormatStringToHandle(kStartCountPosX, kStartCountPosY, 0xffd700, m_pFont->GetStartCountFont(), "1");
	}
	if (m_startTime < kStartCount3 && m_startTime >= kStartCount4)
	{
		DrawFormatStringToHandle(kNoticeStartPosX, kStartCountPosY, 0xffd700, m_pFont->GetStartCountFont(), "START!");
	}
}


/// <summary>
/// ���Ԍo�߂̒ʒm���s��
/// </summary>
void ScenePlaying::UpdateNotice()
{
	m_noticeDisPlayFrame--;
	if (m_noticeDisPlayFrame > 0)
	{
		m_noticePos = VGet(Game::kScreenWidth + (-Game::kScreenWidth * kNoticeMove), 0.0f, 0.0f);	// �ʒm���E���獶�Ɉړ�
	}
	else
	{
		m_noticeDisPlayFrame = 0;
		m_noticePos = VGet(Game::kScreenWidth, 0.0f, 0.0f);
	}

	if (m_time == kNoticeTime1 || m_time == kNoticeTime2 || m_time == kNoticeTime3 || m_time == kNoticeTime4)	// 20�b���ƂɎ��s
	{
		PlaySoundMem(m_pSound->GetNoticeSE(), DX_PLAYTYPE_BACK);	// SE��炷
		m_noticeDisPlayFrame = kNoticeDisPlayFrame;
	}
}


/// <summary>
/// ���Ԍo�߂̒ʒm��\��
/// </summary>
void ScenePlaying::DrawNotice()
{
	int textPosX = static_cast<int>(m_noticePos.x);	// �e�L�X�g�̕\���ʒuX

	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime1)
	{
		if (m_time <= kNoticeTime1 + kNoticeStopFrame)
		{
			textPosX = kNoticeTimePosX;
			m_noticePos.x = kNoticeTimePosX;
		}
		else
		{
			textPosX = kNoticeTimePosX - static_cast<int>(m_noticePos.x);
		}
		DrawFormatStringToHandle(textPosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "20�b�o�߁I");
	}
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime2)
	{
		if (m_time <= kNoticeTime2 + kNoticeStopFrame)
		{
			textPosX = kNoticeTimePosX;
			m_noticePos.x = kNoticeTimePosX;
		}
		else
		{
			textPosX = kNoticeTimePosX - static_cast<int>(m_noticePos.x);
		}
		DrawFormatStringToHandle(textPosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "40�b�o�߁I");
	}
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime3)
	{
		if (m_time <= kNoticeTime3 + kNoticeStopFrame)
		{
			textPosX = kNoticeTimePosX;
			m_noticePos.x = kNoticeTimePosX;
		}
		else
		{
			textPosX = kNoticeTimePosX - static_cast<int>(m_noticePos.x);
		}
		DrawFormatStringToHandle(textPosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "60�b�o�߁I");
	}
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime4)
	{
		if (m_time <= kNoticeTime4 + kNoticeStopFrame)
		{
			textPosX = kNoticeTimePosX;
			m_noticePos.x = kNoticeTimePosX;
		}
		else
		{
			textPosX = kNoticeTimePosX - static_cast<int>(m_noticePos.x);
		}
		DrawFormatStringToHandle(textPosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "80�b�o�߁I");
	}
}
