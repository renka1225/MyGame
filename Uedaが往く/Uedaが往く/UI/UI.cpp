#include "DxLib.h"
#include "Vec2.h"
#include "Game.h"
#include "Font.h"
#include "UI.h"
#include <algorithm>

// �萔
namespace
{
	// �w�i�֘A
	constexpr int kBackColor = 0xdddddd;			// �w�i�̐F
	constexpr int kBackBoxColor = 0x494949;			// �l�p�̐F
	constexpr int kBackBoxLTPos = 140;				// �l�p�̍���ʒu
	constexpr int kBackBoxWidth = 490;				// �l�p�̕�
	// �J�[�\���֘A
	constexpr float kCursorWidth = 489.0f;			// �J�[�\���̉���
	constexpr float kOptionCursorWidth = 1000.0f;	// �I�v�V������ʂ̃J�[�\���̉���
	constexpr float kCursorHeight = 90.0f;			// �J�[�\���̏c��
	constexpr float kCursorSpeed = 60.0f;			// �J�[�\���̉����̐L�т��
	// �{�^���̉摜�ƃe�L�X�g�̈ʒu
	const Vec2 kButtonTextPos = { 1500, 970 };		// �e�L�X�g�̈ʒu
	constexpr float kButtonTextWidth = 150.0f;		// �e�L�X�g�̕�
	constexpr int kTextColor = 0xffffff;			// �e�L�X�g�̐F
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
UI::UI():
	m_cursorWidth(0.0f),
	m_isOption(false)
{
	m_cursorHandle = LoadGraph("data/UI/cursor.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
UI::~UI()
{
	DeleteGraph(m_cursorHandle);
}


/// <summary>
/// ������
/// </summary>
void UI::Init()
{
	m_cursorWidth = 0.0f;
}


/// <summary>
/// �X�V
/// </summary>
void UI::Update()
{
	// �J�[�\���̉������X�V
	// �I�v�V������ʂ̏ꍇ�̂݃J�[�\���̒�����ς���
	m_cursorWidth += kCursorSpeed;
	if (m_isOption)
	{
		m_cursorWidth = std::min(m_cursorWidth, kOptionCursorWidth);
	}
	else
	{
		m_cursorWidth = std::min(m_cursorWidth, kCursorWidth);
	}
}


/// <summary>
///  �J�[�\���\��
/// </summary>
/// <param name="pos">�\���ʒu</param>
/// <param name="select">�I�����</param>
/// <param name="interval">�\���Ԋu</param>
void UI::DrawCursor(Vec2 pos, int select, float interval, bool isOption)
{
	m_isOption = isOption;
	DrawExtendGraphF(pos.x, pos.y + interval * select,
		pos.x + m_cursorWidth, pos.y + interval * select + kCursorHeight,
		m_cursorHandle, true);
}


/// <summary>
/// ���j���[�̔w�i�\��
/// </summary>
void UI::DrawMenuBg()
{
	// �w�i�`��
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBackColor, true);
	// �w�i�̎l�p�����\��
	DrawBox(kBackBoxLTPos, 0, kBackBoxLTPos + kBackBoxWidth, Game::kScreenHeight, kBackBoxColor, true);
}


/// <summary>
/// �{�^���̉摜�ƃe�L�X�g��\������
/// </summary>
void UI::DrawButtonText()
{
	//TODO:�V�[���ɂ���ăe�L�X�g��ύX����

	// �e�L�X�g�\��
	DrawStringFToHandle(kButtonTextPos.x, kButtonTextPos.y,
		"����", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kButtonText)]);
	DrawStringFToHandle(kButtonTextPos.x + kButtonTextWidth, kButtonTextPos.y,
		"���ǂ�", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kButtonText)]);
}
