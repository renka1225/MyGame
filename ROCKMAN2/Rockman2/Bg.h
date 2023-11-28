#pragma once
#include "Vec2.h"
#include "Game.h"

class Bg
{
public:
	Bg();
	~Bg();

	void Init();
	void Update();
	void Draw();

	// �O���t�B�b�N�̐ݒ�
	void SetHandle(int handle) { m_handle = handle; }

private:
	// �w�i�̕\���ʒu
	Vec2 m_pos;

	// �O���t�B�b�N
	int m_handle;
};