#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "Game.h"
#include "UI.h"
#include "ScenePause.h"
#include "SceneOption.h"
#include "SceneSelectStage.h"

// �萔
namespace
{
	constexpr int kAlpha = 200;
	constexpr int kBackColor = 0xdcdcdc;				// �w�i�̐F
	constexpr int kBackBoxColor = 0x494949;				// �l�p�̐F
	const Vec2 kBackBoxLTPos = { 500.0f, 120.0f };		// �l�p�̍���ʒu
	const Vec2 kBackBoxRBPos = { 1420.0f, 880.0f };		// �l�p�̉E���ʒu
	constexpr int kBackBoxWidth = 490;					// �l�p�̕�
	const Vec2 kSelectTextPos = { 750, 300 };			// �I���e�L�X�g�\���ʒu
	constexpr float kSelectTextInterval = 200.0f;		// �I���e�L�X�g�\���Ԋu
	const Vec2 kCursorPos = { 700, 290 };				// �J�[�\���\���ʒu
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pScene">�O�Ɏ��s���Ă����V�[��</param>
ScenePause::ScenePause(std::shared_ptr<SceneBase> pScene)
{
	m_select = Select::kBack;
	m_pPrevScene = pScene;
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ScenePause::~ScenePause()
{
}


/// <summary>
/// ������
/// </summary>
void ScenePause::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePause::Update(Input& input)
{
	// �I����Ԃ��X�V
	UpdateSelect(input, Select::kSelectNum);
	m_pUI->Update();

	if (input.IsTriggered("OK"))
	{
		if (m_select == Select::kBack)
		{
			return m_pPrevScene;	// �Q�[�����
		}
		else if (m_select == Select::kOption)
		{
			return std::make_shared<SceneOption>(shared_from_this());	// �I�v�V�������
		}
		else if (m_select == Select::kStageSelect)
		{
			return std::make_shared<SceneSelectStage>(); // �X�e�[�W�I�����
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePause::Draw()
{
	// �v���C��ʂ𔖂��\������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAlpha);
	m_pPrevScene->Draw();
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBackColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �w�i�ɍ��g��\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAlpha);
	DrawBoxAA(kBackBoxLTPos.x, kBackBoxLTPos.y, kBackBoxRBPos.x, kBackBoxRBPos.y, kBackBoxColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �J�[�\���\��
	m_pUI->DrawCursor(kCursorPos, m_select, kSelectTextInterval);

	// �e�L�X�g�\��
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kBack, "�Q�[���ɂ��ǂ�", 0x000000);
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kOption ,"�I�v�V����", 0x000000);
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kStageSelect,"�X�e�[�W�I���ɖ߂�", 0x000000);

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�|�[�Y���", 0xffffff);
#endif
}
