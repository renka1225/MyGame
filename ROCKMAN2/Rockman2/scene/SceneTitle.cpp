#include "SceneTitle.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// OP����Đ�����
	constexpr int kMoveFrame = 1200;
	// OP�𗬂��܂ł̎���
	constexpr int kStandFrame = 1800;

	// �����\���ʒu
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 720;

	// �I���J�[�\���̏����ʒu
	constexpr int kInitSelectPosX = 950;
	constexpr int kInitSelectPosY = 540;
	// �I���J�[�\���̈ړ���
	constexpr int kSelectmoveY = 185;
	// �I���J�[�\���̃T�C�Y
	constexpr int kSelectSizeX = 450;
	constexpr int kSelectSizeY = 700;

	// �w�i�g�嗦
	constexpr float kBgScale = 2.0f;
	// �w�i�摜�̈ړ���
	constexpr float kBgMove = -3.0f;
}

SceneTitle::SceneTitle():
	m_select(kStart),
	m_isSceneStart(false),
	m_isSceneOption(false),
	m_moveFrame(kMoveFrame),
	m_standFrame(0),
	m_fadeAlpha(180),
	m_bgMove(0.0f)
{
	// �摜�ǂݍ���
	m_logoHandle = LoadGraph("data/image/TitleLogo.png");
	m_charHandle = LoadGraph("data/image/UI/titleChar.png");
	m_selectHandle = LoadGraph("data/image/UI/select.png");
	m_bgHandle = LoadGraph("data/image/BackGround/Title/bg1.png");
	m_bg2Handle = LoadGraph("data/image/BackGround/Title/bg2.png");
	m_bg3Handle = LoadGraph("data/image/BackGround/Title/bg3.png");
	m_bg4Handle = LoadGraph("data/image/BackGround/Title/bg4.png");

	// ���ǂݍ���
	m_bgm = LoadSoundMem("data/sound/BGM/title.mp3");
	m_selectSE = LoadSoundMem("data/sound/SE/select.wav");
	m_cursorSE = LoadSoundMem("data/sound/SE/cursor.mp3");
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_logoHandle);
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_bg2Handle);
	DeleteGraph(m_bg3Handle);
	DeleteGraph(m_bg4Handle);
	DeleteSoundMem(m_bgm);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_cursorSE);
}

void SceneTitle::Init()
{
	m_isSceneStart = false;
	m_isSceneOption = false;
	m_moveFrame = 0;
	m_fadeAlpha = 180;
	m_select = kStart;
	m_selectPos = { kInitSelectPosX,  kInitSelectPosY };
	m_bgMove = kBgMove;

	// BGM��炷
	if (CheckSoundMem(m_bgm) == 0)
	{
		PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
	}
}

void SceneTitle::Update()
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
		return;
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
		return;
	}

	// Z�L�[orA�{�^������������J��
	if (Pad::IsTrigger(PAD_INPUT_A))
	{
		// SE��炷
		PlaySoundMem(m_selectSE, DX_PLAYTYPE_BACK, true);

		// ��ʑJ��
		switch (m_select)
		{
		case kStart:
			m_isSceneStart = true;
			StopSoundMem(m_bgm);
			break;
		case kOption:
			m_isSceneOption = true;
			break;
		case kExit:
			DxLib_End();
			StopSoundMem(m_bgm);
			break;
		default:
			break;
		}
		return;
	}

	// ���΂炭���u�����瓮����Đ�����
	m_standFrame++;
	if (m_standFrame > kStandFrame)
	{
		// OP�Đ�
		StopSoundMem(m_bgm);
		PlayMovie("data/OP.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		m_standFrame = 0;

		Init();
	}

	// �t�F�[�h�C���A�E�g
	if (m_isSceneStart)
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

	// �w�i�̕\���ʒu�̍X�V
	m_bgMove += kBgMove;
}

void SceneTitle::Draw()
{
	// �w�i�\��
	DrawBg();
	
	// ���S�\��
	DrawRotaGraph(static_cast<int>(Game::kScreenWidth * 0.5), static_cast<int>(Game::kScreenHeight * 0.25 - 40), 1.0f, 0.0f, m_logoHandle, true);
	// �����\��
	DrawRectRotaGraph(kCharPosX, kCharPosY, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_charHandle, true, false);
	// �I���J�[�\���̕\��
	DrawRectRotaGraph(static_cast<int>(m_selectPos.x), static_cast<int>(m_selectPos.y), 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_selectHandle, true, false);

	// �t�F�[�h�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x808080, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �s�����ɖ߂�
}

// �w�i�`��
void SceneTitle::DrawBg()
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
	int scrollBg3 = static_cast<int>(m_bgMove * 0.4f) % static_cast<int>(bg3Size.width * kBgScale);
	int scrollBg4 = static_cast<int>(m_bgMove) % static_cast<int>(bg4Size.width * kBgScale);

	// �`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(0, 0, m_bgHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

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

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x00004d, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
