#include "DxLib.h"
#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "Light.h"
#include "Confetti.h"
#include "Font.h"
#include "Sound.h"
#include "Input.h"

// �萔
namespace
{	
	/*�t�F�[�h*/
	constexpr int kFadeFrame = 8;			// �t�F�[�h�ω���
	constexpr int kStartFadeAlpha = 200;	// �X�^�[�g���̃t�F�[�h���l
	constexpr int kMaxFadeAlpha = 255;		// �ő�t�F�[�h���l

	/*����������*/
	constexpr int kOperationFramePosX = 40;			// �g�\���ʒuX
	constexpr int kOperationFramePosY = 340;		// �g�\���ʒuY
	constexpr int kOperationWidth = 200;			// �g�̉���
	constexpr int kOperationHeight = 770;			// �g�̏c��
	constexpr int kOperationBackColor = 0x000000;	// �g�̔w�i�F

	// �e�L�X�g
	constexpr int kTaskPosX = 40;				// �^�X�N�\���ʒuX
	constexpr int kTaskPosY = 50;				// �^�X�N�\���ʒuY
	constexpr int kTaskColor = 0xffffff;		// �^�X�N�̕����F
	constexpr int kOpenClosePosX = 90;			// "�Ђ炭�A�Ƃ���"�\���ʒuX
	constexpr int kOpenClosePosY = 390;			// "�Ђ炭�A�Ƃ���"�\���ʒuY
	constexpr int kOperationPosX = 50;			// "�������"�\���ʒuX
	constexpr int kOperationPosY = 350;			// "�������"�\���ʒuY
	constexpr int kMovePosX = 50;				// "�ړ�"�\���ʒuX
	constexpr int kMovePosY = 450;				// "�ړ�"�\���ʒuY
	constexpr int kJumpPosX = 50;				// "�W�����v"�\���ʒuX
	constexpr int kJumpPosY = 530;				// "�W�����v"�\���ʒuY
	constexpr int kMoveCameraPosX = 50;			// "�J�����ړ�"�\���ʒuX
	constexpr int kMoveCameraPosY = 610;		// "�J�����ړ�"�\���ʒuY
	constexpr int kPausePosX = 50;				// "�|�[�Y"�\���ʒuX
	constexpr int kPausePosY = 690;				// "�|�[�Y"�\���ʒuY
	constexpr int kOperationColor = 0x34a3f8;	// "�������"�̕����F
	// �{�^���摜
	constexpr int kButtonSize = 32;				// �{�^��1�̃T�C�Y
	constexpr float kButtonScale = 1.3f;		// �{�^���̊g�嗦
	constexpr int kButtonPosX = 110;			// �{�^���̕\���ʒuX
	constexpr int kButtonPosY = 500;			// �{�^���̕\���ʒuY
	constexpr int kLRButtonPosX = 120;			// LB,RB�{�^���̕\���ʒuX
	constexpr int kViewButtonPosX = 70;			// �r���[�{�^���̕\���ʒuX
	constexpr int kViewButtonPosY = 400;		// �r���[�{�^���̕\���ʒuY
	constexpr float kViewButtonScale = 1.0f;	// �r���[�{�^���̊g�嗦
	constexpr int kButtonInterval = 80;			// �{�^���̕\���Ԋu

