#include "SceneClear.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// �N���A�����\���ʒu
	constexpr int kClearPosX = 960;
	constexpr int kClearPosY = 300;

	// �N���A�����̃T�C�Y
	constexpr int kClearSizeX = 1035;
	constexpr int kClearSizeY = 171;

	// �����\���ʒu
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 700;

	// �I���J�[�\���̏����ʒu
	constexpr int kInitSelectPosX = 910;
	constexpr int kInitSelectPosY = 610;
	// �I���J�[�\���̈ړ���
	constexpr int kSelectmoveY = 190;
	// �I���J�[�\���̃T�C�Y
	constexpr int kSelectSizeX = 500;
	constexpr int kSelectSizeY = 700;
}


SceneClear::SceneClear():
	m_select(kSelectStage),
	m_isSceneSelectStage(false),
	m_isSceneTitle(false),
	m_fadeAlpha(255)
{
	// �摜�ǂݍ���
	m_bgHandle = LoadGraph("data/image/BackGround/clear.png");
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
	DeleteGraph(m_clearHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_selectHandle);
	DeleteSoundMem(m_bgm);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_cursorSE);
}

void SceneClear::Init()
{
	m_isSceneSelectStage = false;
	m_isSceneTitle = false;
	m_select = kSelectStage;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
	m_fadeAlpha = 255;

	// BGM��炷
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
}

void SceneClear::End()
{
}

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
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else
	{
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
}

void SceneClear::Draw()
{
	// �w�i�\��
	DrawGraph(0, 0, m_bgHandle, false);
	// �N���A�\��
	DrawRectRotaGraph(kClearPosX, kClearPosY, 0, 0, kClearSizeX, kClearSizeY, 0.8f, 0.0f, m_clearHandle, true, false);
	// �����\��
	DrawRectRotaGraph(kCharPosX, kCharPosY, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_charHandle, true, false);
	// �I���J�[�\���̕\��
	DrawRectRotaGraph(m_selectPos.x, m_selectPos.y, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_selectHandle, true, false);

#ifdef _DEBUG
	DrawString(8, 16, "�N���A���", 0xffffff, false);
#endif
}
