#pragma once
#include "DxLib.h"

/// <summary>
/// 球
/// </summary>
class Sphere
{
public:
	Sphere();
	~Sphere();
	void Init();
	void Update();
	void Draw();

private:
	// 球との当たり判定
	void HitSphere();
	// カプセルとの当たり判定
	void HitCupsule();

private:
	VECTOR m_pos;				// 移動する球の位置
	VECTOR m_targetSpherePos;	// 動かない球の位置
	VECTOR m_cupsulePos1;		// カプセルの1つめの点の座標
	VECTOR m_cupsulePos2;		// カプセルの2つめの点の座標
	bool m_isHit;				// 当たっているか

	static constexpr float kRadius = 5.0f;	// 半径
	static constexpr int kDivNum = 32;

	static constexpr float kCupsuleRadius = 5.0f;	// カプセルの当たり半径
};

