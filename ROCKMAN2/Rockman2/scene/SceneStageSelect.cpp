#include "SceneStageSelect.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// �����Ԋu
	constexpr int kCharInterval = 50;

	// �����\���ʒu
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 700;

	// �I���J�[�\���̏����ʒu
	constexpr int kInitSelectPosX = 920;
	constexpr int kInitSelectPosY = 500;
	// �I���J�[�\���̈ړ���
	constexpr int kSelectmoveY = 135;
	// �I���J�[�\���̃T�C�Y
	constexpr int kSelectSizeX = 500;
	constexpr int kSelectSizeY = 700;

	// �w�i�g�嗦
	constexpr float kBgScale = 2.0f;
	// �w�i�摜�̈ړ���
	constexpr int kBgMove = -3;
}

SceneStageSelect::SceneStageSelect() :
	m_select(kStage1),
	m_isSceneStage1(false),
	m_isSceneStage2(false),
	m_isSceneStage3(false),
	m_isSceneTitle(false),
	m_bgMove(0.0f),
	m_fadeAlpha(255),
	m_selectPos(kInitSelectPosX, kInitSelectPosY)
{
	// �摜�ǂݍ���
	m_selectHandle = LoadGraph("data/image/UI/select.png");
	m_selectCharHandle = LoadGraph("data/image/UI/selectRogo.png");
	m_charHandle = LoadGraph("data/image/UI/stageSelect.png");
	m_bgHandle = LoadGraph("data/image/BackGround/Title/bg1.png");
	m_bg2Handle = LoadGraph("data/image/BackGround/Title/bg2.png");
	m_bg3Handle = LoadGraph("data/image/BackGround/Title/bg3.png");
	m_bg4Handle = LoadGraph("data/image/BackGround/Title/bg4.png");
	
	// ���ǂݍ���
	m_bgm = LoadSoundMem("data/sound/BGM/stageSelect.mp3");
	m_selectSE = LoadSoundMem("data/sound/SE/select.wav");
	m_cursorSE = LoadSoundMem("data/sound/SE/cursor.mp3");
}

SceneStageSelect::~SceneStageSelect()
{
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_selectCharHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_bg2Handle);
	DeleteGraph(m_bg3Handle);
	DeleteGraph(m_bg4Handle);
	DeleteGraph(m_bgm);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_cursorSE);
}

void SceneStageSelect::Init()
{
	m_isSceneStage1 = false;
	m_isSceneStage2 = false;
	m_isSceneStage3 = false;
	m_isSceneTitle = false;
	m_select = kStage1;
	m_bgPos = { 0, 0 };
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
	
	// BGM��炷
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP, true);
}

void SceneStageSelect::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ���L�[����������I����Ԃ�1������
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		// SE��炷
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

		m_select = (m_select + 1) % kSelectNum;
		m_selectPos.y += kSelectmoveY; // �I�𒆂̎l�p�����Ɉړ�

		// �I�𒆂̎l�p����ԉ��ɂ�������l�p����ԏ�ɖ߂�
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
		m_selectPos.y -= kSelectmoveY;	// �I�𒆂̎l�p����Ɉړ�

		if (m_selectPos.y < kInitSelectPosY)
		{
			m_selectPos.y = kInitSelectPosY + kSelectmoveY * (kSelectNum - 1);
		}
	}

	// Z�L�[���������Ƃ�
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// SE��炷
		PlaySoundMem(m_selectSE, DX_PLAYTYPE_NORMAL, true);

		switch (m_select)
		{
		case kStage1:
			m_isSceneStage1 = true;
			StopSoundMem(m_bgm);
			break;
		case kStage2:
			m_isSceneStage2 = true;
			StopSoundMem(m_bgm);
			break;
		case kStage3:
			m_isSceneStage3 = true;
			StopSoundMem(m_bgm);
			break;
		case kBackTitle:
			m_isSceneTitle = true;
			StopSoundMem(m_bgm);
			break;
		default:
			break;
		}
	}

	// �t�F�[�h�C��
	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	// �w�i�̕\���ʒu�̍X�V
	m_bgMove += kBgMove;
}

void SceneStageSelect::Draw()
{
	// �t�F�[�h�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xe6e6fa, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �s�����ɖ߂�

	// �w�i�\�� TODO:�w�i������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawGraph(0, 0, m_bgHandle, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �\�����[�h�����ɖ߂�

	// �����\��
	DrawGraph(300, 150, m_selectCharHandle, true);
	DrawRectRotaGraph(kCharPosX, kCharPosY, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_charHandle, true, false);
	// �I���J�[�\���̕\��
	DrawRectRotaGraph(m_selectPos.x, m_selectPos.y, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_selectHandle, true, false);
}

void SceneStageSelect::End()
{
}

void SceneStageSelect::DrawBg()
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
	int scrollBg4 = static_cast<int>(m_bgMove) % static_cast<int>(bg4Size.width * kBgScale);

	// �`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 240);
	DrawGraph(0, 0, m_bgHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			scrollBg2 + index * bg2Size.width * kBgScale,
			Game::kScreenHeight - bg2Size.height * kBgScale,
			0, 0,
			kBgScale, 0.0f,
			m_bg2Handle, true);
	}

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			scrollBg3 + index * bg3Size.width * kBgScale,
			Game::kScreenHeight - bg3Size.height * kBgScale,
			0, 0,
			kBgScale, 0.0f,
			m_bg3Handle, true);
	}

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			scrollBg4 + index * bg4Size.width * kBgScale,
			Game::kScreenHeight - bg4Size.height * kBgScale,
			0, 0,
			kBgScale, 0.0f,
			m_bg4Handle, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
