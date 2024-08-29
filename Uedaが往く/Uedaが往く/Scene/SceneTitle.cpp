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
	constexpr float kTitleLogoInitRot = 360.0f;		// �J�n���̃^�C�g�����S�̉�]��
	constexpr float kTitleLogoChangeRot = 20.0f;	// �^�C�g�����S�̉�]���ω���
	const Vec2 kTextPos = { 500.0f, 780.0f };		// "PRESS ANY BUTTON"�̃e�L�X�g�ʒu
	constexpr int kTextDisplayTime = 2;				// �e�L�X�g��\������Ԋu
	constexpr int kTextDisplayAnimTime = 240;		// �e�L�X�g�A�j���[�V�����̎���
	constexpr int kMaxAlpha = 255;					// �ő�A���t�@�l
	constexpr int kMinAlpha = 30;					// �ŏ��A���t�@�l
	constexpr int kTitleTime = 60;					// �^�C�g����\������܂ł̎���
	constexpr int kTextTime = 120;					// �e�L�X�g��\������܂ł̎���
	constexpr int kBGMTime = 150;					// BGM���Đ����͂��߂鎞��
	
	constexpr int kStartFadeAlpha = 255;			// �X�^�[�g���̃t�F�[�h�l
	constexpr int kFadeFrame = 8;					// �t�F�[�h�ω���

	// OP����
	const char* kOpMovePath = "data/op.mp4";		// ����̃p�X��
	constexpr int kOpMoveTime = 65010;				// ����̍Đ�����
	constexpr int kOpMoveStartTime = 1800;			// ������Đ�����܂ł̎���
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle():
	m_time(0),
	m_textDisplayTime(0),
	m_titleLogoScale(kTitleLogoMaxScale),
	m_titleLogoRot(kTitleLogoInitRot),
	m_textAlpha(kMinAlpha),
	m_opStartTime(0)
{
	m_fadeAlpha = kStartFadeAlpha;
	m_titleLogo = LoadGraph("data/UI/title.png");
	m_titleLogoBack = LoadGraph("data/UI/titleBack.png");
	m_textHandle = LoadGraph("data/UI/PRESS.png");
	m_opMoveHandle = LoadGraph(kOpMovePath);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneTitle::~SceneTitle()
{
	StopSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kTitle)]);
	DeleteGraph(m_titleLogo);
	DeleteGraph(m_titleLogoBack);
	DeleteGraph(m_textHandle);
	DeleteGraph(m_opMoveHandle);
}


/// <summary>
/// ������
/// </summary>
void SceneTitle::Init()
{
	m_titleLogoScale = kTitleLogoMaxScale;
	m_titleLogoRot = kTitleLogoInitRot;
	m_time = 0;
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	FadeOut(kFadeFrame); // �t�F�[�h�A�E�g

	m_opStartTime--;	// op���Đ�����܂ł̎��Ԃ��X�V

	// ������Đ�����
	if (m_opStartTime == 0)
	{
		Init();
		StopSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kTitle)]);
	}
	else if (m_opStartTime < 0)
	{
		PlayMovieToGraph(m_opMoveHandle);

		// ���悪�I���������{�^�����������ꍇ�^�C�g���ɖ߂�
		const bool isMoveStop = TellMovieToGraph(m_opMoveHandle) >= kOpMoveTime || input.IsTriggered("A") || input.IsTriggered("B") || input.IsTriggered("X") || input.IsTriggered("Y");
		if (isMoveStop)
		{
			PauseMovieToGraph(m_opMoveHandle);
			SeekMovieToGraph(m_opMoveHandle, 0);
			m_opStartTime = kOpMoveStartTime;
		}

		return shared_from_this();
	}

	m_time++;		 // �o�ߎ��Ԃ��X�V
	UpdateDisplay(); // �e�L�X�g�̕\�����X�V����

	// �^�C�g�����S�\����BGM��炷
	if (m_time < kBGMTime)
	{
		if (!CheckSoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kTitleDisp)]))
		{
			PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kTitleDisp)], DX_PLAYTYPE_BACK);
		}
	}
	if (m_time > kBGMTime)
	{
		if (!CheckSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kTitle)]))
		{
			PlaySoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kTitle)], DX_PLAYTYPE_LOOP);
		}
	}

	// �V�[���J��
	if (input.IsTriggered("A") || input.IsTriggered("B") || input.IsTriggered("X") || input.IsTriggered("Y"))
	{
		FadeIn(kFadeFrame); // �t�F�[�h�C��
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
	DrawRectRotaGraphF(kTitleLogoPos.x, kTitleLogoPos.y, 0, 0, Game::kScreenWidth, Game::kScreenHeight, m_titleLogoScale, m_titleLogoRot, m_titleLogoBack, true);
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

	// �����\������
	if (m_opStartTime < 0)
	{
		DrawGraph(0, 0, m_opMoveHandle, true);
	}

	DrawFade();	// �t�F�[�h�C���A�E�g�`��

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�^�C�g�����", 0xffffff);
	DrawFormatString(0, 20, 0x0000ff, "����Đ��܂ł̎���:%d", m_opStartTime);
	DrawFormatString(0, 40, 0xff0000, "���݂̓��掞��:%d", TellMovieToGraph(m_opMoveHandle));
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

	// �^�C�g�����S����]������
	m_titleLogoRot -= kTitleLogoChangeRot;
	m_titleLogoRot = std::max(0.0f, m_titleLogoRot);
}