	/*�|�[�Y���*/
	constexpr int kPauseFramePosX = 650;	// �g�\���ʒuX
	constexpr int kPauseFramePosY = 200;	// �g�\���ʒuY
	constexpr int kPauseBackPosX = 670;		// �w�i�\���ʒuX
	constexpr int kPauseBackPosY = 210;		// �w�i�\���ʒuY
	constexpr int kPauseWidth = 620;		// �w�i�̉���
	constexpr int kPauseHeight = 700;		// �w�i�̏c��
	constexpr int kPauseColor = 0x040a15;	// �|�[�Y��ʂ̔w�i�F
	constexpr int kPauseAlpha = 180;		// �|�[�Y��ʂ̃��l
	// �g
	constexpr int kFramePosX = 780;			// �g�\���ʒuX
	constexpr int kFramePosY = 300;			// �g�\���ʒuY
	constexpr int kSelectMove = 200;		// �I��\���̈ړ���
	constexpr float kFrameAnim = 0.05f;		// �g�̊g��k���A�j���[�V�����Đ�����
	constexpr float kFrameScale = 1.0f;		// ���̘g�̃T�C�Y
	constexpr float kFrameChange = 0.1f;	// �g�̃T�C�Y�̕ω���
	constexpr float kHalf = 0.5f;			// ����
	// �e�L�X�g
	constexpr int kTextColor = 0x000000;	// �e�L�X�g�̐F
	constexpr int kBackPosX = 830;			// "�Q�[���ɖ߂�"�\���ʒuX
	constexpr int kBackPosY = 340;			// "�Q�[���ɖ߂�"�\���ʒuY
	constexpr int kRetryPosX = 890;			// "���g���C"�\���ʒuX
	constexpr int kRetryPosY = 540;			// "���g���C"�\���ʒuY
	constexpr int kTitlePosX = 810;			// "�^�C�g���ɖ߂�"�\���ʒuY
	constexpr int kTitlePosY = 740;			// "�^�C�g���ɖ߂�"�\���ʒuY

	/*�N���A���o*/
	constexpr float kClearStagingTime = 240.0f;	 // �N���A���o�̎���
	constexpr float kClearSETime = 180.0f;		 // �N���ASE���~�߂鎞��
	constexpr float kClearCheersSETime = 200.0f; // ������SE���Đ����鎞��
	constexpr int kAddPal = 200;				 // ���Z�u�����h�̒l

	/*�V���h�E�}�b�v*/
	constexpr int kShadowMapSize = 1024;							// �쐬����V���h�E�}�b�v�̃T�C�Y
	const VECTOR kShadowMapMinPos = VGet(-500.0f, 0.0f, -500.0f);   // �V���h�E�}�b�v�͈̔͂̍ŏ��l
	const VECTOR kShadowMapMaxPos = VGet(500.0f, 200.0f, 500.0f);   // �V���h�E�}�b�v�͈̔͂̍ő�l
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
ScenePlaying::ScenePlaying() :
	m_select(Select::kBack),
	m_isOperation(true),
	m_isPause(false),
	m_frame(0),
	m_frameAnimTime(0.0f),
	m_clearStagingTime(kClearStagingTime)
{
	m_fadeAlpha = kStartFadeAlpha;
	m_pPlayer = std::make_shared<Player>();
	m_pCamera = std::make_shared<Camera>();
	m_pStage = std::make_shared<Stage>();

	m_frameHandle = LoadGraph("data/UI/frame.png");
	m_pauseBackHandle = LoadGraph("data/UI/pauseBack.png");
	m_padHandle = LoadGraph("data/UI/pad.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ScenePlaying::~ScenePlaying()
{
	StopSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kPlayBGM)]);
	StopSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kClearCheersSE)]);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_pauseBackHandle);
	DeleteGraph(m_padHandle);
	Light::DeleteLight();
	Confetti::DeleteCofetti();
}


