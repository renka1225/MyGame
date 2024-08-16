#pragma once
#include "Vec2.h"

/// <summary>
/// UI�̕\���Ɋւ���N���X
/// </summary>
class UI
{
public:
	UI();
	~UI();
	void Init();
	void Update();
	void DrawCursor(Vec2 pos, int select, float interval, bool isOption = false); // �J�[�\���\��
	void DrawMenuBg();	// ���j���[�̔w�i�\��

private:
	float m_cursorWidth;	// �J�[�\���̉���
	bool m_isOption;		// �I�v�V������ʂ��ǂ���
	int m_cursorHandle;		// �J�[�\���̉摜
};