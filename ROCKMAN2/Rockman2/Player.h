#pragma once
#include "Vec2.h"

class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();

private:
	int m_playerHandle;// �O���t�B�b�N�̃n���h��
	Vec2 m_pos;	 // �\���ʒu
};

