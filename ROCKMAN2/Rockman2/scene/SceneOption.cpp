#include "SceneOption.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// �����Ԋu
	constexpr int kCharInterval = 50;

	// �����\���ʒu
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 600;

	// �I���J�[�\���̏����ʒu
	constexpr int kInitSelectPosX = 950;
	constexpr int kInitSelectPosY = 340;
	// �I���J�[�\���̈ړ���
	constexpr int kSelectmoveY = 190;
	// �I���J�[�\���̃T�C�Y
	constexpr int kSelectSizeX = 414;
	constexpr int kSelectSizeY = 700;
}


SceneOption::SceneOption():
	m_select(kBackTitle),
	m_isSceneTitle(false),
	m_fadeAlpha(255),
	m_charHandle(-1)
{
	m_selectHandle = LoadGraph("data/image/select.png");
}

SceneOption::~SceneOption()
{
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_charHandle);
}

void SceneOption::Init()
{
	m_isSceneTitle = false;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
}

void SceneOption::Update()
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

void SceneOption::Draw()
{

#ifdef _DEBUG
	DrawString(20, 20, "�I�v�V�������", 0xffffff);
#endif

}

void SceneOption::End()
{
}
