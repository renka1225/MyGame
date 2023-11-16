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
	int m_playerHandle;// グラフィックのハンドル
	Vec2 m_pos;	 // 表示位置
};

