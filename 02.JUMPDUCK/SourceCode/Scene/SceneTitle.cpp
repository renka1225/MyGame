#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "Game.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle():
	m_textFrame(0),
	m_fadeAlpha(0),
	m_select(kStart)
{
	m_titleLogo = LoadGraph("data/UI/titleLogo.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogo);
}


/// <summary>
///	�X�V
/// </summary>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	if (!CheckSoundMem(m_pSound->GetTitleBgm()))
	{
		PlaySoundMem(m_pSound->GetTitleBgm(), DX_PLAYTYPE_BACK);	// BGM��炷
	}

	m_textFrame++;

	if (input.IsTriggered("down"))
	{
		PlaySoundMem(m_pSound->GetSelectSE(), DX_PLAYTYPE_BACK);	// SE��炷
		m_select = (m_select + 1) % kSelectNum;						// �I����Ԃ�1������
		if (m_cursorPosY == kTextPosY)
		{
			m_cursorPosY = kText2PosY;
		}
		else
		{
			m_cursorPosY = kTextPosY;
		}
		
	}
	if(input.IsTriggered("up"))
	{
		PlaySoundMem(m_pSound->GetSelectSE(), DX_PLAYTYPE_BACK);	// SE��炷
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;		// �I����Ԃ�1�グ��
		if (m_cursorPosY == kTextPosY)
		{
			m_cursorPosY = kText2PosY;
		}
		else
		{
			m_cursorPosY = kTextPosY;
		}
	}

	// �V�[���J��
	if (input.IsTriggered("OK"))
	{
		PlaySoundMem(m_pSound->GetDetermineSE(), DX_PLAYTYPE_BACK);	// SE��炷
		// �t�F�[�h�C��
		m_fadeAlpha += kFadeFrame;
		if (m_fadeAlpha > kMaxFade)
		{
			m_fadeAlpha = kMaxFade;
		}

		if (m_select == kStart)
		{
			return std::make_shared<ScenePlaying>();	// �Q�[���V�[���Ɉړ�
		}
		else if (m_select == kEnd)
		{
			DxLib_End();	// �Q�[���I��
		}
	}
	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneTitle::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x17949B, true);		// �w�i�\��
	DrawGraph(kLogoPosX, kLogoPosY, m_titleLogo, true);							// �^�C�g�����S�\��
	DrawGraph(kCursorPosX, m_cursorPosY, m_cursorHandle, true);					// �J�[�\���\��

	DrawFormatStringToHandle(kCreditTextPosX, kCreditTextPosX, 0xffffff, m_pFont->GetCreditFont(), "Sound:OtoLogic");	// �N���W�b�g�\��

#if _DEBUG
	// MEMO:�f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�^�C�g�����");
	// MEMO:���S��
	//DrawLine(Game::kScreenWidth * 0.5f, 0, Game::kScreenWidth * 0.5f, Game::kScreenHeight, 0x0000000, 1);
#endif

	// �I�𒆂̃e�L�X�g��_�ł�����
	if (m_select == kStart)
	{
		DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "�����");
		if (m_textFrame % 60 >= kTextFrame) return;
		DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "�͂��߂�");
	}
	else if (m_select == kEnd)
	{
		DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "�͂��߂�");
		if (m_textFrame % 60 >= kTextFrame) return;
		DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "�����");
	}

	// �t�F�[�h�C��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x126662, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}