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
}

SceneStageSelect::SceneStageSelect() :
	m_select(kStage1),
	m_isSceneStage1(false),
	m_isSceneStage2(false),
	m_isSceneStage3(false),
	m_isSceneTitle(false),
	m_fadeAlpha(255),
	m_selectPos(kInitSelectPosX, kInitSelectPosY)
{
	m_selectHandle = LoadGraph("data/image/UI/select.png");
	m_selectCharHandle = LoadGraph("data/image/UI/selectRogo.png");
	m_charHandle = LoadGraph("data/image/UI/stageSelect.png");
	m_bgHandle = LoadGraph("data/image/BackGround/stageSelect.png");
}

SceneStageSelect::~SceneStageSelect()
{
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_selectCharHandle);
	DeleteGraph(m_bgHandle);
}

void SceneStageSelect::Init()
{
	m_isSceneStage1 = false;
	m_isSceneStage2 = false;
	m_isSceneStage3 = false;
	m_isSceneTitle = false;
	m_select = kStage1;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
}

void SceneStageSelect::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ���L�[����������I����Ԃ�1������
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
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
		// TODO:�I����Ԃɂ���Ĉړ����ς���
		switch (m_select)
		{
		case kStage1:
			m_isSceneStage1 = true;
			break;
		case kStage2:
			m_isSceneStage2 = true;
			break;
		case kStage3:
			m_isSceneStage3 = true;
			break;
		case kBackTitle:
			m_isSceneTitle = true;
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
