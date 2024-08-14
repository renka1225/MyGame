#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "Game.h"
#include "UI.h"
#include "SceneOption.h"

// �萔
namespace
{
	constexpr int kBackColor = 0xdddddd;			// �w�i�̐F
	constexpr int kBackBoxColor = 0x494949;			// �l�p�̐F
	constexpr int kBackBoxLTPos = 140;				// �l�p�̍���ʒu
	constexpr int kBackBoxWidth = 490;				// �l�p�̕�
	const Vec2 kSelectTextPos = { 200, 300 };		// �I���e�L�X�g�\���ʒu
	constexpr float kSelectTextInterval = 100.0f;	// �I���e�L�X�g�\���Ԋu
	const Vec2 kCursorPos = { 140, 290 };			// �J�[�\���\���ʒu
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneOption::SceneOption(std::shared_ptr<SceneBase> pScene):
	m_pPrevScene(pScene)
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
	UpdateSelect(input, kSelectNum);
	m_pUI->Update();

	if (input.IsTriggered("back"))
	{
		return m_pPrevScene;	// �O�̉�ʂɂ��ǂ�
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
	m_pUI->DrawCursor(kCursorPos, m_select, kSelectTextInterval);

	// �I�����ڕ\��
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kSound , "�T�E���h", 0xffffff);
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kBrightness, "���邳", 0xffffff);
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kKyeConfig, "�{�^���z�u", 0xffffff);

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�I�v�V�������", 0xffffff);
#endif
}
