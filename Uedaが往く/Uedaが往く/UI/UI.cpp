#include "DxLib.h"
#include "UI.h"
#include <algorithm>

// �萔
namespace
{
	constexpr float kCursorWidth = 489.0f;			// �J�[�\���̉���
	constexpr float kCursorHeight = 90.0f;			// �J�[�\���̏c��
	constexpr float kCursorSpeed = 60.0f;			// �J�[�\���̉����̐L�т��
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
UI::UI():
	m_cursorWidth(0.0f)
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
	m_cursorWidth += kCursorSpeed;
	m_cursorWidth = std::min(m_cursorWidth, kCursorWidth);
}


/// <summary>
///  �J�[�\���\��
/// </summary>
/// <param name="pos">�\���ʒu</param>
/// <param name="select">�I�����</param>
/// <param name="interval">�\���Ԋu</param>
void UI::DrawCursor(Vec2 pos, int select, float interval)
{
	DrawExtendGraphF(pos.x, pos.y + interval * select,
		pos.x + m_cursorWidth, pos.y + interval * select + kCursorHeight,
		m_cursorHandle, true);
}
