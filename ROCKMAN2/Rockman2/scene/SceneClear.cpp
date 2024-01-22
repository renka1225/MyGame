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
	constexpr int kInitSelectPosX = 920;
	constexpr int kInitSelectPosY = 630;
	// �I���J�[�\���̈ړ���
	constexpr int kSelectmoveY = 170;
	// �I���J�[�\���̃T�C�Y
	constexpr int kSelectSizeX = 500;
	constexpr int kSelectSizeY = 700;
}


SceneClear::SceneClear():
	m_select(kSelectStage),
	m_isSceneSelectStage(false),
	m_isSceneTitle(false)
{
	m_clearHandle = LoadGraph("data/image/UI/clear.png");
	m_charHandle = LoadGraph("data/image/UI/clearSelect.png");
	m_selectHandle = LoadGraph("data/image/UI/select.png");
}

SceneClear::~SceneClear()
{
	DeleteGraph(m_clearHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_selectHandle);
}

void SceneClear::Init()
{
	m_isSceneSelectStage = false;
	m_isSceneTitle = false;
	m_select = kSelectStage;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
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
		// �ړ��������
		switch (m_select)
		{
		case kSelectStage:
			m_isSceneSelectStage = true;
			break;
		case kTitle:
			m_isSceneTitle = true;
		default:
			break;
		}
	}
}

void SceneClear::Draw()
{
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
