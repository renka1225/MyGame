#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "SceneSelectStage.h"
#include "SceneTitle.h"
#include "Game.h"

// �萔
namespace
{
	const Vec2 kTitleLogoPos = { 950, 400 };
	constexpr float kTitleLogoScale = 0.5f;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle()
{
	m_titleLogo = LoadGraph("data/UI/titleLogo.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogo);
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
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);
	// �^�C�g�����S�\��
	DrawRectRotaGraphF(kTitleLogoPos.x, kTitleLogoPos.y, 0, 0, Game::kScreenWidth, Game::kScreenHeight, kTitleLogoScale, 0.0f, m_titleLogo, true);

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�^�C�g�����", 0xffffff);
#endif
}
