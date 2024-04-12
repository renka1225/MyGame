#include "SceneClear.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "ManagerFont.h"
#include "Game.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneClear::SceneClear():
	m_textFrame(0),
	m_fadeAlpha(kStartFadeAlpha),
	m_select(kStart)
{
	m_clearText = LoadGraph("data/UI/clear.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneClear::~SceneClear()
{
	DeleteGraph(m_clearText);
}


/// <summary>
/// ������
/// </summary>
void SceneClear::Init()
{
	// �����Ȃ�
}


/// <summary>
/// �X�V
/// </summary>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	// �t�F�[�h�A�E�g
	m_fadeAlpha -= kFadeFrame;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	m_textFrame++;	// �����_��

	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;					// �I����Ԃ�1������
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum; 	// �I����Ԃ�1�グ��
	}

	//�@��ʑJ��
	if (input.IsTriggered("OK"))
	{
		// �t�F�[�h�C��
		m_fadeAlpha += kFadeFrame;
		if (m_fadeAlpha > kMaxFade)
		{
			m_fadeAlpha = kMaxFade;
		}

		if(m_select == kStart)
		{
			return std::make_shared<ScenePlaying>();	// �Q�[���V�[���Ɉړ�
		}
		else if (m_select == kTitle)
		{
			return std::make_shared<SceneTitle>();		// �^�C�g����ʂɈړ�
		}
	}
	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneClear::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x17949B, true);	// �w�i
	DrawGraph(kClearTextPosX, kClearTextPosY, m_clearText, true);			// CLEAR�̕���

#if _DEBUG
	// MEMO:�f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�N���A���");
	// MEMO:���S��
	DrawLine(Game::kScreenWidth * 0.5f, 0, Game::kScreenWidth * 0.5f, Game::kScreenHeight, 0x0000000, 1);
#endif

	// �I�𒆂̃e�L�X�g��_�ł�����
	if (m_select == kStart)
	{
		DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "�^�C�g���ɂ��ǂ�");
		if (m_textFrame % 60 >= 30) return;
		DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "����1��V��");
	}
	else if (m_select == kTitle)
	{
		DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "����1��V��");
		if (m_textFrame % 60 >= 30) return;
		DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "�^�C�g���ɂ��ǂ�");
	}

	// �t�F�[�h�C���A�E�g
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x126662, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}