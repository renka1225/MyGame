#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "Sound.h"
#include "Game.h"
#include "UI.h"
#include "SceneOption.h"

// �萔
namespace
{
	constexpr int kBackColor = 0xdddddd;				 // �w�i�̐F
	constexpr int kBackBoxColor = 0x494949;				 // �l�p�̐F
	constexpr int kBackBoxLTPos = 140;					 // �l�p�̍���ʒu
	constexpr int kBackBoxWidth = 490;					 // �l�p�̕�
	const Vec2 kSelectTextPos = { 200, 300 };			 // �I���e�L�X�g�\���ʒu
	constexpr float kSelectTextInterval = 100.0f;		 // �I���e�L�X�g�\���Ԋu
	const Vec2 kCursorPos = { 140, 290 };				 // �J�[�\���\���ʒu
	const Vec2 kAfterSelectTextPos = { 800, 310 };		 // �I����e�L�X�g�\���ʒu
	constexpr float kAfterSelectTextInterval = 100.0f;	 // �I����e�L�X�g�\���Ԋu
	const Vec2 kAfterSelectCursorPos = { 800, 300 };	 // �I����J�[�\���\���ʒu
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
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneOption::~SceneOption()
{
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
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBackColor, true);
	// �w�i�̎l�p�����\��
	DrawBox(kBackBoxLTPos, 0, kBackBoxLTPos + kBackBoxWidth, Game::kScreenHeight, kBackBoxColor, true);

	// �J�[�\���\��
	if (!m_isSound && !m_isKeyConfig)
	{
		m_pUI->DrawCursor(kCursorPos, m_select, kSelectTextInterval);
	}
	else
	{
		m_pUI->DrawCursor(kAfterSelectCursorPos, m_afterSelect, kAfterSelectTextInterval);
	}

	// �e�L�X�g�\��
	DrawDispText();

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�I�v�V�������", 0xffffff);
	DrawFormatString(0, 100, 0xffffff, "���:%d", m_afterSelect);
	DrawFormatString(0, 120, 0xffffff, "���:%d", m_select);
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
		//// ���ʂ�������
		//if (input.IsPressing("left"))
		//{
		//	printfDx("BGM:-1\n");
		//}
		//// ���ʂ��グ��
		//else if (input.IsPressing("right"))
		//{
		//	printfDx("BGM:+1\n");
		//}

		Sound::ChangeBgmVol(input);
	}
	// SE�I�𒆂̏ꍇ
	if (m_afterSelect == SelectSound::kSE)
	{
		//// ���ʂ�������
		//if (input.IsPressing("left"))
		//{
		//	printfDx("SE:-1\n");
		//}
		//// ���ʂ��グ��
		//else if (input.IsPressing("right"))
		//{
		//	printfDx("SE:+1\n");
		//}

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
/// �e�L�X�g�\��
/// </summary>
void SceneOption::DrawDispText()
{
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kSound, "�T�E���h", 0xffffff);
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kKeyConfig, "�{�^���z�u", 0xffffff);

	if (m_isSound)
	{
		DrawStringF(kAfterSelectTextPos.x, kAfterSelectTextPos.y + kAfterSelectTextInterval * SelectSound::kBGM, "BGM", 0xffffff);
		DrawStringF(kAfterSelectTextPos.x, kAfterSelectTextPos.y + kAfterSelectTextInterval * SelectSound::kSE, "SE", 0xffffff);
	}
	else if (m_isKeyConfig)
	{
		DrawStringF(kAfterSelectTextPos.x, kAfterSelectTextPos.y + kAfterSelectTextInterval * SelectKeyConfig::kXButton, "X", 0xffffff);
		DrawStringF(kAfterSelectTextPos.x, kAfterSelectTextPos.y + kAfterSelectTextInterval * SelectKeyConfig::kYButton, "Y", 0xffffff);
	}
}