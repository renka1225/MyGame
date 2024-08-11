#include "Dxlib.h"
#include "Input.h"
#include "Vec2.h"
#include "Game.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneTitle.h"
#include "SceneSelectStage.h"
#include "SceneStage2.h"
#include "SceneGameover.h"

// �萔
namespace
{
	const char* const kHaibokuTextPath = "data/UI/haiboku.png";	// �s�k�̃e�L�X�g�摜�̃t�@�C���ʒu
	const char* const kCursorPath = "data/UI/cursor.png";		// �J�[�\���摜�̃t�@�C���ʒu
	const Vec2 kHaibokuTextPos = { 670, 100 };					// �s�k�̃e�L�X�g�摜�\���ʒu
	const Vec2 kRetryTextPos = { 650, 600 };					// "���g���C"�\���ʒu
	const Vec2 kStageTextPos = { 650, 700 };					// "�X�e�[�W�I���ɂ��ǂ�"�\���ʒu
	const Vec2 kTitleTextPos = { 650, 800 };					// "�^�C�g���ɂ��ǂ�"�\���ʒu
	const Vec2 kCursorPos = { 600, 590 };						// �J�[�\���\���ʒu
	constexpr float kCursorMove = 100.0f;						// �J�[�\���̈ړ���
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pScene">�O�Ɏ��s���Ă����V�[��</param>
SceneGameover::SceneGameover(std::shared_ptr<SceneBase> pScene)
{
	m_select = Select::kRetry;
	m_pPrevScene = pScene;
	m_textHandle = LoadGraph(kHaibokuTextPath);
	m_cursorHandle = LoadGraph(kCursorPath);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneGameover::~SceneGameover()
{
	DeleteGraph(m_textHandle);
	DeleteGraph(m_cursorHandle);
}


/// <summary>
/// ������
/// </summary>
void SceneGameover::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <returns></returns>
std::shared_ptr<SceneBase> SceneGameover::Update(Input& input)
{
	UpdateSelect(input);	// �I����ԍX�V

	if (input.IsTriggered("OK"))
	{
		if (m_select == kRetry)
		{
			std::shared_ptr<Player> pPlayer = std::make_shared<Player>();
			std::shared_ptr<Camera> pCamera = std::make_shared<Camera>();
			std::shared_ptr<Stage> pStage = std::make_shared<Stage>();
			return std::make_shared<SceneStage2>(pPlayer, pCamera, pStage);	// �v���C��ʂɈړ�
			//return m_pPrevScene;
		}
		else if (m_select == kStageSelect)
		{
			return std::make_shared<SceneSelectStage>(); // �X�e�[�W�I����ʂɈړ�
		}
		else if (m_select == kTitle)
		{
			return std::make_shared<SceneTitle>();	// �^�C�g����ʂɈړ�
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneGameover::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x1a1a1a, true);

	// �s�k�̕�����\��
	DrawGraphF(kHaibokuTextPos.x, kHaibokuTextPos.y, m_textHandle, true);

	// �J�[�\���\��
	DrawGraphF(kCursorPos.x, kCursorPos.y + kCursorMove * m_select, m_cursorHandle, true);

	// �I�����ڂ�\��
	DrawStringF(kRetryTextPos.x, kRetryTextPos.y, "���g���C", 0xffffff);
	DrawStringF(kStageTextPos.x, kStageTextPos.y, "�X�e�[�W�I���ɂ��ǂ�", 0xffffff);
	DrawStringF(kTitleTextPos.x, kTitleTextPos.y, "�^�C�g���ɂ��ǂ�", 0xffffff);

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�Q�[���I�[�o�[���", 0xffffff);
	// ���S��
	DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0x0000ff);
#endif
}


/// <summary>
/// �I����Ԃ��X�V����
/// </summary>
/// <param name="input">���͏��</param>
void SceneGameover::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1������
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;	// �I����Ԃ�1�グ��
	}
}
