#include "SceneBase.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "ManagerResult.h"
#include "ConversionTime.h"
#include "Game.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneBase::SceneBase():
	m_fadeAlpha(0),
	m_soundPal(kStartSoundPal)
{
	m_pFont = std::make_shared<ManagerFont>();
	m_pSound = std::make_shared<ManagerSound>();
	m_pConversionTime = std::make_shared<ConversionTime>();

	m_frameHandle = LoadGraph("data/UI/frame.png");
	m_buttonHandle = LoadGraph("data/UI/button.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneBase::~SceneBase()
{
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_buttonHandle);
}


/// <summary>
/// �t�F�[�h�C��
/// </summary>
void SceneBase::FadeIn()
{
	m_fadeAlpha += kFadeFrame;
	if (m_fadeAlpha > kMaxFade)
	{
		m_fadeAlpha = kMaxFade;
	}
}


/// <summary>
/// �t�F�[�h�A�E�g
/// </summary>
void SceneBase::FadeOut()
{
	m_fadeAlpha -= kFadeFrame;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}
}


/// <summary>
/// �t�F�[�h�C���A�E�g�̕`��
/// </summary>
void SceneBase::DrawFade()
{
	// �t�F�[�h�C��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
