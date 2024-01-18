#include "SceneTitle.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// �����\���ʒu
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 700;

	// �I���J�[�\���̏����ʒu
	constexpr int kInitSelectPosX = 950;
	constexpr int kInitSelectPosY = 580;
	// �I���J�[�\���̈ړ���
	constexpr int kSelectmoveY = 120;
	// �I���J�[�\���̃T�C�Y
	constexpr int kSelectSizeX = 414;
	constexpr int kSelectSizeY = 700;

	// �w�i�摜�̈ړ���
	constexpr int kBgMove = -4;
}

SceneTitle::SceneTitle():
	m_select(kStart),
	m_isSceneStart(false),
	m_isSceneOption(false),
	m_fadeAlpha(80)
{
	m_logoHandle = LoadGraph("data/image/Title/TitleLogo.png");
	m_selectHandle = LoadGraph("data/image/select.png");
	m_charHandle = LoadGraph("data/image/Title/titleChar.png");
	m_bg = LoadGraph("data/image/Title/bg.jpg");
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_logoHandle);
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_charHandle);
}

void SceneTitle::Init()
{
	m_isSceneStart = false;
	m_isSceneOption = false;
	m_select = kStart;
	m_selectPos = { kInitSelectPosX,  kInitSelectPosY };
	m_bgMove = { kBgMove, 0 };
}

void SceneTitle::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ���L�[����������I����Ԃ�1������
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
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
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;
		m_selectPos.y -= kSelectmoveY;	// �I���J�[�\������Ɉړ�

		if (m_selectPos.y < kInitSelectPosY)
		{
			m_selectPos.y = kInitSelectPosY + kSelectmoveY * (kSelectNum - 1);
		}
	}

	// Z�L�[���������Ƃ�
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// TODO:�I����Ԃɂ���Ĉړ����ς���
		switch (m_select)
		{
		case kStart:
			m_isSceneStart = true;
			break;
		case kOption:
			m_isSceneOption = true;
			break;
		case kExit:
			DxLib_End();
			break;
		default:
			break;
		}
	}

	if (m_isSceneStart)
	{
		m_fadeAlpha += 3;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else
	{
		m_fadeAlpha -= 3;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}

	// �w�i�̕\���ʒu�̍X�V
	m_bgPos += m_bgMove;
}

void SceneTitle::Draw()
{
	// �t�F�[�h�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xe6e6fa, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �s�����ɖ߂�

	// �w�i�\�� TODO:�w�i�摜�ύX�A�w�i�����悤��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
	DrawGraph(m_bgPos.x, 0, m_bg, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �\�����[�h�����ɖ߂�
	
	// ���S�\��
	DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 4, 1.0f, 0.0f, m_logoHandle, true);
	// �����\��
	DrawRectRotaGraph(kCharPosX, kCharPosY, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_charHandle, true, false);
	// �I���J�[�\���̕\��
	DrawRectRotaGraph(m_selectPos.x, m_selectPos.y, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_selectHandle, true, false);

}

void SceneTitle::End()
{
}
