#include "ScenePlaying.h"
#include "SceneClear.h"
#include "ManagerModel.h"
#include "ManagerLight.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "ManagerResult.h"
#include "ConversionTime.h"
#include "Player.h"
#include "Camera.h"
#include "Background.h"
#include "Input.h"
#include "Game.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ScenePlaying::ScenePlaying() :
	m_nowCommand(A),
	m_startTime(kStartTime),
	m_clearStagingTime(kClearStagingTime),
	m_time(0),
	m_stopTime(0),
	m_pushCount(0),
	m_isPush(true),
	m_shadowMapHandle(-1),
	m_shadowMapMinPos(VGet(kShadowMapMinPosX, kShadowMapMinPosY, kShadowMapMinPosZ)),
	m_shadowMapMaxPos(VGet(kShadowMapMaxPosX, kShadowMapMaxPosY, kShadowMapMaxPosZ))
{
	m_pModel = std::make_shared<ManagerModel>();
	m_pLight = std::make_shared<ManagerLight>();
	m_pPlayer = std::make_shared<Player>(m_pModel);
	m_pCamera = std::make_shared<Camera>(m_pPlayer);
	m_pBackground = std::make_shared<Background>(m_pModel);

	m_startCount3 = LoadGraph("data/UI/3.png");
	m_startCount2 = LoadGraph("data/UI/2.png");
	m_startCount1 = LoadGraph("data/UI/1.png");

	m_fadeAlpha = kStartFadeAlpha;
	m_pLight->CreateDirLight();	// �f�B���N�V���i�����C�g���쐬
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ScenePlaying::~ScenePlaying()
{
	m_pLight->DeleteDirLight();

	// �V���h�E�}�b�v�̍폜
	DeleteShadowMap(m_shadowMapHandle);
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
	PlaySoundMem(m_pSound->GetCountSE(), DX_PLAYTYPE_BACK);	// �J�E���g�_�E��

	// �V���h�E�}�b�v�n���h�����쐬
	m_shadowMapHandle = MakeShadowMap(kMakeShadowMapSize, kMakeShadowMapSize);
	// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection(m_shadowMapHandle, VGet(kShadowMapLightDirX, kShadowMapLightDirY, kShadowMapLightDirZ));

	// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
	SetShadowMapDrawArea(m_shadowMapHandle, m_shadowMapMinPos, m_shadowMapMaxPos);
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���̓R�}���h</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	FadeOut();	// �t�F�[�h�A�E�g

	m_pModel->Update();			// ���f���X�V
	m_pBackground->Update();	// �w�i�X�V
	m_pCamera->Update();		// �J�����X�V
	m_pPlayer->Update(input);	// �v���C���[�X�V

	// �X�^�[�g���o���s��
	if (m_startTime > 0)
	{
		m_startTime--;
		return shared_from_this();
	}

	// �N���A���o��A�N���A��ʂɈړ�
	if (m_clearStagingTime < 0)
	{
		m_pResult->Save(m_time);	// �N���A�^�C����ۑ�
		FadeIn();	// �t�F�[�h�C��
		return std::make_shared<SceneClear>(m_time);
	}

	// �N���A������N���A���o���s��
	if (m_pushCount >= kMaxPush)
	{
		StopSoundMem(m_pSound->GetPlayBgm());
		ClearStaging();
		return shared_from_this();
	}

	// BGM��炷
	if (!CheckSoundMem(m_pSound->GetPlayBgm()))
	{
		PlaySoundMem(m_pSound->GetPlayBgm(), DX_PLAYTYPE_LOOP);
	}

	// �^�C���X�V
	m_time++;
	m_stopTime--;
	if (m_stopTime <= 0)
	{
		m_stopTime = 0;
		m_isPush = true;
	}

	// ���̓R�}���h���X�V
	UpdateCommand(input);

#ifdef _DEBUG
	// MEMO:�f�o�b�O�p
	if (input.IsTriggered("sceneChange"))
	{
		m_pushCount = kMaxPush;
	}
#endif

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePlaying::Draw()
{
	// �w�i�`��
	m_pBackground->Draw();

	// �V���h�E�}�b�v�ւ̕`��̏���
	ShadowMap_DrawSetup(m_shadowMapHandle);
	// ���f���`��
	m_pModel->Draw();
	// �v���C���[�`��
	m_pPlayer->Draw();
	// �V���h�E�}�b�v�ւ̕`����I��
	ShadowMap_DrawEnd();

	// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
	SetUseShadowMap(0, m_shadowMapHandle);
	// ���f���`��
	m_pModel->Draw();
	// �v���C���[�`��
	m_pPlayer->Draw();
	// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
	SetUseShadowMap(0, -1);

	m_pConversionTime->Change(m_time);	// �^�C���ϊ�
	// �����\��
	DrawFormatStringToHandle(kTimeEdgePosX, kTimeEdgePosY, 0x2e3b40, m_pFont->GetTimeFontEdge(),
		"%02d:%03d", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
	// �o�ߎ��ԕ\��
	DrawFormatStringToHandle(kTimePosX, kTimePosY, 0xffffff, m_pFont->GetTimeFont(),
		"%02d:%03d", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

#ifdef _DEBUG
	// MEMO:XYZ���f�o�b�N�\��
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0.0f, 0), VGet(lineSize, 0.0f, 0.0f), 0xff0000);
	DrawLine3D(VGet(0.0f, -lineSize, 0.0f), VGet(0.0f, lineSize, 0.0f), 0x00ff00);
	DrawLine3D(VGet(0.0f, 0.0f, -lineSize), VGet(0.0f, 0.0f, lineSize), 0x0000ff);

	// MEMO:��ʍ���ɃV���h�E�}�b�v���e�X�g�`��
	TestDrawShadowMap(m_shadowMapHandle, 0, 0, 320, 240);

	// MEMO:�f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�v���C���");
	DrawFormatString(0, 20, 0xffffff, "���͉�:%d", m_pushCount);
#endif

	if (m_startTime > 0)
	{
		DrawFade();		// �t�F�[�h
		StartStaging();	// �X�^�[�g���o�̕\��
	}
	else if(m_pushCount < kMaxPush)
	{
		DrawCommand();	// ���̓R�}���h��\��
	}
}


/// <summary>
/// �X�^�[�g���o�̕\��
/// </summary>
void ScenePlaying::StartStaging()
{
	if (m_startTime >= kStartCount1)
	{
		DrawGraph(kStartCountPosX, kStartCountPosY, m_startCount3, true);
	}
	if (m_startTime < kStartCount1 && m_startTime >= kStartCount2)
	{
		DrawGraph(kStartCountPosX, kStartCountPosY, m_startCount2, true);
	}
	if (m_startTime <= kStartCount2 && m_startTime > kStartCount3)
	{
		DrawGraph(kStartCountPosX, kStartCountPosY, m_startCount1, true);
	}
}


/// <summary>
/// �N���A���o�̕\��
/// </summary>
void ScenePlaying::ClearStaging()
{
	m_clearStagingTime--;

	m_pPlayer->ClearStaging();	// �v���C���[�̉��o

	if (!CheckSoundMem(m_pSound->GetClearSE()) && m_clearStagingTime >= kClearSEChangeTime)
	{
		PlaySoundMem(m_pSound->GetClearSE(), DX_PLAYTYPE_BACK);
	}
	if (!CheckSoundMem(m_pSound->GetClearStagingBgm()) && m_clearStagingTime <= kClearSEChangeTime)
	{
		PlaySoundMem(m_pSound->GetClearStagingBgm(), DX_PLAYTYPE_BACK);
	}
}


/// <summary>
/// ���̓R�}���h�X�V
/// </summary>
void ScenePlaying::UpdateCommand(Input& input)
{
	if (m_nowCommand == A) // A�{�^�����������Ƃ�
	{
		if (input.IsTriggered("A") && m_isPush)
		{
			PushCorrect();
		}
		else if ((input.IsTriggered("B") || input.IsTriggered("X") || input.IsTriggered("Y")))
		{
			m_isPush = false;
		}
	}
	if (m_nowCommand == B) // B�{�^�����������Ƃ�
	{
		if (input.IsTriggered("B") && m_isPush)
		{
			PushCorrect();
		}
		else if ((input.IsTriggered("A") || input.IsTriggered("X") || input.IsTriggered("Y")))
		{
			m_isPush = false;
		}
	}
	if (m_nowCommand == X) // X�{�^�����������Ƃ�
	{
		if (input.IsTriggered("X") && m_isPush)
		{
			PushCorrect();
		}
		else if (input.IsTriggered("A") || input.IsTriggered("B") || input.IsTriggered("Y"))
		{
			m_isPush = false;
		}
	}
	if (m_nowCommand == Y) // Y�{�^�����������Ƃ�
	{
		if (input.IsTriggered("Y") && m_isPush)
		{
			PushCorrect();
		}
		else if((input.IsTriggered("A") || input.IsTriggered("B") || input.IsTriggered("X")))
		{
			m_isPush = false;
		}
	}

	// �{�^���������ԈႦ���ꍇ
	if (!m_isPush && m_stopTime <= 0)
	{
		m_stopTime = kStopTime;
		if (!CheckSoundMem(m_pSound->GetMissSE()))
		{
			PlaySoundMem(m_pSound->GetMissSE(), DX_PLAYTYPE_BACK);
		}
	}
}


/// <summary>
/// �������{�^�����������ۂ̏���
/// </summary>
void ScenePlaying::PushCorrect()
{
	PlaySoundMem(m_pSound->GetJumpSE(), DX_PLAYTYPE_BACK);
	m_pushCount++;
	m_stopTime = kNextCommandTime;
	m_pPlayer->Move();
	m_nowCommand = GetRand(Y);

	// �e�̈ʒu���X�V
	m_shadowMapMinPos = VAdd(m_shadowMapMinPos, VGet(0.0f, 0.0f, m_pPlayer->GetMove().z));
	m_shadowMapMaxPos = VAdd(m_shadowMapMaxPos, VGet(0.0f, 0.0f, m_pPlayer->GetMove().z));
	SetShadowMapDrawArea(m_shadowMapHandle, m_shadowMapMinPos, m_shadowMapMaxPos);
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