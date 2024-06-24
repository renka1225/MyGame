#include "DxLib.h"
#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "Font.h"
#include "Input.h"

// �萔
namespace
{
	/*�I�v�V�������*/
	constexpr int kOptionPosX = 40;			// ��������\���ʒuX
	constexpr int kOptionPosY = 300;		// ��������\���ʒuX
	constexpr int kOptionWidth = 400;		// ��������̉���
	constexpr int kOptionHeight = 800;		// ��������̏c��
	constexpr int kOptionColor = 0x000000;	// ��������̔w�i�F

	/*�|�[�Y���*/
	constexpr int kPausePosX = 650;			// �g�\���ʒuX
	constexpr int kPausePosY = 200;			// �g�\���ʒuY
	constexpr int kPauseBackPosX = 670;		// �w�i�\���ʒuX
	constexpr int kPauseBackPosY = 210;		// �w�i�\���ʒuY
	constexpr int kPauseWidth = 620;		// �w�i�̉���
	constexpr int kPauseHeight = 700;		// �w�i�̏c��
	constexpr int kPauseColor = 0x040a15;	// �|�[�Y��ʂ̔w�i�F
	constexpr int kPauseAlpha = 180;		// �|�[�Y��ʂ̃��l

	// UI�\���֘A
	constexpr int kFramePosX = 780;			// �g�\���ʒuX
	constexpr int kFramePosY = 300;			// �g�\���ʒuY
	constexpr int kSelectMove = 200;		// �I��\���̈ړ���
	constexpr float kFrameAnim = 0.05f;		// �g�̊g��k���A�j���[�V�����Đ�����
	constexpr float kFrameScale = 1.0f;		// ���̘g�̃T�C�Y
	constexpr float kFrameChange = 0.1f;	// �g�̃T�C�Y�̕ω���

	// �e�L�X�g�֘A
	constexpr int kTextColor = 0x000000;	// �e�L�X�g�̐F
	constexpr int kBackPosX = 830;			// "�Q�[���ɖ߂�"�\���ʒuX
	constexpr int kBackPosY = 340;			// "�Q�[���ɖ߂�"�\���ʒuY
	constexpr int kRetryPosX = 890;			// "���g���C"�\���ʒuX
	constexpr int kRetryPosY = 540;			// "���g���C"�\���ʒuY
	constexpr int kTitlePosX = 810;			// "�^�C�g���ɖ߂�"�\���ʒuY
	constexpr int kTitlePosY = 740;			// "�^�C�g���ɖ߂�"�\���ʒuY
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
ScenePlaying::ScenePlaying():
	m_select(Select::kBack),
	m_isPause(false),
	m_frame(0),
	m_frameAnimTime(0.0f)
{
	m_pPlayer = std::make_shared<Player>();
	m_pCamera = std::make_shared<Camera>();
	m_pStage = std::make_shared<Stage>();

	m_frameHandle = LoadGraph("data/UI/frame.png");
	m_pauseBackHandle = LoadGraph("data/UI/pauseBack.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ScenePlaying::~ScenePlaying()
{
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_pauseBackHandle);
}


/// <summary>
/// ������
/// </summary>
void ScenePlaying::Init()
{
	m_pPlayer->Init();
	m_pCamera->Init();
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">����</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
#ifdef _DEBUG	// �f�o�b�O���[�h
	if (input.IsPressing("sceneChange"))
	{
		auto sceneClear = std::make_shared<SceneClear>();
		sceneClear->SetClearTime(m_frame);
		return sceneClear;	// �N���A��ʂɈړ�
	}
	// P�L�[�Ń|�[�Y�A�|�[�Y����P�ŃR�}����
	if (m_debugState == DebugState::Normal && input.IsPressing("debug_pause"))
	{
		m_debugState = DebugState::Pause;
	}
	if (m_debugState == DebugState::Pause && input.IsPressing("debug_enter"))
	{
		m_debugState = DebugState::Normal;
	}
	if (m_debugState != DebugState::Pause || input.IsPressing("debug_pause"))
#endif
	{
		// �{�^������������|�[�Y��ʂ��J��
		if (m_isPause)
		{
			m_frameAnimTime += kFrameAnim;

			// �I����Ԃ��X�V
			UpdateSelect(input);

			// �V�[���؂�ւ�
			if (input.IsTriggered("OK"))
			{
				if (m_select == Select::kBack)
				{
					m_isPause = false;	// �Q�[���ɖ߂�
				}
				else if (m_select == Select::kRetry)
				{
					return std::make_shared<ScenePlaying>(); // ���g���C����
				}
				else if (m_select == Select::kTitle)
				{
					return std::make_shared<SceneTitle>();	// �^�C�g����ʂɈړ�
				}
			}
		}
		else
		{
			m_frame++;	// �o�߃t���[�������X�V

			// �{�^������������|�[�Y��ʂ�\������
			if (input.IsPressing("pause"))
			{
				m_isPause = true;
			}

			// �v���C���[�X�V
			m_pPlayer->Update(input, *m_pCamera, *m_pStage);
			// �J�����X�V
			m_pCamera->Update(input, *m_pPlayer, *m_pStage);
		}

		// �v���C���[���S�[��������N���A��ʂɈړ�
		if (m_pPlayer->GetIsGoal())
		{
			auto sceneClear = std::make_shared<SceneClear>();
			sceneClear->SetClearTime(m_frame);

			return sceneClear;
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePlaying::Draw()
{
	// �X�e�[�W�`��
	m_pStage->Draw();

	// �v���C���[�`��
	m_pPlayer->Draw(m_pDrawDebug);

	// ��������\��
	DrawOption();

	// �|�[�Y��ʕ\��
	if (m_isPause)
	{
		DrawPause();
	}

#ifdef _DEBUG	// �f�o�b�O�\��
	// �O���b�h�\��
	//m_pDrawDebug.DrawGrid();
	// ���݂̃V�[��
	DrawString(0, 0, "�v���C���", 0xffffff);
	// �^�C���\��
	m_pDrawDebug.DrawTime(m_frame);
#endif
}


/// <summary>
/// �I����Ԃ��X�V
/// </summary>
/// <param name="input">����</param>
void ScenePlaying::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1������
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;;	// �I����Ԃ�1�グ��
	}
}


/// <summary>
/// ���������\��
/// </summary>
void ScenePlaying::DrawOption()
{
	// �w�i�𔖂��\������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kPauseAlpha);
	DrawBox(kOptionPosX, kOptionPosY, kOptionWidth, kOptionHeight, kOptionColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �����\��
	DrawFormatStringToHandle(50, 350,
		0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)], "�������");
}


/// <summary>
/// �|�[�Y��ʂ�\��
/// </summary>
void ScenePlaying::DrawPause()
{
	// �|�[�Y��ʂ�\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kPauseAlpha);
	DrawBox(kPauseBackPosX, kPauseBackPosY, kPauseBackPosX + kPauseWidth, kPauseBackPosY + kPauseHeight, kPauseColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawGraph(kPausePosX, kPausePosY, m_pauseBackHandle, true);

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
	DrawFormatStringToHandle(kBackPosX, kBackPosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kPauseMenu)], "�Q�[���ɂ��ǂ�");
	DrawFormatStringToHandle(kRetryPosX, kRetryPosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kPauseMenu)], "���g���C");
	DrawFormatStringToHandle(kTitlePosX, kTitlePosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kPauseMenu)], "�^�C�g���ɂ��ǂ�");

#ifdef _DEBUG
	DrawString(0, 10, "�|�[�Y��", 0xffffff);
#endif
}
