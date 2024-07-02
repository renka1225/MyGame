#include "DxLib.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Font.h"
#include "Sound.h"
#include "ConversionTime.h"
#include "Game.h"
#include "Input.h"

// �萔
namespace
{
	/*�t�F�[�h*/
	constexpr int kFadeFrame = 5;			// �t�F�[�h�ω���
	constexpr int kStartFadeAlpha = 200;	// �X�^�[�g���̃t�F�[�h���l

	/*UI�\��*/
	constexpr int kClearPosX = 570;			// �N���A�̕����ʒuX
	constexpr int kClearPosY = 130;			// �N���A�̕����ʒuY
	constexpr int kFramePosX = 760;			// �g�\���ʒuX
	constexpr int kFramePosY = 600;			// �g�\���ʒuY
	constexpr int kSelectMove = 200;		// �I��\���̈ړ���
	constexpr float kFrameAnim = 0.05f;		// �g�̊g��k���A�j���[�V�����Đ�����
	constexpr float kFrameScale = 1.0f;		// ���̘g�̃T�C�Y
	constexpr float kFrameChange = 0.1f;	// �g�̃T�C�Y�̕ω���

	/*�e�L�X�g*/
	constexpr int kTextColor = 0x000000;	// �e�L�X�g�̐F
	constexpr int kTimePosX = 750;			// �^�C���\���ʒuX
	constexpr int kTimePosY = 450;			// �^�C���\���ʒuY
	constexpr int kStartPosX = 820;			// "����1��v���C"�ʒuX
	constexpr int kStartPosY = 640;			// "����1��v���C"�ʒuY
	constexpr int kTitlePosX = 790;			// "�^�C�g���ɖ߂�"�\���ʒuX
	constexpr int kTitlePosY = 840;			// "�^�C�g���ɖ߂�"�\���ʒuY

	/*�w�i*/
	constexpr int kBgColor = 0x2d6676;		// �w�i�F
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneClear::SceneClear():
	m_select(Select::kStart),
	m_clearTime(0),
	m_frameAnimTime(0.0f)
{
	m_fadeAlpha = kStartFadeAlpha;
	m_clearHandle = LoadGraph("data/UI/clear.png");
	m_frameHandle = LoadGraph("data/UI/frame.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneClear::~SceneClear()
{
	StopSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kClearBGM)]);
	DeleteGraph(m_clearHandle);
	DeleteGraph(m_frameHandle);
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
/// <param name="input">����</param>
/// <returns>�J�ڐ�̃V�[��</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	FadeOut(); // �t�F�[�h�A�E�g

	// BGM��炷
	if (!CheckSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kClearBGM)]))
	{
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kClearBGM)], DX_PLAYTYPE_LOOP);
	}

	m_frameAnimTime += kFrameAnim;

	// �I����Ԃ��X�V
	UpdateSelect(input);

	// �V�[���؂�ւ�
	if (input.IsTriggered("OK"))
	{
		FadeIn();	// �t�F�[�h�C��
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kSelectSE)], DX_PLAYTYPE_BACK); // SE��炷

		if (m_select == Select::kStart)
		{
			return std::make_shared<ScenePlaying>(); // �Q�[���V�[���Ɉړ�
		}
		else if (m_select == Select::kTitle)
		{
			return std::make_shared<SceneTitle>();	// �^�C�g����ʂɈړ�
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneClear::Draw()
{
	// �w�i�\��
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBgColor, true);

	// �N���A�̕����\��
	DrawGraph(kClearPosX, kClearPosY, m_clearHandle, true);

	// �N���A�^�C�����t���[��������b���ɕϊ�
	int min = Conversion::ChangeMin(m_clearTime);
	int sec = Conversion::ChangeSec(m_clearTime);
	int milliSec = Conversion::ChangeMilliSec(m_clearTime);

	// �N���A�^�C���\��
	DrawFormatStringToHandle(kTimePosX, kTimePosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearMenu)],
		"�N���A���� %02d:%02d:%03d", min, sec, milliSec);

	// �g�\��
	for (int i = 0; i < kSelectNum; i++)
	{
		// �I�𒆂̃{�^�����g��k��������
		if (m_select == i)
		{
			// �g�̃T�C�Y��1.0�`1.1�ŕω�������
			float scale = kFrameScale + kFrameChange * sin(m_frameAnimTime);

			int width, height;
			int size = GetGraphSize(m_frameHandle, &width, &height);
			int scaleWidth = static_cast<int>(width * scale);
			int scaleHeight = static_cast<int>(height * scale);

			DrawExtendGraph(
				kFramePosX - static_cast<int>((scaleWidth - width) * 0.5f),
				kFramePosY + kSelectMove * i - static_cast<int>((scaleHeight - height) * 0.5f),
				kFramePosX + static_cast<int>((scaleWidth - width) * 0.5f) + width,
				kFramePosY + static_cast<int>(kSelectMove * i + (scaleHeight - height) * 0.5f) + height,
				m_frameHandle, true);
		}
		else
		{
			DrawGraph(kFramePosX, kFramePosY + kSelectMove * i, m_frameHandle, true);
		}
	}

	// �����\��
	DrawStringToHandle(kStartPosX, kStartPosY, "����1��v���C",
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearMenu)]);
	DrawStringToHandle(kTitlePosX, kTitlePosY, "�^�C�g���ɂ��ǂ�",
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearMenu)]);

	// �t�F�[�h�C���A�E�g�`��
	DrawFade();

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�N���A���", 0xffffff);
	// �N���A�^�C��
	DrawFormatString(0, 40, 0xffffff, "�N���A�^�C��:%d", m_clearTime);
	// ���S��
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0xffffff);
#endif
}


/// <summary>
/// �t�F�[�h�C������
/// </summary>
void SceneClear::FadeIn()
{
	m_fadeAlpha += kFadeFrame;
}


/// <summary>
/// �t�F�[�h�A�E�g����
/// </summary>
void SceneClear::FadeOut()
{
	m_fadeAlpha -= kFadeFrame;
}


/// <summary>
/// �I����Ԃ��X�V
/// </summary>
/// <param name="input">����</param>
void SceneClear::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kCursorSE)], DX_PLAYTYPE_BACK); // SE��炷
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1������
	}
	if (input.IsTriggered("up"))
	{
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kCursorSE)], DX_PLAYTYPE_BACK); // SE��炷
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;	// �I����Ԃ�1�グ��
	}
}
