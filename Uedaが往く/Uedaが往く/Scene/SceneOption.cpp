#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "Sound.h"
#include "Font.h"
#include "Game.h"
#include "UI.h"
#include "SceneOption.h"

// �萔
namespace
{
	constexpr int kBackBoxColor = 0x494949;				 // �l�p�̐F
	const Vec2 kBackBoxPos = { 712, 115 };				 // �w�i�̎l�p�̕\���ʒu
	constexpr float kBackBoxWidth = 1070;				 // �w�i�̎l�p�̕�
	constexpr float kBackBoxHeight = 800;				 // �w�i�̎l�p�̍���

	constexpr int kTextColor = 0xffffff;				 // �e�L�X�g�̐F
	const Vec2 kSelectTextPos = { 200, 300 };			 // �I���e�L�X�g�\���ʒu
	constexpr float kSelectTextInterval = 120.0f;		 // �I���e�L�X�g�\���Ԋu
	const Vec2 kAfterSelectTextPos = { 800, 310 };		 // �I����e�L�X�g�\���ʒu
	const Vec2 kCursorPos = { 140, 290 };				 // �J�[�\���\���ʒu
	const Vec2 kAfterSelectCursorPos = { 780, 300 };	 // �I����J�[�\���\���ʒu

	// �T�E���h�֌W
	const Vec2 kSoundNumText = { 1650, 320 };			 // ���ʃe�L�X�g�\���ʒu
	const Vec2 kSoundBarPos = { 950, 330 };				 // ���ʃo�[�w�i�\���ʒu
	const Vec2 kCurrentSoundBarPos = { 954, 333 };		 // ���݂̉��ʃo�[����ʒu
	constexpr float kCurrentSoundBarWidth = 650;		 // ���݂̉��ʃo�[�̍ő剡��
	constexpr float kCurrentSoundBarHeight = 23;		 // ���݂̉��ʃo�[�̍���
	constexpr int kCurrentSoundBarColor = 0xcf2223;		 // ���݂̉��ʃo�[�̐F
	const Vec2 kSoundKnobPos = { 1600, 315 };			 // �܂ݏ����\���ʒu
	constexpr float kSoundKnobMinPosX = 950.0f;			 // �܂ݍŏ��\���ʒuX

