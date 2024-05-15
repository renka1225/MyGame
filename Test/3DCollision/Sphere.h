#pragma once
#include "DxLib.h"
#include <memory>

class Sphere2;
class Capsule2;

// 球1クラス
class Sphere
{
public:
	Sphere(std::shared_ptr<Sphere2> pSphere2, std::shared_ptr<Capsule2> pCapsule2);
	~Sphere() {};
	void Update();
	void Draw();
	void HitSphere();	// 球と球の当たり判定
	void HitCapsule();	// 球とカプセルの当たり判定

private:
	std::shared_ptr<Sphere2> m_pSphere2;
	std::shared_ptr<Capsule2> m_pCapsule2;

	VECTOR m_pos;	// 球1の表示位置
	int m_color;	// 球の色
	bool m_isHit;	// 当たったか
};

