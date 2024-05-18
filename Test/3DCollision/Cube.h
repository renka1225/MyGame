#pragma once
#include "DxLib.h"
#include <memory>

class Plane;

// 立方体1クラス
class Cube
{
public:
	Cube(std::shared_ptr<Plane> pPlane);
	~Cube() {};
	void Update();
	void Draw();
	void HitPlane(); // 立方体と平面の当たり判定 

private:
	std::shared_ptr<Plane> m_pPlane;

	// 立方体1の中心点
	VECTOR m_centerPos;
	// 立方体1の表示位置
	VECTOR m_pos1;
	VECTOR m_pos2;
	// 立方体1の角度
	float m_angle;
	// 立方体の色
	int m_color;
	// 当たったか
	bool m_isHit;

};

