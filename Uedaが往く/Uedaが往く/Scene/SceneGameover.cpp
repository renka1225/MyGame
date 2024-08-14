#include "Dxlib.h"
#include "Input.h"
#include "Vec2.h"
#include "Game.h"
#include "UI.h"
#include "Sound.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneTitle.h"
#include "SceneSelectStage.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "SceneGameover.h"

// �萔
namespace
{
	const char* const kHaibokuTextPath = "data/UI/haiboku.png";	// �s�k�̃e�L�X�g�摜�̃t�@�C���ʒu
	const char* const kCursorPath = "data/UI/cursor.png";		// �J�[�\���摜�̃t�@�C���ʒu
	const Vec2 kHaibokuTextPos = { 670, 100 };					// �s�k�̃e�L�X�g�摜�\���ʒu
	const Vec2 kRetryTextPos = { 850, 600 };					// "���g���C"�\���ʒu
	const Vec2 kStageTextPos = { 850, 700 };					// "�X�e�[�W�I���ɂ��ǂ�"�\���ʒu
	const Vec2 kTitleTextPos = { 850, 800 };					// "�^�C�g���ɂ��ǂ�"�\���ʒu
	const Vec2 kCursorPos = { 750, 590 };						// �J�[�\���\���ʒu
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
	StopSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kGameoverBGM)]);
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
	// �I����ԍX�V
	UpdateSelect(input, Select::kSelectNum);
	m_pUI->Update();

	// BGM��炷
	if (!CheckSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kGameoverBGM)]))
	{
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kGameoverBGM)], DX_PLAYTYPE_LOOP);
	}

	if (input.IsTriggered("OK"))
	{
		if (m_select == kRetry)
		{
			std::shared_ptr<Player> pPlayer = std::make_shared<Player>();
			std::shared_ptr<Camera> pCamera = std::make_shared<Camera>();
			std::shared_ptr<Stage> pStage = std::make_shared<Stage>();

			// MEMO:typeid�ŃN���X���擾����
			if (typeid(*m_pPrevScene) == typeid(SceneStage1))
			{
				return std::make_shared<SceneStage1>(pPlayer, pCamera, pStage); // �X�e�[�W1�Ɉړ�
			}
			if (typeid(*m_pPrevScene) == typeid(SceneStage2))
			{
				return std::make_shared<SceneStage2>(pPlayer, pCamera, pStage); // �X�e�[�W2�Ɉړ�
			}

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
	m_pUI->DrawCursor(kCursorPos, m_select, kCursorMove);

	// �I�����ڂ�\��
	DrawStringF(kRetryTextPos.x, kRetryTextPos.y, "���g���C", 0xffffff);
	DrawStringF(kStageTextPos.x, kStageTextPos.y, "�X�e�[�W�I���ɂ��ǂ�", 0xffffff);
	DrawStringF(kTitleTextPos.x, kTitleTextPos.y, "�^�C�g���ɂ��ǂ�", 0xffffff);

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�Q�[���I�[�o�[���", 0xffffff);
	// ���S��
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0x0000ff);
#endif
}