#pragma once
#include "DxLib.h"

/// <summary>
/// 三角形クラス
/// </summary>
class Triangle
{
public:
	Triangle();
	~Triangle() {};
	void Draw();

	// 頂点1を取得
	VECTOR GetPos1() const { return m_pos1; }
	// 頂点2を取得
	VECTOR GetPos2() const { return m_pos2; }
	// 頂点3を取得
	VECTOR GetPos3() const { return m_pos3; }

private:
	// 頂点1の座標
	VECTOR m_pos1;
	// 頂点2の座標
	VECTOR m_pos2;
	// 頂点3の座標
	VECTOR m_pos3;
};