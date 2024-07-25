#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "SceneSelectStage.h"
#include "SceneTitle.h"
#include "Game.h"

// �萔
namespace
{
	const Vec2 kTitleLogoPos = { 950.0f, 400.0f };	// �^�C�g�����S�\���ʒu
	constexpr float kTitleLogoScale = 0.5f;			// �^�C�g�����S�̃T�C�Y
	const Vec2 kTextPos = { 500.0f, 800.0f };		// "PRESS ANY BUTTON"�̃e�L�X�g�ʒu
	constexpr int kTitleTime = 10;					// �^�C�g����\������܂ł̎���
	constexpr int kTextTime = 60;					// �e�L�X�g��\������܂ł̎���
	constexpr int kTextDisplayTime = 2;				// �e�L�X�g��\������Ԋu
	constexpr int kTextDisplayAnimTime = 240;		// �e�L�X�g�A�j���[�V�����̎���
	constexpr int kMaxAlpha = 255;					// �ő�A���t�@�l
	constexpr int kMinAlpha = 30;					// �ŏ��A���t�@�l
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle():
	m_titleTime(kTitleTime),
	m_textTime(kTextTime),
	m_textDisplayTime(0),
	m_textAlpha(0)
{
	m_titleLogo = LoadGraph("data/UI/title.png");
	m_titleLogoBack = LoadGraph("data/UI/titleBack.png");
	m_textHandle = LoadGraph("data/UI/PRESS.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogo);
	DeleteGraph(m_titleLogoBack);
	DeleteGraph(m_textHandle);
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
	m_textDisplayTime += kTextDisplayTime;

	// �e�L�X�g�̃A���t�@�l�𒲐�����
	m_textDisplayTime %= kTextDisplayAnimTime;
	// MEMO:sin�g���g����0�`1�͈̔͂ɂ���
	float sinAlpha = 0.5f + 0.5f * sinf(static_cast<float>(m_textDisplayTime) / kTextDisplayAnimTime * DX_PI_F);
	m_textAlpha = kMinAlpha + static_cast<int>((kMaxAlpha - kMinAlpha) * sinAlpha);

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
	// �w�i�`��
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);

	// �^�C�g�����S�\��
	DrawRectRotaGraphF(kTitleLogoPos.x, kTitleLogoPos.y, 0, 0, Game::kScreenWidth, Game::kScreenHeight, kTitleLogoScale, 0.0f, m_titleLogoBack, true);
	if (m_titleTime < 0)
	{
		DrawRectRotaGraphF(kTitleLogoPos.x, kTitleLogoPos.y, 0, 0, Game::kScreenWidth, Game::kScreenHeight, kTitleLogoScale, 0.0f, m_titleLogo, true);
	}

	// ������_�ł�����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_textAlpha);
	DrawGraph(kTextPos.x, kTextPos.y, m_textHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�^�C�g�����", 0xffffff);
#endif
}
