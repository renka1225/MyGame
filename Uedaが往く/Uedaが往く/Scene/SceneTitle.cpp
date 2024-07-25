#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "SceneSelectStage.h"
#include "SceneTitle.h"
#include "Game.h"

// �萔
namespace
{
	const Vec2 kTitleLogoPos = { 950, 400 };
	const Vec2 kTitleBackPos = { 950,400 };
	constexpr float kTitleLogoScale = 0.5f;
	constexpr int kTitleTime = 10;			// �^�C�g����\������܂ł̎���
	constexpr int kTextTime = 60;			// �e�L�X�g��\������܂ł̎���
	constexpr int kTextDisplayTime = 100;	// �e�L�X�g��\������Ԋu
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle():
	m_titleTime(kTitleTime),
	m_textTime(kTextTime),
	m_textDisplayTime(0)
{
	m_titleLogo = LoadGraph("data/UI/title.png");
	m_titleLogoBack = LoadGraph("data/UI/titleBack.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogo);
	DeleteGraph(m_titleLogoBack);
}


/// <summary>
/// ������
/// </summary>
void SceneTitle::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <returns></returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	m_titleTime--;
	m_textTime--;
	m_textDisplayTime++;

	// �V�[���J��
	if (input.IsTriggered("OK"))
	{
		return std::make_shared<SceneSelectStage>();
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneTitle::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);
	// �^�C�g�����S�\��
	DrawRectRotaGraphF(kTitleBackPos.x, kTitleBackPos.y, 0, 0, Game::kScreenWidth, Game::kScreenHeight, kTitleLogoScale, 0.0f, m_titleLogoBack, true);
	if (m_titleTime < 0)
	{
		DrawRectRotaGraphF(kTitleLogoPos.x, kTitleLogoPos.y, 0, 0, Game::kScreenWidth, Game::kScreenHeight, kTitleLogoScale, 0.0f, m_titleLogo, true);
	}

	if (m_textTime < 0)
	{
		if (m_textDisplayTime % 180 >= kTextDisplayTime) return;
		DrawString(900, 800, "PRESS ANY BUTTON", 0x000000);
	}

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�^�C�g�����", 0xffffff);
#endif
}
