#include "SceneGameOver.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// �Q�[���I�[�o�[�����\���ʒu
	constexpr int kGameOverPosX = 960;
	constexpr int kGameOverPosY = 300;

	// �Q�[���I�[�o�[�����̃T�C�Y
	constexpr int kGameOverSizeX = 1592;
	constexpr int kGameOverSizeY = 174;

	// �����\���ʒu
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 700;

	// �I���J�[�\���̏����ʒu
	constexpr int kInitSelectPosX = 910;
	constexpr int kInitSelectPosY = 560;
	// �I���J�[�\���̈ړ���
	constexpr int kSelectmoveY = 145;
	// �I���J�[�\���̃T�C�Y
	constexpr int kSelectSizeX = 500;
	constexpr int kSelectSizeY = 700;
}


SceneGameOver::SceneGameOver():
	m_select(kRetry),
	m_isSceneRetry(false),
	m_isSceneSelect(false),
	m_isSceneTitle(false)
{
	m_bgHandle = LoadGraph("data/image/BackGround/gameover.png");
	m_gameoverHandle = LoadGraph("data/image/UI/gameover.png");
	m_charHandle = LoadGraph("data/image/UI/gameoverSelect.png");
	m_selectHandle = LoadGraph("data/image/UI/select.png");
}

SceneGameOver::~SceneGameOver()
{
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_gameoverHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_selectHandle);
}

void SceneGameOver::Init()
{
	m_isSceneRetry = false;
	m_isSceneSelect = false;
	m_isSceneTitle = false;
	m_select = kRetry;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
}

void SceneGameOver::Update()
{
	// TODO:���g���C�ł���悤�ɂ���

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
		case kRetry:
			m_isSceneRetry = true;
			break;
		case kSelectStage:
			m_isSceneSelect = true;
			break;
		case kTitle:
			m_isSceneTitle = true;
		default:
			break;
		}
	}

#ifdef _DEBUG
	// Z�L�[����������X�e�[�W�I����ʂɑJ��
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_isSceneSelect = true;
	}
#endif

}

void SceneGameOver::Draw()
{
	// �w�i�\��
	DrawGraph(0, 0, m_bgHandle, true);

	// �Q�[���I�[�o�[�\��
	DrawRectRotaGraph(kGameOverPosX, kGameOverPosY, 0, 0,kGameOverSizeX,kGameOverSizeY, 0.8f, 0.0f, m_gameoverHandle, true, false);
	// �����\��
	DrawRectRotaGraph(kCharPosX, kCharPosY, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_charHandle, true, false);
	// �I���J�[�\���̕\��
	DrawRectRotaGraph(m_selectPos.x, m_selectPos.y, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_selectHandle, true, false);

#ifdef _DEBUG
	DrawString(10, 10, "�Q�[���I�[�o�[", 0xff0000);
#endif
}

void SceneGameOver::End()
{
	
}

