#pragma once
#include "DxLib.h"
#include <memory>

class Sphere2;
class Capsule2;
class Triangle;

// 球1クラス
class Sphere
{
public:
	Sphere(std::shared_ptr<Sphere2> pSphere2, std::shared_ptr<Capsule2> pCapsule2, std::shared_ptr<Triangle> pTriangle);
	~Sphere() {};
	void Update();
	void Draw();
	void HitSphere();	// 球と球の当たり判定
	void HitCapsule();	// 球とカプセルの当たり判定
	void HitTriangle();	// 球と三角形の当たり判定

private:
	std::shared_ptr<Sphere2> m_pSphere2;
	std::shared_ptr<Capsule2> m_pCapsule2;
	std::shared_ptr<Triangle> m_pTriangle;

	// 球1の表示位置
	VECTOR m_pos;
	// 球1の半径
	float m_radius;
	// 球の色
	int m_color;
	// 当たったか
	bool m_isHit;

private:
	static constexpr float kRadius = 10.0f;	// 球の半径
};

