#include "EffekseerForDXLib.h"
#include "DxLib.h"
#include "Vec2.h"
#include "Game.h"
#include "Input.h"
#include "Sound.h"
#include "UI.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "SceneOption.h"
#include "SceneTitle.h"
#include "SceneSelectStage.h"

// �萔
namespace
{
	constexpr int kBackColor = 0xdddddd;			// �w�i�̐F
	constexpr int kBackBoxColor = 0x494949;			// �l�p�̐F
	constexpr int kBackBoxLTPos = 140;				// �l�p�̍���ʒu
	constexpr int kBackBoxWidth = 490;				// �l�p�̕�
	const Vec2 kSelectTextPos = { 200, 300 };		// �I���e�L�X�g�\���ʒu
	constexpr float kSelectTextInterval = 100.0f;	// �I���e�L�X�g�\���Ԋu
	const Vec2 kCursorLTPos = { 140, 290 };			// �J�[�\������ʒu
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneSelectStage::SceneSelectStage()
{
	m_select = SelectScene::kStage1;
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneSelectStage::~SceneSelectStage()
{
	StopSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kStageSelect)]);
}


/// <summary>
/// ������
/// </summary>
void SceneSelectStage::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏���</param>
/// <returns>�J�ڐ�̃V�[��</returns>
std::shared_ptr<SceneBase> SceneSelectStage::Update(Input& input)
{
	//�I����ԍX�V
	UpdateSelect(input, kSelectNum);
	m_pUI->Update();

	// BGM��炷
	if (!CheckSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kStageSelect)]))
	{
		PlaySoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kStageSelect)], DX_PLAYTYPE_LOOP);
	}

	// �V�[���J��
	if (input.IsTriggered("OK"))
	{
		PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kSelect)], DX_PLAYTYPE_BACK); // SE��炷

		std::shared_ptr<Player> pPlayer = std::make_shared<Player>();
		std::shared_ptr<Camera> pCamera = std::make_shared<Camera>();
		std::shared_ptr<Stage> pStage = std::make_shared<Stage>();

		if (m_select == SelectScene::kStage1)
		{
			return std::make_shared<SceneStage1>(pPlayer, pCamera, pStage);
		}
		else if (m_select == SelectScene::kStage2)
		{
			return std::make_shared<SceneStage2>(pPlayer, pCamera, pStage);
		}
		else if (m_select == kOption)
		{
			return std::make_shared<SceneOption>();
		}
		else if (m_select == kEnd)
		{
			Effkseer_End();	// Effekseer�̏I������
			DxLib_End();
		}
	}
	if (input.IsTriggered("back"))
	{
		return std::make_shared<SceneTitle>();
	}

	return shared_from_this();
}


/// <summary>
/// �`��
/// </summary>
void SceneSelectStage::Draw()
{
	// �w�i�`��
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBackColor, true);
	// �w�i�̎l�p�����\��
	DrawBox(kBackBoxLTPos, 0, kBackBoxLTPos + kBackBoxWidth, Game::kScreenHeight, kBackBoxColor, true);
	
	// �J�[�\���\��
	m_pUI->DrawCursor(kCursorLTPos, m_select, kSelectTextInterval);

	// �e�L�X�g�\��
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * SelectScene::kStage1, "���K�։���", 0xffffff);
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * SelectScene::kStage2, "�����։���", 0xffffff);
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * SelectScene::kOption, "�I�v�V����", 0xffffff);
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * SelectScene::kEnd, "�Q�[�����I���", 0xffffff);

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�X�e�[�W�I�����", 0xffffff);
#endif
}