/// <summary>
/// ������
/// </summary>
void ScenePlaying::Init()
{
	m_pPlayer->Init();
	m_pCamera->Init();
	Light::SetLight();
	Confetti::CreateCofetti();
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">����</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
#ifdef _DEBUG	// �f�o�b�O���[�h
	if (input.IsTriggered("sceneChange"))
	{
		ClearStaging();	// �N���A���o���s��
		if (m_clearStagingTime <= 0.0f)
		{
			auto sceneClear = std::make_shared<SceneClear>();
			sceneClear->SetClearTime(m_frame);
			return sceneClear;
		}
	}
	// P�L�[�Ń|�[�Y�A�|�[�Y����P�ŃR�}����
	if (m_debugState == DebugState::Normal && input.IsTriggered("debug_pause"))
	{
		m_debugState = DebugState::Pause;
	}
	if (m_debugState == DebugState::Pause && input.IsTriggered("debug_enter"))
	{
		m_debugState = DebugState::Normal;
	}
	if (m_debugState != DebugState::Pause || input.IsTriggered("debug_pause"))
#endif
	{
		FadeOut(); // �t�F�[�h�A�E�g

		// BGM��炷
		if (!CheckSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kPlayBGM)]))
		{
			PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kPlayBGM)], DX_PLAYTYPE_LOOP);
		}

		// �{�^������������|�[�Y��ʂ��J��
		if (m_isPause)
		{
			m_frameAnimTime += kFrameAnim;

			// �I����Ԃ��X�V
			UpdateSelect(input);

			// �V�[���؂�ւ�
			if (input.IsTriggered("OK"))
			{
				FadeIn(); // �t�F�[�h�C��
				PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kSelectSE)], DX_PLAYTYPE_BACK); // SE��炷
				
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

			// �v���C���[�X�V
			m_pPlayer->Update(input, *m_pCamera, *m_pStage);
			// �J�����X�V
			m_pCamera->Update(input, *m_pPlayer, *m_pStage);

			// �\����Ԃ��X�V����
			if (!m_pPlayer->GetIsGoal())
			{
				UpdateOperation(input);
				UpdatePause(input);
			}
		}

		// �v���C���[���S�[��������N���A��ʂɈړ�
		if (m_pPlayer->GetIsGoal())
		{
			ClearStaging();	// �N���A���o���s��
			if (m_clearStagingTime <= 0.0f)
			{
				auto sceneClear = std::make_shared<SceneClear>();
				sceneClear->SetClearTime(m_frame);
				return sceneClear;
			}
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
	DrawOperation();

	// �|�[�Y��ʕ\��
	if (m_isPause)
	{
		DrawPause();
	}

	// �N���A���o�`��
	if (m_pPlayer->GetIsGoal())
	{
		DrawClearStaging();
	}

	// �t�F�[�h�C���A�E�g�`��
	DrawFade();

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
/// �t�F�[�h�C������
/// </summary>
void ScenePlaying::FadeIn()
{
	m_fadeAlpha += kFadeFrame;
}


/// <summary>
/// �t�F�[�h�A�E�g����
/// </summary>
void ScenePlaying::FadeOut()
{
	m_fadeAlpha -= kFadeFrame;
}


/// <summary>
/// �I����Ԃ��X�V
/// </summary>
/// <param name="input">����</param>
void ScenePlaying::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kCursorSE)], DX_PLAYTYPE_BACK); //SE��炷
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1������
	}
	if (input.IsTriggered("up"))
	{
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kCursorSE)], DX_PLAYTYPE_BACK); //SE��炷
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;	// �I����Ԃ�1�グ��
	}
}


/// <summary>
/// ��������̕\����Ԃ��X�V
/// </summary>
/// <param name="input">����</param>
void ScenePlaying::UpdateOperation(Input& input)
{
	// ���������ʂ̕\����\��
	if (input.IsTriggered("operation"))
	{
		if (m_isOperation)
		{
			m_isOperation = false;
		}
		else
		{
			m_isOperation = true;
		}
	}
}


/// <summary>
/// �|�[�Y��ʂ̕\����Ԃ��X�V
/// </summary>
/// <param name="input">����</param>
void ScenePlaying::UpdatePause(Input& input)
{
	// �{�^������������|�[�Y��ʂ�\������
	if (input.IsTriggered("pause"))
	{
		// SE��炷
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kCursorSE)], DX_PLAYTYPE_BACK);
		m_isPause = true;
	}
}


/// <summary>
/// �N���A���̉��o	
/// </summary>
void ScenePlaying::ClearStaging()
{
	m_clearStagingTime--;

	Confetti::UpdateCofetti();

	if (m_clearStagingTime >= kClearSETime && !CheckSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kClearSE)]))
	{
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kClearSE)], DX_PLAYTYPE_BACK);		  // SE��炷
	}
	else if (m_clearStagingTime <= kClearCheersSETime && !CheckSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kClearCheersSE)]))
	{
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kClearCheersSE)], DX_PLAYTYPE_LOOP); // SE��炷
	}
}


