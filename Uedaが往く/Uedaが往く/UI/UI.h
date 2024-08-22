#pragma once
#include "Vec2.h"

/// <summary>
/// UI�̕\���Ɋւ���N���X
/// </summary>
class UI
{
public:
	UI();
	virtual ~UI();
	void Init();
	void Update();
	void DrawCursor(Vec2 pos, int select, float interval, bool isOption = false); // �J�[�\���\��
	void DrawPauseBack();		// �|�[�Y��ʂ̔w�i�\��
	void DrawMenuBg();			// ���j���[�̔w�i�\��
	void DrawButtonText();		// �{�^���e�L�X�g�\��
	void DrawClearButtonText();	// �N���A��ʂł̃{�^���e�L�X�g�\��


protected:
	int m_buttonHandle;		// �{�^���̉摜

	// �{�^���̎��
	enum ButtonKind
	{
		kAButton,		// A
		kBButton,		// B
		kXButton,		// X
		kYButton,		// Y
		kMenuButton,	// ���k�[
		kViewButton,	// �r���[
		kLStick,		// ���X�e�B�b�N
		kRStick,		// �E�X�e�B�b�N
		kLBButton,		// LB
		kRBButton,		// RB
	};

private:
	float m_cursorWidth;	// �J�[�\���̉���
	bool m_isOption;		// �I�v�V������ʂ��ǂ���
	int m_cursorHandle;		// �J�[�\���̉摜
	int m_backHandle;		// �w�i�̉摜
};