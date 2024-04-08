#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "ManagerFont.h"
#include "Game.h"
#include "DxLib.h"

SceneTitle::SceneTitle():
	m_textFrame(0),
	m_fadeAlpha(0)
{
	m_titleLogo = LoadGraph("data/title_test.png");
}


SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogo);
}


/// <summary>
/// ������
/// </summary>
void SceneTitle::Init()
{
	// �����Ȃ�
}


/// <summary>
///	�X�V
/// </summary>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	m_textFrame++;

	// �v���C��ʂɑJ��
	if (input.IsTriggered("OK"))
	{
		// �t�F�[�h�C��
		m_fadeAlpha += kFadeFrame;
		if (m_fadeAlpha > kMaxFade)
		{
			m_fadeAlpha = kMaxFade;
		}

		return std::make_shared<ScenePlaying>();
	}
	// �Q�[���I��
	if (input.IsTriggered("end"))
	{
		DxLib_End();
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneTitle::Draw()
{
	// �^�C�g�����S�\��
	DrawGraph(0, 0, m_titleLogo, false);

#if _DEBUG
	// MEMO:�f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�^�C�g�����");
	// MEMO:���S��
	//DrawLine(Game::kScreenWidth * 0.5f, 0, Game::kScreenWidth * 0.5f, Game::kScreenHeight, 0x0000000, 1);
#endif

	// �e�L�X�g�\��
	if (m_textFrame % 60 >= 30) return;
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "�͂��߂�");
	DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "�����");

	// �t�F�[�h�C��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x126662, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}