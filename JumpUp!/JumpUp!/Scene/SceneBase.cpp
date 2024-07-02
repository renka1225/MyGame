#include "DxLib.h"
#include "Game.h"
#include "SceneBase.h"

// �萔
namespace
{
	constexpr int kFadeColor = 0x5f9ea0; // �t�F�[�h�̐F
	constexpr int kMaxFade = 255;		 // �t�F�[�h�̍ő�l
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneBase::SceneBase():
	m_fadeAlpha(0)
{
}


/// <summary>
/// �t�F�[�h�C������
/// </summary>
void SceneBase::FadeIn()
{
	m_fadeAlpha = std::min(m_fadeAlpha, kMaxFade);
}


/// <summary>
/// �t�F�[�h�A�E�g����
/// </summary>
void SceneBase::FadeOut()
{
	m_fadeAlpha = std::max(0, m_fadeAlpha);
}


/// <summary>
/// �t�F�[�h�C���A�E�g�̕`��
/// </summary>
void SceneBase::DrawFade()
{
	// �t�F�[�h�C��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kFadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
