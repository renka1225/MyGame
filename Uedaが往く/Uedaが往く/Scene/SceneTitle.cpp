#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "Sound.h"
#include "SceneSelectStage.h"
#include "SceneTitle.h"
#include "Game.h"

// �萔
namespace
{
	const Vec2 kTitleLogoPos = { 950.0f, 400.0f };	// �^�C�g�����S�\���ʒu
	constexpr float kTitleLogoMinScale = 0.5f;		// �^�C�g�����S�̍ŏ��T�C�Y
	constexpr float kTitleLogoMaxScale = 10.0f;		// �^�C�g�����S�̍ő�T�C�Y
	constexpr float kTitleLogoChangeScale = 0.3f;	// �^�C�g�����S�̃T�C�Y�ω���
	const Vec2 kTextPos = { 500.0f, 880.0f };		// "PRESS ANY BUTTON"�̃e�L�X�g�ʒu
	constexpr int kTextDisplayTime = 2;				// �e�L�X�g��\������Ԋu
	constexpr int kTextDisplayAnimTime = 240;		// �e�L�X�g�A�j���[�V�����̎���
	constexpr int kMaxAlpha = 255;					// �ő�A���t�@�l
	constexpr int kMinAlpha = 30;					// �ŏ��A���t�@�l
	constexpr int kTitleTime = 60;					// �^�C�g����\������܂ł̎���
	constexpr int kTextTime = 120;					// �e�L�X�g��\������܂ł̎���
	constexpr int kBGMTime = 150;					// BGM���Đ����͂��߂鎞��
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle():
	m_time(0),
	m_textDisplayTime(0),
	m_titleLogoScale(kTitleLogoMaxScale),
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
	StopSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kTitleBGM)]);
	DeleteGraph(m_titleLogo);
	DeleteGraph(m_titleLogoBack);
	DeleteGraph(m_textHandle);
}


/// <summary>
/// ������
/// </summary>
void SceneTitle::Init()
{
	// �����Ȃ�
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	m_time++;

	UpdateDisplay(); // �e�L�X�g�̕\�����X�V����

	// �^�C�g�����S�\����BGM��炷
	if (m_time > kBGMTime)
	{
		if (!CheckSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kTitleBGM)]))
		{
			PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kTitleBGM)], DX_PLAYTYPE_LOOP);
		}
	}

	// �V�[���J��
	if (input.IsTriggered("OK"))
	{
		return std::make_shared<SceneSelectStage>(); // �X�e�[�W�I���֑J��
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
	DrawRectRotaGraphF(kTitleLogoPos.x, kTitleLogoPos.y, 0, 0, Game::kScreenWidth, Game::kScreenHeight, m_titleLogoScale, 0.0f, m_titleLogoBack, true);
	if (m_time > kTitleTime)
	{
		DrawRectRotaGraphF(kTitleLogoPos.x, kTitleLogoPos.y, 0, 0, Game::kScreenWidth, Game::kScreenHeight, m_titleLogoScale, 0.0f, m_titleLogo, true);
	}

	// "PRESSANYBUTTON"�\��
	if (m_time > kTextTime)
	{
		// ������_�ł�����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_textAlpha);
		DrawGraphF(kTextPos.x, kTextPos.y, m_textHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�^�C�g�����", 0xffffff);
#endif
}


/// <summary>
/// �e�L�X�g�̕\�����X�V����
/// </summary>
void SceneTitle::UpdateDisplay()
{
	// �e�L�X�g�̃A���t�@�l�𒲐�����
	m_textDisplayTime += kTextDisplayTime;
	m_textDisplayTime %= kTextDisplayAnimTime;
	// MEMO:sin�g���g����0�`1�͈̔͂ɂ���
	float sinAlpha = 0.5f + 0.5f * sinf(static_cast<float>(m_textDisplayTime) / kTextDisplayAnimTime * DX_PI_F);
	m_textAlpha = kMinAlpha + static_cast<int>((kMaxAlpha - kMinAlpha) * sinAlpha);

	// �^�C�g�����S�̃T�C�Y�����񂾂񏬂�������
	m_titleLogoScale -= kTitleLogoChangeScale;
	m_titleLogoScale = std::max(kTitleLogoMinScale, m_titleLogoScale);
}
