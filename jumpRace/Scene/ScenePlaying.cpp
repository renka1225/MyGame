#include "ScenePlaying.h"
#include "SceneClear.h"
#include "ManagerModel.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "ManagerResult.h"
#include "Player.h"
#include "Camera.h"
#include "Background.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ScenePlaying::ScenePlaying(): 
	m_nowCommand(A),
	m_startTime(kStartTime),
	m_time(0),
	m_stopTime(0),
	m_pushCount(0)
{
	m_pModel = std::make_shared<ManagerModel>();
	m_pPlayer = std::make_shared<Player>(m_pModel);
	m_pCamera = std::make_shared<Camera>(m_pPlayer);
	m_pBackground = std::make_shared<Background>(m_pModel);

	m_fadeAlpha = kStartFadeAlpha;
}


/// <summary>
/// ������
/// </summary>
void ScenePlaying::Init(std::shared_ptr<ManagerResult> pResult)
{
	m_pResult = pResult;
	m_pBackground->Init();
	m_pResult->Load();
	m_nowCommand = GetRand(Y);
	//PlaySoundMem(m_pSound->GetCountSE(), DX_PLAYTYPE_BACK);	// �J�E���g�_�E��
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">�{�^������</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	FadeOut();		// �t�F�[�h�A�E�g

	m_pModel->Update();			// ���f���X�V
	m_pBackground->Update();	// �w�i�X�V
	m_pPlayer->Update(input);	// �v���C���[�X�V
	m_pCamera->Update();		// �J�����X�V

	// �X�^�[�g���o���s��
	if (m_startTime > 0)
	{
		m_startTime--;
		return shared_from_this();
	}

	// �^�C���X�V
	m_time++;
	m_stopTime--;
	if (m_stopTime < 0)
	{
		m_stopTime = 0;
	}

	// ���̓R�}���h���X�V
	UpdateCommand(input);

	// 50����͂ł�����N���A��ʂɑJ��
	if (m_pushCount >= kMaxPush)
	{
		m_pResult->Save(m_time);	// �N���A�^�C����ۑ�
		FadeIn();	// �t�F�[�h�C��
		return std::make_shared<SceneClear>(m_time);
	}

#ifdef _DEBUG
	// MEMO:�f�o�b�O�p
	if (input.IsTriggered("sceneChange"))
	{
		FadeIn();	// �t�F�[�h�C��
		return std::make_shared<SceneClear>(m_time);
	}
#endif

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePlaying::Draw()
{
	m_pBackground->Draw(); // �w�i�`��
	m_pModel->Draw();	   // ���f���`��

	// �o�ߎ��Ԃ̕`��
	int milliSec = m_time * 1000 / 60;
	int sec = (milliSec / 1000) % 90;
	milliSec %= 1000;
	DrawFormatStringToHandle(580, 80, 0xffffff, m_pFont->GetTimeFont(), "%02d:%03d", sec, milliSec);

#ifdef _DEBUG
	// MEMO:XYZ���f�o�b�N�\��
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0.0f, 0), VGet(lineSize, 0.0f, 0.0f), 0xff0000);
	DrawLine3D(VGet(0.0f, -lineSize, 0.0f), VGet(0.0f, lineSize, 0.0f), 0x00ff00);
	DrawLine3D(VGet(0.0f, 0.0f, -lineSize), VGet(0.0f, 0.0f, lineSize), 0x0000ff);

	// MEMO:�f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�v���C���");
	DrawFormatString(0, 20, 0xffffff, "���͉�:%d", m_pushCount);
#endif

	if (m_startTime > 0)
	{
		DrawFade();		// �t�F�[�h
		StartStaging();	// �X�^�[�g���o�̕\��
	}
	else
	{
		DrawCommand();	// ���̓R�}���h��\��
	}

	m_pPlayer->Draw();	// �v���C���[�̕`��
}


/// <summary>
/// �X�^�[�g���o�̕\��
/// </summary>
void ScenePlaying::StartStaging()
{
	if (m_startTime >= kStartCount1)
	{
		DrawFormatStringToHandle(kStartCountPosX, kStartCountPosY, 0xffffff, m_pFont->GetStartCountFont(), "3");
	}
	if (m_startTime < kStartCount1 && m_startTime >= kStartCount2)
	{
		DrawFormatStringToHandle(kStartCountPosX, kStartCountPosY, 0xffffff, m_pFont->GetStartCountFont(), "2");
	}
	if (m_startTime <= kStartCount2 && m_startTime > kStartCount3)
	{
		DrawFormatStringToHandle(kStartCountPosX, kStartCountPosY, 0xffffff, m_pFont->GetStartCountFont(), "1");
	}
}