/// <summary>
/// ���������\��
/// </summary>
void ScenePlaying::DrawOperation()
{
	// �J���Ă���Ƃ�
	if (m_isOperation)
	{
		// �w�i�𔖂��\������
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, kPauseAlpha);
		DrawBox(kOperationFramePosX, kOperationFramePosY, kOperationWidth, kOperationHeight, kOperationBackColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		// �����\��
		DrawStringToHandle(kOpenClosePosX, kOpenClosePosY, "�łƂ���",
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)]);
		DrawStringToHandle(kMovePosX, kMovePosY, "�ړ�",
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)]);
		DrawStringToHandle(kJumpPosX, kJumpPosY, "�W�����v",
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)]);
		DrawStringToHandle(kMoveCameraPosX, kMoveCameraPosY, "�J�����ړ�",
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)]);
		DrawStringToHandle(kPausePosX, kPausePosY, "�|�[�Y",
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)]);

		// LS�A�i���O�X�e�B�b�N
		DrawRectRotaGraph(kButtonPosX, kButtonPosY + kButtonInterval * Button::kLSButton,
			kButtonSize * Button::kLSButton, 0,
			kButtonSize, kButtonSize, kButtonScale, 0.0f,
			m_padHandle, true);
		// A�{�^��
		DrawRectRotaGraph(kButtonPosX, kButtonPosY + kButtonInterval * Button::kAButton,
			kButtonSize * Button::kAButton, 0,
			kButtonSize, kButtonSize, kButtonScale, 0.0f,
			m_padHandle, true);
		// LB,RB�{�^��
		DrawRectRotaGraph(kLRButtonPosX, kButtonPosY + kButtonInterval * Button::kLRButton,
			kButtonSize * (Button::kLRButton), 0,
			kButtonSize * 2, kButtonSize, kButtonScale, 0.0f,
			m_padHandle, true);
		// �O�{���{�^��
		DrawRectRotaGraph(kButtonPosX, kButtonPosY + kButtonInterval * Button::kLineButton,
			kButtonSize * (Button::kLineButton + 1), 0,
			kButtonSize, kButtonSize, kButtonScale, 0.0f,
			m_padHandle, true);
	}
	// ���Ă���Ƃ�
	else
	{
		DrawStringToHandle(kOpenClosePosX, kOpenClosePosY, "�łЂ炭",
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)]);
	}

	DrawStringToHandle(kOperationPosX, kOperationPosY, "�������",
		kOperationColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);

	// �r���[�{�^��
	DrawRectRotaGraph(kViewButtonPosX, kViewButtonPosY,
		kButtonSize * (Button::kViewButton + 1), 0,
		kButtonSize, kButtonSize, kViewButtonScale, 0.0f, m_padHandle, true);

	// �����\��
	DrawStringToHandle(kTaskPosX, kTaskPosY, "�W�����v�ł��΂₭\n�S�[�����߂����I\n",
		kTaskColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kTask)]);
}


/// <summary>
/// �|�[�Y��ʂ�\��
/// </summary>
void ScenePlaying::DrawPause()
{
	// �|�[�Y��ʂ�\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kPauseAlpha);
	DrawBox(kPauseBackPosX, kPauseBackPosY, kPauseBackPosX + kPauseWidth, kPauseBackPosY + kPauseHeight, kPauseColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, kMaxFadeAlpha);
	DrawGraph(kPauseFramePosX, kPauseFramePosY, m_pauseBackHandle, true);

	// �g�\��
	for (int i = 0; i < kSelectNum; i++)
	{
		if (m_select == i)
		{
			// �g�̃T�C�Y��1.0�`1.1�ŕω�������
			float scale = kFrameScale + kFrameChange * sin(m_frameAnimTime);

			int width, height;
			int size = GetGraphSize(m_frameHandle, &width, &height);
			int scaleWidth = static_cast<int>(width * scale);
			int scaleHeight = static_cast<int>(height * scale);

			// �I�𒆂̃{�^�����g��k��������
			DrawExtendGraph(
				kFramePosX - static_cast<int>((scaleWidth - width) * kHalf),
				kFramePosY + kSelectMove * i - static_cast<int>((scaleHeight - height) * kHalf),
				kFramePosX + static_cast<int>((scaleWidth - width) * kHalf) + width,
				kFramePosY + static_cast<int>(kSelectMove * i + (scaleHeight - height) * kHalf) + height,
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


/// <summary>
/// �N���A���̉��o�`��
/// </summary>
void ScenePlaying::DrawClearStaging()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, kAddPal);
	Confetti::DrawCofetti();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, kMaxFadeAlpha);
}
