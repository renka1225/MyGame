#include "SceneClear.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"
#include <cassert>

/// <summary>
/// �萔
/// </summary>
namespace
{
	// �N���A�\���ʒu
	constexpr int kClearPosX = 960;
	constexpr int kClearPosY = 300;
	// �N���A�̕����T�C�Y
	constexpr int kClearSizeX = 1038;
	constexpr int kClearSizeY = 174;
	// �N���A�̕����g�嗦
	constexpr float kClearScale = 0.8f;

	// �����\���ʒu
	constexpr int kCharPosX = Game::kScreenWidth - kClearSizeX + 80;
	constexpr int kCharPosY = 700;

	// �I���J�[�\���̏����ʒu
	constexpr int kInitSelectPosX = Game::kScreenWidth - kClearSizeX + 35;
	constexpr int kInitSelectPosY = 610;
	// �I���J�[�\���̈ړ���
	constexpr int kSelectmoveY = 190;
	// �I���J�[�\���̃T�C�Y
	constexpr int kSelectSizeX = 500;
	constexpr int kSelectSizeY = 700;

	// �w�i�g�嗦
	constexpr float kBgScale = 4.0f;
	// �w�i�摜�̈ړ���
	constexpr float kBgMove = -0.8f;

	// �t�F�[�h
	constexpr int kFadeFrame = 8;
}


SceneClear::SceneClear():
	m_select(kSelectStage),
	m_isSceneSelectStage(false),
	m_isSceneTitle(false),
	m_fadeAlpha(255),
	m_bgMove(0.0f)
{
	// �摜�ǂݍ���
	m_bgHandle = LoadGraph("data/image/BackGround/clear/clear.png");
	m_bg2Handle = LoadGraph("data/image/BackGround/clear/2.png");
	m_bg3Handle = LoadGraph("data/image/BackGround/clear/3.png");
	m_bg4Handle = LoadGraph("data/image/BackGround/clear/4.png");
	m_clearHandle = LoadGraph("data/image/UI/clear.png");
	m_charHandle = LoadGraph("data/image/UI/clearSelect.png");
	m_selectHandle = LoadGraph("data/image/UI/select.png");

	// ���ǂݍ���
	m_bgm = LoadSoundMem("data/sound/BGM/clear.mp3");
	m_selectSE = LoadSoundMem("data/sound/SE/select.wav");
	m_cursorSE = LoadSoundMem("data/sound/SE/cursor.mp3");
}


SceneClear::~SceneClear()
{
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_bg2Handle);
	DeleteGraph(m_bg3Handle);
	DeleteGraph(m_bg4Handle);
	DeleteGraph(m_clearHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_selectHandle);
	DeleteSoundMem(m_bgm);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_cursorSE);
}


/// <summary>
/// ������
/// </summary>
void SceneClear::Init()
{
	m_isSceneSelectStage = false;
	m_isSceneTitle = false;
	m_select = kSelectStage;
	m_selectPos = { kInitSelectPosX, kInitSelectPosY };
	m_fadeAlpha = 255;
	m_bgMove = kBgMove;

	// BGM��炷
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
}


/// <summary>
/// �X�V
/// </summary>
void SceneClear::Update()
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
		case kSelectStage:
			m_isSceneSelectStage = true;
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
	if (m_isSceneSelectStage || m_isSceneTitle)
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
void SceneClear::Draw()
{
	// �w�i�\��
	DrawBg();
	// �N���A�\��
	DrawRectRotaGraph(kClearPosX, kClearPosY, 
		0, 0, 
		kClearSizeX, kClearSizeY, 
		kClearScale, 0.0f,
		m_clearHandle, true);
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

	// �t�F�[�h�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x335980, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG
	DrawString(8, 16, "�N���A���", 0xffffff, false);
#endif
}


/// <summary>
/// �w�i�`��
/// </summary>
void SceneClear::DrawBg()
{
	// �摜�T�C�Y���擾
	Size bg2Size;
	Size bg3Size;
	Size bg4Size;
	GetGraphSize(m_bg2Handle, &bg2Size.width, &bg2Size.height);
	GetGraphSize(m_bg3Handle, &bg3Size.width, &bg3Size.height);
	GetGraphSize(m_bg4Handle, &bg4Size.width, &bg4Size.height);

	// �X�N���[���ʂ��v�Z����
	int scrollBg2 = static_cast<int>(m_bgMove * 0.25f) % static_cast<int>(bg2Size.width * kBgScale);
	int scrollBg3 = static_cast<int>(m_bgMove * 0.5f) % static_cast<int>(bg3Size.width * kBgScale);
	int scrollBg4 = static_cast<int>(m_bgMove * 0.8f) % static_cast<int>(bg4Size.width * kBgScale);

	// �`��
	DrawGraph(0, 0, m_bgHandle, false);

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

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			static_cast<int>(scrollBg4 + index * bg4Size.width * kBgScale),
			static_cast<int>(Game::kScreenHeight - bg4Size.height * kBgScale),
			0, 0,
			kBgScale, 0.0f,
			m_bg4Handle, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x335980, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
