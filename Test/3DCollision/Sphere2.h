#pragma once
#include "DxLib.h"

// 球2クラス
class Sphere2
{
public:
	Sphere2();
	~Sphere2() {};
	void Draw();

	// 球2の座標を取得
	VECTOR GetPos() const { return m_pos; }

private:
	VECTOR m_pos;	// 表示位置
};

