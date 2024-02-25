#include "SceneGameOver.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

/// <summary>
/// �萔
/// </summary>
namespace
{
	// Gameover�̕����\���ʒu
	constexpr int kGameOverPosX = 960;
	constexpr int kGameOverPosY = 280;
	// Gameover�̕����T�C�Y
	constexpr int kGameOverSizeX = 1592;
	constexpr int kGameOverSizeY = 174;
	// Gameover�̕����g�嗦
	constexpr float kGameOverScale = 0.8f;

	// �����\���ʒu
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 720;

	// �I���J�[�\���̏����ʒu
	constexpr int kInitSelectPosX = 910;
	constexpr int kInitSelectPosY = 540;
	// �I���J�[�\���̈ړ���
	constexpr int kSelectmoveY = 185;
	// �I���J�[�\���̃T�C�Y
	constexpr int kSelectSizeX = 500;
	constexpr int kSelectSizeY = 700;

	// �w�i�g�嗦
	constexpr float kBgScale = 3.0f;
	// �w�i�摜�̈ړ���
	constexpr float kBgMove = -1.0f;

	//�t�F�[�h
	constexpr int kFadeFrame = 8;
}


SceneGameOver::SceneGameOver():
	m_select(kRetry),
	m_isSceneRetry(false),
	m_isSceneSelect(false),
	m_isSceneTitle(false),
	m_fadeAlpha(255),
	m_bgMove(0.0f)
{
	// �摜�ǂݍ���
	m_bgHandle = LoadGraph("data/image/BackGround/gameover/gameover.png");
	m_bg2Handle = LoadGraph("data/image/BackGround/gameover/2.png");
	m_bg3Handle = LoadGraph("data/image/BackGround/gameover/3.png");
	m_gameoverHandle = LoadGraph("data/image/UI/gameover.png");
	m_charHandle = LoadGraph("data/image/UI/gameoverSelect.png");
	m_selectHandle = LoadGraph("data/image/UI/select.png");

	// ���ǂݍ���
	m_bgm = LoadSoundMem("data/sound/BGM/gameover.mp3");
	m_selectSE = LoadSoundMem("data/sound/SE/select.wav");
	m_cursorSE = LoadSoundMem("data/sound/SE/cursor.mp3");
}


SceneGameOver::~SceneGameOver()
{
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_bg2Handle);
	DeleteGraph(m_bg3Handle);
	DeleteGraph(m_gameoverHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_selectHandle);
	DeleteSoundMem(m_bgm);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_cursorSE);
}


/// <summary>
/// ������
/// </summary>
void SceneGameOver::Init()
{
	m_isSceneRetry = false;
	m_isSceneSelect = false;
	m_isSceneTitle = false;
	m_fadeAlpha = 255;
	m_select = kRetry;
	m_selectPos = { kInitSelectPosX, kInitSelectPosY };
	m_bgMove = kBgMove;

	// BGM��炷
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
}


/// <summary>
/// �X�V
/// </summary>
void SceneGameOver::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ���L�[����������I����Ԃ�1������
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		// SE��炷
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

		m_select = (m_select + 1) % kSelectNum;
		m_selectPos.y += kSelectmoveY; // �I���J�[�\�������Ɉړ�

		// �I���J�[�\������ԉ��ɂ�������l�p����ԏ�ɖ߂�
		if (m_selectPos.y > kInitSelectPosY + kSelectmoveY * (kSelectNum - 1))
		{
			m_selectPos.y = kInitSelectPosY;
		}
	}
	// ���L�[����������I����Ԃ�1�グ��
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		// SE��炷
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;
		m_selectPos.y -= kSelectmoveY;	// �I���J�[�\������Ɉړ�

		if (m_selectPos.y < kInitSelectPosY)
		{
			m_selectPos.y = kInitSelectPosY + kSelectmoveY * (kSelectNum - 1);
		}
	}

	// Z�L�[orA�{�^�����������Ƃ�
	if (Pad::IsTrigger(PAD_INPUT_A))
	{
		// SE��炷
		PlaySoundMem(m_selectSE, DX_PLAYTYPE_NORMAL, true);

		// �ړ��������
		switch (m_select)
		{
		case kRetry:
			m_isSceneRetry = true;
			StopSoundMem(m_bgm);
			break;
		case kSelect:
			m_isSceneSelect = true;
			StopSoundMem(m_bgm);
			break;
		case kTitle:
			m_isSceneTitle = true;
			StopSoundMem(m_bgm);
			break;
		default:
			break;
		}
	}

	// �t�F�[�h�C���A�E�g
	if (m_isSceneRetry || m_isSceneTitle)
	{
		m_fadeAlpha += kFadeFrame;
		if (m_fadeAlpha > 255) m_fadeAlpha = 255;
	}
	else
	{
		m_fadeAlpha -= kFadeFrame;
		if (m_fadeAlpha < 0) m_fadeAlpha = 0;
	}

	// �w�i�̕\���ʒu�̍X�V
	m_bgMove += kBgMove;
}


/// <summary>
/// �`��
/// </summary>
void SceneGameOver::Draw()
{
	// �w�i�\��
	DrawBg();

	// �Q�[���I�[�o�[�\��
	DrawRectRotaGraph(kGameOverPosX, kGameOverPosY, 
		0, 0,
		kGameOverSizeX, kGameOverSizeY, 
		kGameOverScale, 0.0f,
		m_gameoverHandle, true);

	// �����\��
	DrawRectRotaGraph(kCharPosX, kCharPosY,
		0, 0, 
		kSelectSizeX, kSelectSizeY, 
		1.0f, 0.0f, 
		m_charHandle, true);

	// �I���J�[�\���̕\��
	DrawRectRotaGraph(static_cast<int>(m_selectPos.x), static_cast<int>(m_selectPos.y),
		0, 0, 
		kSelectSizeX, kSelectSizeY, 
		1.0f, 0.0f, 
		m_selectHandle, true);

#ifdef _DEBUG
	DrawString(10, 10, "�Q�[���I�[�o�[", 0xff0000);
#endif
}


/// <summary>
/// �w�i�`��
/// </summary>
void SceneGameOver::DrawBg()
{
	// �摜�T�C�Y���擾
	Size bg2Size;
	Size bg3Size;
	GetGraphSize(m_bg2Handle, &bg2Size.width, &bg2Size.height);
	GetGraphSize(m_bg3Handle, &bg3Size.width, &bg3Size.height);

	// �X�N���[���ʂ��v�Z����
	int scrollBg2 = static_cast<int>(m_bgMove * 0.1f) % static_cast<int>(bg2Size.width * kBgScale);
	int scrollBg3 = static_cast<int>(m_bgMove * 0.5f) % static_cast<int>(bg3Size.width * kBgScale);

	// �`��
	DrawGraph(0, 0, m_bgHandle, true);

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			static_cast<int>(scrollBg2 + index * bg2Size.width * kBgScale),
			static_cast<int>(Game::kScreenHeight - bg2Size.height * kBgScale),
			0, 0,
			kBgScale, 0.0f,
			m_bg2Handle, true);
	}

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			static_cast<int>(scrollBg3 + index * bg3Size.width * kBgScale),
			static_cast<int>(Game::kScreenHeight - bg3Size.height * kBgScale),
			0, 0,
			kBgScale, 0.0f,
			m_bg3Handle, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