	// �摜�̎��
	enum class Handle
	{
		kSoundBar,
		kSoundKnob,
		kHandleNum,
	};
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneOption::SceneOption(std::shared_ptr<SceneBase> pScene) :
	m_pPrevScene(pScene),
	m_afterSelect(SelectSound::kBGM),
	m_isSound(false),
	m_isKeyConfig(false)
{
	m_handle.resize(static_cast<int>(Handle::kHandleNum));
	m_handle[static_cast<int>(Handle::kSoundBar)] = LoadGraph("data/UI/soundBar.png");
	m_handle[static_cast<int>(Handle::kSoundKnob)] = LoadGraph("data/UI/soundKnob.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneOption::~SceneOption()
{
	for (auto& handle : m_handle)
	{
		DeleteGraph(handle);
	}
}


/// <summary>
/// ������
/// </summary>
void SceneOption::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input"></param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneOption::Update(Input& input)
{
	//�I����ԍX�V
	if (m_isSound)
	{
		// �T�E���h�X�V
		UpdateSound(input);
	}
	else if (m_isKeyConfig)
	{
		UpdateSelect(input, SelectKeyConfig::kSelectKeyNum);
	}
	else
	{
		UpdateSelect(input, Select::kSelectNum);
	}

	m_pUI->Update();

	if (input.IsTriggered("back"))
	{
		if (m_isSound || m_isKeyConfig)
		{
			m_isSound = false;
			m_isKeyConfig = false;
		}
		else
		{
			return m_pPrevScene;	// �O�̉�ʂɂ��ǂ�
		}
	}
	if (input.IsTriggered("OK"))
	{
		if (m_select == Select::kSound)
		{
			m_isSound = true;
			m_isKeyConfig = false;
			m_afterSelect = SelectSound::kBGM;
		}
		else if (m_select == Select::kKeyConfig)
		{
			m_isSound = false;
			m_isKeyConfig = true;
			m_afterSelect = SelectKeyConfig::kXButton;
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneOption::Draw()
{
	// �w�i�`��
	m_pUI->DrawMenuBg();
	DrawBox(kBackBoxPos.x, kBackBoxPos.y, kBackBoxPos.x + kBackBoxWidth, kBackBoxPos.y + kBackBoxHeight, kBackBoxColor, true);

	// �J�[�\���\��
	if (!m_isSound && !m_isKeyConfig)
	{
		m_pUI->DrawCursor(kCursorPos, m_select, kSelectTextInterval);
	}
	else
	{
		m_pUI->DrawCursor(kAfterSelectCursorPos, m_afterSelect, kSelectTextInterval, true);
	}

	// �T�E���h�֘A�\��
	if (m_select == Select::kSound)
	{
		DrawSound();
	}
	// �L�[�R���t�B�O�֘A�\��
	else if (m_select == Select::kKeyConfig)
	{
		DrawKeyConfig();
	}

	// �e�L�X�g�\��
	DrawStringFToHandle(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kSound,
		"�T�E���h", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
	DrawStringFToHandle(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kKeyConfig,
		"�{�^���z�u", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�I�v�V�������", 0xffffff);
#endif
}


/// <summary>
/// �T�E���h�X�V
/// </summary>
/// <param name="input">���͏��</param>
void SceneOption::UpdateSound(Input& input)
{
	// �I����Ԃ�1������
	if (input.IsTriggered("down"))
	{
		m_afterSelect = (m_afterSelect + 1) % SelectSound::kSelectSoundNum;
		m_pUI->Init();
		PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kCursor)], DX_PLAYTYPE_BACK);
	}
	// �I����Ԃ�1�グ��
	if (input.IsTriggered("up"))
	{
		m_afterSelect = (m_afterSelect + (SelectSound::kSelectSoundNum - 1)) % SelectSound::kSelectSoundNum;
		m_pUI->Init();
		PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kCursor)], DX_PLAYTYPE_BACK);
	}

	// BGM�I�𒆂̏ꍇ
	if (m_afterSelect == SelectSound::kBGM)
	{
		Sound::ChangeBgmVol(input);
	}
	// SE�I�𒆂̏ꍇ
	if (m_afterSelect == SelectSound::kSE)
	{
		Sound::ChangeSeVol(input);
	}
}


/// <summary>
/// �L�[�X�V
/// </summary>
/// <param name="input">���͏��</param>
void SceneOption::UpdateKeyConfig(Input& input)
{
}


/// <summary>
/// �T�E���h�����\��
/// </summary>
void SceneOption::DrawSound()
{
	// �T�E���h�o�[�\��
	DrawGraphF(kSoundBarPos.x, kSoundBarPos.y + kSelectTextInterval * SelectSound::kBGM, m_handle[static_cast<int>(Handle::kSoundBar)], true);
	DrawGraphF(kSoundBarPos.x, kSoundBarPos.y + kSelectTextInterval * SelectSound::kSE, m_handle[static_cast<int>(Handle::kSoundBar)], true);

	// ���ʂɍ��킹�Ďl�p�̒������X�V����
	float bgmBarWidth = kCurrentSoundBarWidth * (Sound::GetBgmVol() / 100.0f);
	float seBarWidth = kCurrentSoundBarWidth * (Sound::GetSeVol() / 100.0f);
	DrawBox(kCurrentSoundBarPos.x, kCurrentSoundBarPos.y + kSelectTextInterval * SelectSound::kBGM,
		kCurrentSoundBarPos.x + bgmBarWidth, kCurrentSoundBarPos.y + kCurrentSoundBarHeight + kSelectTextInterval * SelectSound::kBGM,
		kCurrentSoundBarColor, true);
	DrawBox(kCurrentSoundBarPos.x, kCurrentSoundBarPos.y + kSelectTextInterval * SelectSound::kSE,
		kCurrentSoundBarPos.x + seBarWidth, kCurrentSoundBarPos.y + kCurrentSoundBarHeight + kSelectTextInterval * SelectSound::kSE,
		kCurrentSoundBarColor, true);

	// ���ʂɂ���Ă܂݂̈ʒu���X�V����
	float bgmKnobPosX = kSoundKnobMinPosX + (kSoundKnobPos.x - kSoundKnobMinPosX) * (Sound::GetBgmVol() / 100.0f);
	float seKnobPosX = kSoundKnobMinPosX + (kSoundKnobPos.x - kSoundKnobMinPosX) * (Sound::GetSeVol() / 100.0f);
	DrawGraphF(bgmKnobPosX, kSoundKnobPos.y + kSelectTextInterval * SelectSound::kBGM, m_handle[static_cast<int>(Handle::kSoundKnob)], true);
	DrawGraphF(seKnobPosX, kSoundKnobPos.y + kSelectTextInterval * SelectSound::kSE, m_handle[static_cast<int>(Handle::kSoundKnob)], true);

	// �e�L�X�g�\��
	DrawStringFToHandle(kAfterSelectTextPos.x, kAfterSelectTextPos.y + kSelectTextInterval * SelectSound::kBGM,
		"BGM", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
	DrawStringFToHandle(kAfterSelectTextPos.x, kAfterSelectTextPos.y + kSelectTextInterval * SelectSound::kSE,
		"SE", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
	DrawFormatStringFToHandle(kSoundNumText.x, kSoundNumText.y + kSelectTextInterval * SelectSound::kBGM,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)], "%d", Sound::GetBgmVol());
	DrawFormatStringFToHandle(kSoundNumText.x, kSoundNumText.y + kSelectTextInterval * SelectSound::kSE,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)], "%d", Sound::GetSeVol());

}


/// <summary>
/// �L�[�R���t�B�O�����\��
/// </summary>
void SceneOption::DrawKeyConfig()
{
}
