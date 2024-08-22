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
	constexpr int kBackBoxColor = 0x494949;					 // �l�p�̐F
	const Vec2 kBackBoxPos = { 712.0f, 115.0f };			 // �w�i�̎l�p�̕\���ʒu
	constexpr float kBackBoxWidth = 1070;					 // �w�i�̎l�p�̕�
	constexpr float kBackBoxHeight = 800;					 // �w�i�̎l�p�̍���

	constexpr int kTextColor = 0xffffff;					 // �e�L�X�g�̐F
	const Vec2 kSelectTextPos = { 250.0f, 300.0f };			 // �I���e�L�X�g�\���ʒu
	constexpr float kSelectTextAdj = 30.0f;					 // �I���e�L�X�g�\���ʒu����
	constexpr float kSelectTextInterval = 120.0f;			 // �I���e�L�X�g�\���Ԋu
	const Vec2 kAfterSelectTextPos = { 800.0f, 310.0f };	 // �I����e�L�X�g�\���ʒu
	const Vec2 kCursorPos = { 140.0f, 290.0f };				// �J�[�\���\���ʒu
	const Vec2 kAfterSelectCursorPos = { 780.0f, 300.0f };	// �I����J�[�\���\���ʒu

	// �T�E���h�֘A
	const Vec2 kSoundNumTextPos = { 1650.0f, 320.0f };		 // ���ʃe�L�X�g�\���ʒu
	const Vec2 kSoundBarPos = { 950.0f, 330.0f };			 // ���ʃo�[�w�i�\���ʒu
	const Vec2 kCurrentSoundBarPos = { 954.0f, 333.0f };	 // ���݂̉��ʃo�[����ʒu
	constexpr float kCurrentSoundBarWidth = 650;			 // ���݂̉��ʃo�[�̍ő剡��
	constexpr float kCurrentSoundBarHeight = 23;			 // ���݂̉��ʃo�[�̍���
	constexpr int kCurrentSoundBarColor = 0xcf2223;			 // ���݂̉��ʃo�[�̐F
	const Vec2 kSoundKnobPos = { 1600.0f, 315.0f };			 // �܂ݏ����\���ʒu
	constexpr float kSoundKnobMinPosX = 950.0f;				 // �܂ݍŏ��\���ʒuX

	// �N���W�b�g�\�L�֘A
	const Vec2 kSoundCreditTextPos = { 800.0f, 250.0f }; 	 // �T�E���h�N���W�b�g�\�L�ʒu
	const Vec2 kModelCreditTextPos = { 800.0f, 540.0f };	 // 3D���f���N���W�b�g�\�L�ʒu
	constexpr float kCreditTextAdj = 30.0f;					 // �N���W�b�g�\�L�ʒu����
	constexpr float kCreditTextIntervel = 60.0f;			 // �N���W�b�g�\�L�Ԋu


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
	m_isSound(false)
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
	else
	{
		UpdateSelect(input, Select::kSelectNum);
	}

	m_pUI->Update();

	if (input.IsTriggered("back"))
	{
		if (m_isSound)
		{
			m_isSound = false;
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
			m_afterSelect = SelectSound::kBGM;
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
	DrawBoxAA(kBackBoxPos.x, kBackBoxPos.y, kBackBoxPos.x + kBackBoxWidth, kBackBoxPos.y + kBackBoxHeight, kBackBoxColor, true);

	// �J�[�\���\��
	if (!m_isSound)
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
	// �N���W�b�g�\�L
	if (m_select == Select::kCredit)
	{
		DrawCredit();
	}
	// �L�[�R���t�B�O�֘A�\��
	//else if (m_select == Select::kKeyConfig)
	//{
	//	DrawKeyConfig();
	//}

	// �e�L�X�g�\��
	DrawStringFToHandle(kSelectTextPos.x + kSelectTextAdj, kSelectTextPos.y + kSelectTextInterval * Select::kSound,
		"�T�E���h", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
	DrawStringFToHandle(kSelectTextPos.x - kSelectTextAdj, kSelectTextPos.y + kSelectTextInterval * Select::kCredit,
		"�N���W�b�g�\�L", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);

	// �{�^���摜�\��
	m_pUI->DrawButtonText();

	// TODO:�L�[�R���t�B�O�͌�قǍs���\��
	//DrawStringFToHandle(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kKeyConfig,
		//"�{�^���z�u", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);

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


///// <summary>
///// �L�[�X�V
///// </summary>
///// <param name="input">���͏��</param>
//void SceneOption::UpdateKeyConfig(Input& input)
//{
//}


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
	DrawBoxAA(kCurrentSoundBarPos.x, kCurrentSoundBarPos.y + kSelectTextInterval * SelectSound::kBGM,
		kCurrentSoundBarPos.x + bgmBarWidth, kCurrentSoundBarPos.y + kCurrentSoundBarHeight + kSelectTextInterval * SelectSound::kBGM,
		kCurrentSoundBarColor, true);
	DrawBoxAA(kCurrentSoundBarPos.x, kCurrentSoundBarPos.y + kSelectTextInterval * SelectSound::kSE,
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
	DrawFormatStringFToHandle(kSoundNumTextPos.x, kSoundNumTextPos.y + kSelectTextInterval * SelectSound::kBGM,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)], "%d", Sound::GetBgmVol());
	DrawFormatStringFToHandle(kSoundNumTextPos.x, kSoundNumTextPos.y + kSelectTextInterval * SelectSound::kSE,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)], "%d", Sound::GetSeVol());

}


/// <summary>
/// �N���W�b�g�\�L
/// </summary>
void SceneOption::DrawCredit()
{
	// �e�L�X�g�\��
	DrawStringFToHandle(kSoundCreditTextPos.x, kSoundCreditTextPos.y,
		"�E�T�E���h", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
	DrawStringFToHandle(kSoundCreditTextPos.x + kCreditTextAdj, kSoundCreditTextPos.y + kCreditTextIntervel,
		"���ʉ����{\nOtoLogic\n������", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
	DrawStringFToHandle(kModelCreditTextPos.x, kModelCreditTextPos.y,
		"�E3D���f��", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
	DrawStringFToHandle(kModelCreditTextPos.x + kCreditTextAdj, kModelCreditTextPos.y + kCreditTextIntervel,
		"Mixamo\nZENRIN City Asset SeriesTM", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
}


/// <summary>
/// �L�[�R���t�B�O�����\��
/// </summary>
void SceneOption::DrawKeyConfig()
{
}
