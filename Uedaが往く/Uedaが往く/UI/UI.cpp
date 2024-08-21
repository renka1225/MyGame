#include "DxLib.h"
#include "Vec2.h"
#include "Game.h"
#include "Font.h"
#include "UI.h"
#include <algorithm>

// �萔
namespace
{
	/*�w�i�֘A*/
	constexpr int kBackColor = 0xdddddd;				// �w�i�̐F
	constexpr int kBackBoxColor = 0x494949;				// �l�p�̐F
	constexpr int kBackBoxLTPos = 140;					// �l�p�̍���ʒu
	constexpr int kBackBoxWidth = 490;					// �l�p�̕�
	const Vec2 kBackHandlePos = { 750.0f, 200.0f };		// �w�i�摜�̕\���ʒu

	const Vec2 kPauseBackLTPos = { 600.0f, 200.0f };	// �|�[�Y��ʂ̔w�i�摜����ʒu
	const Vec2 kPauseBackRBPos = { 1320.0f, 880.0f };	// �|�[�Y��ʂ̔w�i�摜�E���ʒu

	/*�J�[�\���֘A*/
	constexpr float kCursorWidth = 489.0f;				// �J�[�\���̉���
	constexpr float kOptionCursorWidth = 1000.0f;		// �I�v�V������ʂ̃J�[�\���̉���
	constexpr float kCursorHeight = 90.0f;				// �J�[�\���̏c��
	constexpr float kCursorSpeed = 60.0f;				// �J�[�\���̉����̐L�т��

	/*�{�^���̉摜�ƃe�L�X�g�̈ʒu*/
	const Vec2 kButtonPos = { 1500, 1000 };				// �{�^���\���ʒu
	const Vec2 kClearButtonPos = { 1450, 1000 };		// �N���A���{�^���\���ʒu
	constexpr float kButtonWidth = 180.0f;				// �\������{�^���̕�
	constexpr int kButtonSize = 32;						// �{�^���摜�̃T�C�Y
	constexpr float kButtonScale = 1.5f;				// �{�^���̊g�嗦
	const Vec2 kButtonTextPos = { 1530, 970 };			// �e�L�X�g�̈ʒu
	const Vec2 kClearButtonTextPos = { 1480, 975 };		// �N���A���̃e�L�X�g�ʒu
	constexpr float kButtonTextWidth = 170.0f;			// �e�L�X�g�̕�
	constexpr int kTextColor = 0xffffff;				// �e�L�X�g�̐F

	/*����������*/
	const Vec2 kOperationFramePos = { 1720.0f, 280.0f };	// �g�\���ʒu
	constexpr float kOperationWidth = 300.0f;				// �g�̉���
	constexpr float kOperationHeight = 350.0f;				// �g�̏c��
	constexpr int kOperationBackColor = 0x000000;			// �g�̔w�i�F
	const Vec2 kOperationTextPos = { 1730.0f, 300.0f };		// �e�L�X�g�̕\���ʒu
	const Vec2 kOperationButtonPos = { 1880.0f, 320.0f };	// �{�^���ʒu
	constexpr float kOperationButtonScale = 1.0f;			// �{�^���T�C�Y
	constexpr float kOperationInterval = 40.0f;				// �\���Ԋu
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
UI::UI():
	m_cursorWidth(0.0f),
	m_isOption(false)
{
	m_cursorHandle = LoadGraph("data/UI/cursor.png");
	m_buttonHandle = LoadGraph("data/UI/button.png");
	m_backHandle = LoadGraph("data/UI/back.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
UI::~UI()
{
	DeleteGraph(m_cursorHandle);
	DeleteGraph(m_buttonHandle);
	DeleteGraph(m_backHandle);
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
/// �|�[�Y��ʂ̔w�i�\��
/// </summary>
void UI::DrawPauseBack()
{
	// �w�i�摜�\��
	DrawExtendGraphF(kPauseBackLTPos.x, kPauseBackLTPos.y, kPauseBackRBPos.x, kPauseBackRBPos.y, m_backHandle, true);
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
	// �w�i�摜�\��
	DrawGraphF(kBackHandlePos.x, kBackHandlePos.y, m_backHandle, true);
}


/// <summary>
/// �{�^���̉摜�ƃe�L�X�g��\������
/// </summary>
void UI::DrawButtonText()
{
	// �e�L�X�g�\��
	DrawStringFToHandle(kButtonTextPos.x, kButtonTextPos.y,
		"����", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kButtonText)]);
	DrawStringFToHandle(kButtonTextPos.x + kButtonTextWidth, kButtonTextPos.y,
		"���ǂ�", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kButtonText)]);

	// �{�^���摜�\��
	DrawRectRotaGraphF(kButtonPos.x, kButtonPos.y, kButtonSize * ButtonKind::kAButton, 0, kButtonSize, kButtonSize, kButtonScale, 0.0f, m_buttonHandle, true);
	DrawRectRotaGraphF(kButtonPos.x + kButtonWidth, kButtonPos.y, kButtonSize * ButtonKind::kBButton, 0, kButtonSize, kButtonSize, kButtonScale, 0.0f, m_buttonHandle, true);
}


/// <summary>
/// �N���A��ʂŃ{�^���̉摜�ƃe�L�X�g�\������
/// </summary>
void UI::DrawClearButtonText()
{
	// �e�L�X�g�\��
	DrawStringFToHandle(kClearButtonTextPos.x, kClearButtonTextPos.y,
		"�X�e�[�W�I���ɂ��ǂ�", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearButtonText)]);

	// �{�^���摜�\��
	DrawRectRotaGraphF(kClearButtonPos.x, kClearButtonPos.y, kButtonSize * ButtonKind::kAButton, 0, kButtonSize, kButtonSize, kButtonScale, 0.0f, m_buttonHandle, true);
}


/// <summary>
/// ���������\������
/// </summary>
void UI::DrawOperation()
{
	// �w�i�𔖂��\������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxAA(kOperationFramePos.x, kOperationFramePos.y, kOperationFramePos.x + kOperationWidth, kOperationFramePos.y + kOperationHeight, kOperationBackColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �e�L�X�g�\��
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kMove,
		"�ړ�", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kCameraMove,
		"�J�����ړ�", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kPunch,
		"�p���`", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kKick,
		"�L�b�N", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kAvoid,
		"���", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kGuard,
		"�K�[�h", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kRockon,
		"���b�N�I��", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kPause,
		"�|�[�Y", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);

	// �{�^���摜�\��
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kMove,
		kButtonSize * ButtonKind::kRStick, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);		// R�X�e�B�b�N
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kCameraMove,
		kButtonSize * ButtonKind::kLStick, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);		// L�X�e�B�b�N
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kPunch,
		kButtonSize * ButtonKind::kXButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// X
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kKick,
		kButtonSize * ButtonKind::kYButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// Y
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kAvoid,
		kButtonSize * ButtonKind::kAButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// A
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kGuard,
		kButtonSize * ButtonKind::kLBButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// LB
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kRockon,
		kButtonSize * ButtonKind::kRBButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// RB
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kPause,
		kButtonSize * ButtonKind::kMenuButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// Menu
}
