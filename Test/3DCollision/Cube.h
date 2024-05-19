#pragma once
#include "DxLib.h"
#include <memory>

class Cube2;
class Plane;

// 立方体1クラス
class Cube
{
public:
	Cube(std::shared_ptr<Plane> pPlane, std::shared_ptr<Cube2> pCube2);
	~Cube() {};
	void Update();
	void Draw();
	void HitCube();	 // 立方体と立方体の当たり判定 
	void HitPlane(); // 立方体と平面の当たり判定 

private:
	std::shared_ptr<Cube2> m_pCube2;
	std::shared_ptr<Plane> m_pPlane;

	// 立方体1の中心点
	VECTOR m_pos;
	// 立方体1のサイズ
	VECTOR m_scale;
	// 立方体1の角度
	float m_angle;
	// 当たったか
	bool m_isHit;

	// 立方体の3Dモデル
	int m_handle;
};

