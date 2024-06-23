#include "DxLib.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Font.h"
#include "Game.h"
#include "Input.h"

// �萔
namespace
{
	// UI�\���֘A
	constexpr int kClearPosX = 510;			// �N���A�ʒuX
	constexpr int kClearPosY = 130;			// �N���A�ʒuY
	constexpr int kSelectMove = 200;		// �I��\���̈ړ���
	constexpr int kFramePosX = 1250;		// �g�\���ʒuX
	constexpr int kFramePosY = 550;			// �g�\���ʒuY
	constexpr float kFrameAnim = 0.05f;		// �g�̊g��k���A�j���[�V�����Đ�����
	constexpr float kFrameScale = 1.0f;		// ���̘g�̃T�C�Y
	constexpr float kFrameChange = 0.1f;	// �g�̃T�C�Y�̕ω���

	// �e�L�X�g�֘A
	constexpr int kTextColor = 0x000000;	// �e�L�X�g�̐F
	constexpr int kStartPosX = 1350;		// ����1��v���C�ʒuX
	constexpr int kStartPosY = 590;			// ����1��v���C�ʒuY
	constexpr int kTitlePosX = 1350;		// �^�C�g���ɖ߂�\���ʒuX
	constexpr int kTitlePosY = 780;			// �^�C�g���ɖ߂�\���ʒuY
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneClear::SceneClear():
	m_select(Select::kStart),
	m_frameAnimTime(0.0f)
{
	m_clearHandle = LoadGraph("data/UI/clear.png");
	m_frameHandle = LoadGraph("data/UI/frame.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneClear::~SceneClear()
{
	DeleteGraph(m_clearHandle);
	DeleteGraph(m_frameHandle);
}


/// <summary>
/// ������
/// </summary>
void SceneClear::Init()
{
	// �����Ȃ�
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">����</param>
/// <returns>�J�ڐ�̃V�[��</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	m_frameAnimTime += kFrameAnim;

	// �I����Ԃ��X�V
	UpdateSelect(input);

	// �V�[���؂�ւ�
	if (input.IsTriggered("OK"))
	{
		if (m_select == Select::kStart)
		{
			return std::make_shared<ScenePlaying>(); // �Q�[���V�[���Ɉړ�
		}
		else if (m_select == Select::kTitle)
		{
			return std::make_shared<SceneTitle>();	// �^�C�g����ʂɈړ�
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneClear::Draw()
{
	// �w�i�\��
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x2d6676, true);

	// �N���A�̕����\��
	DrawGraph(kClearPosX, kClearPosY, m_clearHandle, true);

	// �g�\��
	for (int i = 0; i < kSelectNum; i++)
	{
		// �I�𒆂̃{�^�����g��k��������
		if (m_select == i)
		{
			// �g�̃T�C�Y��1.0�`1.1�ŕω�������
			float scale = kFrameScale + kFrameChange * sin(m_frameAnimTime);

			int width, height;
			int size = GetGraphSize(m_frameHandle, &width, &height);
			int scaleWidth = static_cast<int>(width * scale);
			int scaleHeight = static_cast<int>(height * scale);

			DrawExtendGraph(
				kFramePosX - static_cast<int>((scaleWidth - width) * 0.5f),
				kFramePosY + kSelectMove * i - static_cast<int>((scaleHeight - height) * 0.5f),
				kFramePosX + static_cast<int>((scaleWidth - width) * 0.5f) + width,
				kFramePosY + static_cast<int>(kSelectMove * i + (scaleHeight - height) * 0.5f) + height,
				m_frameHandle, true);
		}
		else
		{
			DrawGraph(kFramePosX, kFramePosY + kSelectMove * i, m_frameHandle, true);
		}
	}

	// �����\��
	DrawFormatStringToHandle(kStartPosX, kStartPosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearMenu)], "����1��v���C");
	DrawFormatStringToHandle(kTitlePosX, kTitlePosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearMenu)], "�^�C�g���ɂ��ǂ�");

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�N���A���", 0xffffff);
#endif
}


/// <summary>
/// �I����Ԃ��X�V
/// </summary>
/// <param name="input">����</param>
void SceneClear::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1������
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select - 1) % kSelectNum;	// �I����Ԃ�1�グ��
	}
}