/// <summary>
/// ���̓R�}���h�X�V
/// </summary>
void ScenePlaying::UpdateCommand(Input& input)
{
	if (m_nowCommand == A)
	{
		if (input.IsTriggered("A") && m_stopTime <= 0)
		{
			PlaySoundMem(m_pSound->GetJumpSE(), DX_PLAYTYPE_BACK);
			m_pushCount++;
			m_stopTime = kNextCommandTime;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
		else if (!input.IsTriggered("A") && (input.IsTriggered("B") || input.IsTriggered("X") || input.IsTriggered("Y")))
		{
			m_stopTime = kStopTime;
			if (!CheckSoundMem(m_pSound->GetJumpSE()) || !CheckSoundMem(m_pSound->GetMissSE()))
			{
				PlaySoundMem(m_pSound->GetMissSE(), DX_PLAYTYPE_BACK);
			}
		}
	}
	if (m_nowCommand == B)
	{
		if (input.IsTriggered("B") && m_stopTime <= 0)
		{
			PlaySoundMem(m_pSound->GetJumpSE(), DX_PLAYTYPE_BACK);
			m_pushCount++;
			m_stopTime = kNextCommandTime;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
		else if (!input.IsTriggered("B") && (input.IsTriggered("A") || input.IsTriggered("X") || input.IsTriggered("Y")))
		{
			m_stopTime = kStopTime;
			if (!CheckSoundMem(m_pSound->GetJumpSE()) || !CheckSoundMem(m_pSound->GetMissSE()))
			{
				PlaySoundMem(m_pSound->GetMissSE(), DX_PLAYTYPE_BACK);
			}
		}
	}
	if (m_nowCommand == X)
	{
		if (input.IsTriggered("X") && m_stopTime <= 0)
		{
			PlaySoundMem(m_pSound->GetJumpSE(), DX_PLAYTYPE_BACK);
			m_pushCount++;
			m_stopTime = kNextCommandTime;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
		else if (!input.IsTriggered("X"))
		{
			if (input.IsTriggered("A") || input.IsTriggered("B") || input.IsTriggered("Y"))
			{
				m_stopTime = kStopTime;
				if (!CheckSoundMem(m_pSound->GetJumpSE()) || !CheckSoundMem(m_pSound->GetMissSE()))
				{
					PlaySoundMem(m_pSound->GetMissSE(), DX_PLAYTYPE_BACK);
				}
			}
		}
	}
	if (m_nowCommand == Y)
	{
		if (input.IsTriggered("Y") && m_stopTime <= 0)
		{
			PlaySoundMem(m_pSound->GetJumpSE(), DX_PLAYTYPE_BACK);
			m_pushCount++;
			m_stopTime = kNextCommandTime;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
		else if(!input.IsTriggered("Y") && (input.IsTriggered("A") || input.IsTriggered("B") || input.IsTriggered("X")))
		{
			m_stopTime = kStopTime;
			if (!CheckSoundMem(m_pSound->GetJumpSE()) || !CheckSoundMem(m_pSound->GetMissSE()))
			{
				PlaySoundMem(m_pSound->GetMissSE(), DX_PLAYTYPE_BACK);
			}
		}
	}
}


/// <summary>
/// ���̓R�}���h��\��
/// </summary>
void ScenePlaying::DrawCommand()
{
	int srcX = 0;	// �摜�̐؂�o���ʒuX
	int srcY = 0;	// �摜�̐؂�o���ʒuY

	if (m_nowCommand == A)
	{
		srcY = kCommandSize * A;
		DrawRectRotaGraph(kCommandPosX, kCommandPosY, srcX, srcY, kCommandSize, kCommandSize, kCommandScale, 0.0f, m_buttonHandle, true);
	}
	if (m_nowCommand == B)
	{
		srcY = kCommandSize * B;
		DrawRectRotaGraph(kCommandPosX, kCommandPosY, srcX, srcY, kCommandSize, kCommandSize, kCommandScale, 0.0f, m_buttonHandle, true);
	}
	if (m_nowCommand == X)
	{
		srcY = kCommandSize * X;
		DrawRectRotaGraph(kCommandPosX, kCommandPosY, srcX, srcY, kCommandSize, kCommandSize, kCommandScale, 0.0f, m_buttonHandle, true);
	}
	if (m_nowCommand == Y)
	{
		srcY = kCommandSize * Y;
		DrawRectRotaGraph(kCommandPosX, kCommandPosY, srcX, srcY, kCommandSize, kCommandSize, kCommandScale, 0.0f, m_buttonHandle, true);
	}
}