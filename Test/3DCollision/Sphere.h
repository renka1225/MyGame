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
	VECTOR m_pos;		// 移動する球の位置
	VECTOR m_targetPos;	// 動かない球の位置
	bool m_isHit;		// 当たっているか

	static constexpr float kRadius = 40.0f;	// 半径
	static constexpr int kDivNum = 32;
};

