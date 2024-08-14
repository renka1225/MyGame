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
	void DrawCursor(Vec2 pos, int select, float interval);

private:
	float m_cursorWidth;	// �J�[�\���̉���
	int m_cursorHandle;		// �J�[�\���̉摜
};