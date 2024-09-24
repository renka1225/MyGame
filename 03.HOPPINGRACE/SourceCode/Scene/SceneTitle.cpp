#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "SceneResult.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle():
	m_select(kStart)
{
	m_titleLogo = LoadGraph("data/UI/title.png");
	m_playMovie = LoadGraph("data/play.mp4");
	SetMovieVolumeToGraph(0, m_playMovie);
	m_fadeAlpha = kStartFadeAlpha;
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogo);
	DeleteGraph(m_playMovie);
}


/// <summary>
/// ������
/// </summary>
void SceneTitle::Init(std::shared_ptr<ManagerResult> pResult)
{
	m_pResult = pResult;
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">�{�^������</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	FadeOut();	// �t�F�[�h�A�E�g
	UpdateSelect(input);	// �I����ԍX�V

	// �w�i�Ńv���C������Đ�����
	if (GetMovieStateToGraph(m_playMovie) != 1)
	{
		PlayMovieToGraph(m_playMovie);
	}

	// BGM�̉��ʒ���
	m_soundPal += kSoundPal;
	if (m_soundPal >= kMaxSoundPal)
	{
		m_soundPal = kMaxSoundPal;
	}
	ChangeVolumeSoundMem(m_soundPal, m_pSound->GetTitleBgm());
	if (!CheckSoundMem(m_pSound->GetTitleBgm()))
	{
		PlaySoundMem(m_pSound->GetTitleBgm(), DX_PLAYTYPE_LOOP);
	}

	if (input.IsTriggered("OK"))
	{
		FadeIn();	// �t�F�[�h�C��
		PlaySoundMem(m_pSound->GetSelectSE(), DX_PLAYTYPE_BACK);

		// ��ʐ؂�ւ�
		if (m_select == kStart)
		{
			return std::make_shared<ScenePlaying>(); // �Q�[���V�[���Ɉړ�
		}
		else if (m_select == kResult)
		{
			return std::make_shared<SceneResult>();	 // ���ʊm�F��ʂɈړ�
		}
		else if (m_select == kEnd)
		{
			DxLib_End(); // �Q�[���I��
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneTitle::Draw()
{
	// �v���C�����`��
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_playMovie, false);
	// �w�i�ɍ����l�p�𔖂��\������
	SetDrawBlendMode(DX_BLENDMODE_MULA, 150);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �N���W�b�g�\�L
	DrawFormatStringToHandle(kCreditPosX, kCreditPosY, 0xffffff, m_pFont->GetCreditFont(), "Sound/OtoLogic");
	DrawFormatStringToHandle(kCreditPosX, kCreditPos2Y, 0xffffff, m_pFont->GetCreditFont(), "���p�\�t�g/VOICEVOX:�i�[�X���{�Q�^�C�v�s");

	// �^�C�g�����S�\��
	DrawGraph(kTitleLogoPosX, kTitleLogoPosY, m_titleLogo, true);

	DrawSelect();	// �I�����ڂ�\��

	DrawFade();		// �t�F�[�h�C��

#ifdef _DEBUG
	// �f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�^�C�g�����");
	// ���S��
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0xfffff);
#endif
}


/// <summary>
/// �I����Ԃ̍X�V
/// </summary>
void SceneTitle::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		PlaySoundMem(m_pSound->GetCursorSE(), DX_PLAYTYPE_BACK);
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1������
	}
	if (input.IsTriggered("up"))
	{
		PlaySoundMem(m_pSound->GetCursorSE(), DX_PLAYTYPE_BACK);
		m_select = (m_select + 2) % kSelectNum;	// �I����Ԃ�1�グ��
	}
}


/// <summary>
/// �I�����ڂ�\��
/// </summary>
void SceneTitle::DrawSelect()
{
	// �I�𒆂̍��ڂɐF������
	DrawBox(kNowSelectPosX, kNowSelectPosY + kSelectMove * m_select,
		kNowSelectPosX + kNowSelectWidth, kNowSelectPosY + kSelectMove * m_select + kNowSelectHeight,
		0x4289A3, true);

	// �g�\��
	for (int i = 0; i < kSelectNum; i++)
	{
		DrawGraph(kFramePosX, kFramePosY + kSelectMove * i, m_frameHandle, true);
	}

	// �e�L�X�g�\��
	DrawFormatStringToHandle(kStartTextPosX, kStartTextPosY, 0xffffff, m_pFont->GetTextFont(), "�X�^�[�g");
	DrawFormatStringToHandle(kResultTextPosX, kResultTextPosY, 0xffffff, m_pFont->GetTextFont(), "�����L���O");
	DrawFormatStringToHandle(kEndTextPosX, kEndTextPosY, 0xffffff, m_pFont->GetTextFont(), "�����");
}