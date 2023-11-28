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

	// グラフィックの設定
	void SetHandle(int handle) { m_handle = handle; }

private:
	// 背景の表示位置
	Vec2 m_pos;

	// グラフィック
	int m_handle;
};